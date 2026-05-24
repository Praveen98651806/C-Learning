# Phase 4: Processes, Threads & Signals — Theory & Code
> Time: Week 4 | Full C overlap — all code is C with Linux system calls

---

## 4.1 Process vs Thread

```
Process:                        Thread (within a process):
┌──────────────────────┐        ┌──────────────────────┐
│ Virtual Address Space│        │  Stack (per thread)  │
│ Code (.text)         │        │  Registers           │
│ Data (.data/.bss)    │        │  Thread ID (TID)     │
│ Heap (malloc)        │        │  ── shares ──        │
│ Stack                │        │  Code, Heap, Data,   │
│ File descriptors     │        │  File descriptors    │
│ PID                  │        └──────────────────────┘
└──────────────────────┘
```

Use case in chip work:
- `wpa_supplicant` = single process managing WiFi state machine
- Inside it: threads for TX handling, RX handling, timers, EAPOL
- Chip drivers in kernel also use workqueues (like threads)

---

## 4.2 fork() — Create a Child Process

```c
#include <stdio.h>
#include <unistd.h>    // fork, getpid
#include <sys/wait.h>  // wait

int main() {
    pid_t pid = fork();  // Creates exact copy of current process

    if (pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        // === CHILD PROCESS ===
        printf("Child: PID=%d, Parent PID=%d\n", getpid(), getppid());
        // Do child work here...
        return 0;  // Child exits
    } else {
        // === PARENT PROCESS ===
        printf("Parent: PID=%d, Child PID=%d\n", getpid(), pid);
        
        int status;
        wait(&status);  // Wait for child to finish (prevents zombie)
        
        if (WIFEXITED(status))
            printf("Child exited with code: %d\n", WEXITSTATUS(status));
    }
    return 0;
}
```

---

## 4.3 exec() — Replace Process with New Program

```c
#include <unistd.h>    // execv, execvp
#include <stdio.h>

int main() {
    // execvp replaces current process with a new program
    char *args[] = {"ls", "-la", "/sys/class/net", NULL};  // NULL terminated!
    
    execvp("ls", args);
    
    // If execvp returns, it failed
    perror("execvp failed");
    return 1;
}
```

### fork + exec pattern (how shell runs commands):
```c
pid_t pid = fork();
if (pid == 0) {
    // Child: replace with new program
    char *args[] = {"wpa_supplicant", "-i", "wlan0", "-c", "/etc/wpa.conf", NULL};
    execvp("wpa_supplicant", args);
    perror("exec failed");
    exit(1);
} else {
    // Parent: wait for child
    waitpid(pid, NULL, 0);
}
```

---

## 4.4 Signals — Asynchronous Notifications

```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

// Signal handler function
void handle_signal(int sig) {
    if (sig == SIGTERM) {
        printf("Got SIGTERM — cleaning up chip...\n");
        // Close device, save state, cleanup
        // In a real driver daemon: flush buffers, close /dev/...
    } else if (sig == SIGUSR1) {
        printf("Got SIGUSR1 — dumping chip stats\n");
        // Dump stats to file
    }
}

int main() {
    // Register signal handler
    signal(SIGTERM, handle_signal);   // kill <pid>
    signal(SIGUSR1, handle_signal);   // kill -USR1 <pid>
    signal(SIGINT, handle_signal);    // Ctrl+C
    
    // SIG_IGN to ignore a signal:
    signal(SIGPIPE, SIG_IGN);         // Ignore broken pipe
    
    printf("PID: %d — send signals with: kill -USR1 %d\n", getpid(), getpid());
    
    while (1) {
        sleep(1);  // Main loop
    }
    return 0;
}
```

### Common signals:
```
SIGTERM (15) - graceful shutdown (kill PID)
SIGKILL (9)  - force kill (kill -9 PID) — CANNOT be caught
SIGINT  (2)  - Ctrl+C
SIGHUP  (1)  - hang up (restart daemons: kill -HUP PID)
SIGUSR1 (10) - user defined
SIGUSR2 (12) - user defined
SIGCHLD (17) - child process stopped/exited
SIGSEGV (11) - segmentation fault (invalid memory access)
SIGALRM (14) - timer alarm (from alarm() call)
```

---

## 4.5 POSIX Threads (pthreads)

```c
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

// Thread function — must return void*, takes void*
void *rx_handler_thread(void *arg) {
    char *interface = (char *)arg;
    
    while (1) {
        printf("Handling RX on %s\n", interface);
        sleep(1);
    }
    return NULL;
}

void *tx_handler_thread(void *arg) {
    char *interface = (char *)arg;
    
    while (1) {
        printf("Handling TX on %s\n", interface);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t rx_tid, tx_tid;
    
    // Create threads
    pthread_create(&rx_tid, NULL, rx_handler_thread, "wlan0");
    pthread_create(&tx_tid, NULL, tx_handler_thread, "wlan0");
    
    // Wait for threads (join)
    pthread_join(rx_tid, NULL);
    pthread_join(tx_tid, NULL);
    
    return 0;
}
// Compile: gcc -o program program.c -lpthread
```

---

## 4.6 Mutex — Thread Synchronization

```c
#include <pthread.h>
#include <stdio.h>

// Shared data between threads
static int packet_count = 0;
static pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

void *rx_counter(void *arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&count_mutex);   // Lock before modifying shared data
        packet_count++;
        pthread_mutex_unlock(&count_mutex); // Unlock after
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, rx_counter, NULL);
    pthread_create(&t2, NULL, rx_counter, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    // Without mutex: count would be < 2000 due to race condition
    // With mutex: always exactly 2000
    printf("Packet count: %d (expected 2000)\n", packet_count);
    return 0;
}
```

---

## 4.7 Pipes — Inter-Process Communication

```c
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main() {
    int pipefd[2];  // pipefd[0] = read end, pipefd[1] = write end
    pipe(pipefd);
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child: reads from pipe
        close(pipefd[1]);  // Close write end
        
        char buf[256];
        int n = read(pipefd[0], buf, sizeof(buf));
        buf[n] = '\0';
        printf("Child received: %s\n", buf);
        close(pipefd[0]);
    } else {
        // Parent: writes to pipe
        close(pipefd[0]);  // Close read end
        
        const char *msg = "Chip status: OK\n";
        write(pipefd[1], msg, strlen(msg));
        close(pipefd[1]);
        
        wait(NULL);
    }
    return 0;
}
```

---

## 4.8 Shared Memory (mmap)

```c
#include <sys/mman.h>    // mmap, munmap
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
    // Create shared memory object (accessible by multiple processes)
    int fd = shm_open("/chip_shared_mem", O_CREAT | O_RDWR, 0644);
    ftruncate(fd, 4096);  // Set size
    
    // Map into process address space
    void *shared = mmap(NULL, 4096, PROT_READ | PROT_WRITE,
                        MAP_SHARED, fd, 0);
    
    // Write chip stats to shared memory
    struct chip_stats {
        int rx_packets;
        int tx_packets;
        int errors;
    } *stats = (struct chip_stats *)shared;
    
    stats->rx_packets = 1000;
    stats->tx_packets = 900;
    stats->errors = 5;
    
    printf("Stats written to shared memory\n");
    
    // Another process can read this with same shm_open + mmap
    
    munmap(shared, 4096);
    close(fd);
    shm_unlink("/chip_shared_mem");  // Remove shared memory
    return 0;
}
// Compile: gcc program.c -lrt
```

---

## 4.9 /proc Filesystem for Process Info

```bash
# Each running process has a directory in /proc:
ls /proc/$$              # $$ = current shell PID
# Contains:
# cmdline   - command line used to start process
# status    - process status (state, memory, etc.)
# maps      - memory map (virtual address spaces)
# fd/       - open file descriptors
# exe       - symlink to executable
# net/      - network stats for this process's network namespace

# Read wpa_supplicant info:
ps aux | grep wpa_supplicant
PID=12345
cat /proc/$PID/status
ls /proc/$PID/fd/         # See what files/sockets it has open
cat /proc/$PID/maps       # See its virtual memory layout
```

---

## Practice Exercises

1. Write a program that forks 5 children, each prints its PID, parent waits for all
2. Write a ping-pong program using pipes (parent sends, child receives and sends back)
3. Write a multithreaded program with a mutex to safely count to 100000 using 4 threads
4. Write a signal handler that gracefully shuts down a "daemon" on SIGTERM
5. List the file descriptors of a running process using `/proc/PID/fd`
6. Write a program that creates shared memory, fork, and child reads what parent wrote

---

*Next: `05_Networking/THEORY.md`*
