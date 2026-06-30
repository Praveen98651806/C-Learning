# File Handling in C — Complete Training Manual, Reference Guide & Interview Handbook

> **Audience:** College Students · Software Engineers · Embedded Engineers · Firmware Developers · Linux System Programmers · Linux Device Driver Developers  
> **Level:** Beginner → Expert  
> **Author:** Senior C Programming Trainer

---

## Table of Contents

1. [File Handling Fundamentals](#1-file-handling-fundamentals)
2. [FILE Pointer In Depth](#2-file-pointer-in-depth)
3. [File Opening Modes](#3-file-opening-modes)
4. [Standard File Functions In Depth](#4-standard-file-functions-in-depth)
5. [Text File Operations](#5-text-file-operations)
6. [Binary File Operations](#6-binary-file-operations)
7. [File Positioning Functions](#7-file-positioning-functions)
8. [Error Handling](#8-error-handling)
9. [Advanced Topics](#9-advanced-topics)
10. [Structures with Files](#10-structures-with-files)
11. [Dynamic Memory and Files](#11-dynamic-memory-and-files)
12. [OS Concepts Related to Files](#12-os-concepts-related-to-files)
13. [Embedded C and Linux File Concepts](#13-embedded-c-and-linux-file-concepts)
14. [30 Practical C Programs](#14-30-practical-c-programs)
    - [Beginner Programs (1–10)](#beginner-programs-110)
    - [Intermediate Programs (11–20)](#intermediate-programs-1120)
    - [Advanced Programs (21–30)](#advanced-programs-2130)
15. [50+ Interview Questions & Answers](#15-50-interview-questions--answers)
16. [Tricky Interview Questions](#16-tricky-interview-questions)
17. [Real-World Case Studies](#17-real-world-case-studies)
18. [Common Mistakes](#18-common-mistakes)
19. [Best Practices](#19-best-practices)
20. [Memory Diagrams & Flowcharts](#20-memory-diagrams--flowcharts)
21. [Learning & Interview Preparation Roadmap](#21-learning--interview-preparation-roadmap)

---

## 1. File Handling Fundamentals

### What is a File?

A **file** is a named collection of related data stored on a secondary storage device (hard disk, SSD, flash memory). Files persist beyond the lifetime of a process and allow programs to store and retrieve data permanently.

In C, a file is accessed through a **stream** — an abstract layer between the program and the physical storage.

### Why File Handling is Required

| Reason | Explanation |
|--------|-------------|
| **Persistence** | Data survives after the program ends |
| **Large data** | Handle datasets too large for RAM |
| **Inter-process communication** | Share data between programs via files |
| **Configuration** | Read settings at runtime without recompiling |
| **Logging** | Record events, errors, debug information |
| **Databases** | Basis of all flat-file and relational databases |
| **Embedded systems** | Log sensor data, firmware updates, device config |

### Types of Files

```
Files
├── Text Files       (.txt, .csv, .log, .ini, .json, .xml)
│   └── Human-readable, newline-terminated lines
└── Binary Files     (.bin, .dat, .exe, .img)
    └── Raw bytes, machine-readable, compact
```

#### Text Files
- Data stored as ASCII/UTF-8 characters.
- Lines separated by `\n` (Unix) or `\r\n` (Windows).
- Human-readable with a text editor.
- Slower for large structured data.
- Example: `/etc/passwd`, log files, CSV exports.

#### Binary Files
- Data stored as raw bytes — exactly as in memory.
- No newline translation.
- Compact and fast to read/write.
- Not human-readable without a hex editor.
- Example: `.exe`, `.bin` firmware images, `.dat` database files.

### Stream Concept in C

A **stream** is an abstraction that treats I/O as a continuous flow of bytes. C provides:

| Stream | File Descriptor | Default Device | Purpose |
|--------|----------------|----------------|---------|
| `stdin` | 0 | Keyboard | Standard input |
| `stdout` | 1 | Terminal | Standard output |
| `stderr` | 2 | Terminal | Error output |

When you open a file with `fopen()`, C creates a **FILE stream** connecting your program to the storage device through an internal buffer.

### File Handling Architecture

```
Your Program
     │
     ▼
  fopen() / fread() / fwrite()
     │
     ▼
 C Standard Library (stdio.h)
     │
     ▼
 Internal Buffer (Buffer in RAM)
     │
     ▼
 OS System Call (read() / write())
     │
     ▼
 Kernel / File System
     │
     ▼
 Physical Storage (HDD / SSD / Flash)
```

### Real-World Applications

| Domain | Use Case |
|--------|----------|
| Banking | Transaction logs, account records |
| Embedded | Sensor data logging, configuration files |
| Linux | `/proc`, `/sys`, device files (`/dev/ttyS0`) |
| Games | Save files, level data |
| Compilers | Source code input, object file output |
| Web servers | HTML files, access logs |
| Databases | Table storage files |

---

## 2. FILE Pointer In Depth

### What is FILE?

`FILE` is a **structure defined in `<stdio.h>`** that holds all state information about an open file stream. You never access its members directly — you use it only via a pointer.

```c
FILE *fp;   // fp is a pointer to a FILE structure
```

### FILE Structure (Internal — glibc implementation concept)

```c
// Conceptual representation (actual implementation varies by OS/compiler)
typedef struct {
    int          _fileno;      // File descriptor (OS handle)
    int          _flags;       // Open mode flags
    unsigned char *_IO_buf_base; // Start of I/O buffer
    unsigned char *_IO_buf_end;  // End of I/O buffer
    unsigned char *_IO_read_ptr; // Current read position
    unsigned char *_IO_write_ptr;// Current write position
    // ... more internal fields
} FILE;
```

You only interact with this through the `FILE *` pointer.

### FILE Pointer Declaration

```c
FILE *fp;              // Uninitialized — MUST assign before use
FILE *fp = NULL;       // Best practice: initialize to NULL
FILE *fp1, *fp2;       // Multiple file pointers
```

### fopen()

```c
FILE *fopen(const char *filename, const char *mode);
```

- Opens the file named `filename` in the given `mode`.
- Returns `NULL` on failure (file not found, permission denied, etc.).
- Always check the return value!

```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {
    perror("fopen failed");
    return 1;
}
```

### fclose()

```c
int fclose(FILE *fp);
```

- Flushes internal buffer to disk.
- Releases FILE structure memory.
- Returns `0` on success, `EOF` on error.
- **Always call `fclose()`** — not calling it can cause data loss or resource leaks.

```c
fclose(fp);
fp = NULL;   // Good practice: nullify after closing
```

### Working Mechanism

```
fopen("file.txt", "r")
    │
    ├─ OS opens file → gets file descriptor (e.g., fd=3)
    ├─ Allocates FILE structure in heap
    ├─ Allocates internal buffer (usually 8 KB = BUFSIZ)
    └─ Returns FILE * pointer

fgetc(fp)
    │
    ├─ Buffer empty? → OS read() call fills buffer from disk
    ├─ Returns next byte from buffer
    └─ Advances read pointer

fclose(fp)
    │
    ├─ Flushes any unwritten buffer data to disk
    ├─ OS close() → releases file descriptor
    └─ frees FILE structure memory
```

### Internal Buffering Concepts

| Buffer Type | When Flushed | Default For |
|-------------|--------------|-------------|
| **Fully buffered** | When buffer full, on `fflush()`, on `fclose()` | Regular files |
| **Line buffered** | On newline, when buffer full | `stdout` connected to terminal |
| **Unbuffered** | Immediately | `stderr` |

```c
// Force flush without closing
fflush(fp);

// Disable buffering (for stderr-like behavior)
setvbuf(fp, NULL, _IONBF, 0);
```

### Common Mistakes and Best Practices

| Mistake | Correct Approach |
|---------|-----------------|
| Not checking `fopen()` return | Always check for `NULL` |
| Forgetting `fclose()` | Use goto-cleanup or wrapper patterns |
| Using `fp` after `fclose()` | Set `fp = NULL` after closing |
| Opening same file twice in write mode | Check before opening |
| Mixing text and binary operations | Choose mode carefully |

---

## 3. File Opening Modes

### Mode Reference Table

| Mode | Read | Write | Append | Create | Truncate | Binary | File Must Exist? |
|------|------|-------|--------|--------|----------|--------|-----------------|
| `r`  | ✓ | ✗ | ✗ | ✗ | ✗ | ✗ | Yes |
| `w`  | ✗ | ✓ | ✗ | ✓ | ✓ | ✗ | No |
| `a`  | ✗ | ✓ | ✓ | ✓ | ✗ | ✗ | No |
| `r+` | ✓ | ✓ | ✗ | ✗ | ✗ | ✗ | Yes |
| `w+` | ✓ | ✓ | ✗ | ✓ | ✓ | ✗ | No |
| `a+` | ✓ | ✓ | ✓ | ✓ | ✗ | ✗ | No |
| `rb` | ✓ | ✗ | ✗ | ✗ | ✗ | ✓ | Yes |
| `wb` | ✗ | ✓ | ✗ | ✓ | ✓ | ✓ | No |
| `ab` | ✗ | ✓ | ✓ | ✓ | ✗ | ✓ | No |
| `rb+`| ✓ | ✓ | ✗ | ✗ | ✗ | ✓ | Yes |
| `wb+`| ✓ | ✓ | ✗ | ✓ | ✓ | ✓ | No |
| `ab+`| ✓ | ✓ | ✓ | ✓ | ✗ | ✓ | No |

### Detailed Explanation

#### `r` — Read Text
- Opens existing text file for reading.
- File pointer at beginning.
- Returns `NULL` if file does not exist.
```c
FILE *fp = fopen("input.txt", "r");
```

#### `w` — Write Text
- Creates new file or **truncates** existing file to zero length.
- File pointer at beginning.
- **WARNING:** Existing content is destroyed!
```c
FILE *fp = fopen("output.txt", "w");
```

#### `a` — Append Text
- Opens for writing; always writes at **end of file**.
- Creates file if it does not exist.
- Cannot write to earlier positions.
```c
FILE *fp = fopen("log.txt", "a");
```

#### `r+` — Read + Write Text
- Opens existing file for both reading and writing.
- File pointer at beginning.
- Does **not** truncate. Does **not** create.
```c
FILE *fp = fopen("data.txt", "r+");
```

#### `w+` — Read + Write (Truncate)
- Creates or truncates, then allows both read and write.
- Useful for temp files you process in place.
```c
FILE *fp = fopen("temp.txt", "w+");
```

#### `a+` — Read + Append
- Opens for reading anywhere, but all writes go to end.
```c
FILE *fp = fopen("log.txt", "a+");
```

#### Binary Modes (`rb`, `wb`, `ab`, `rb+`, `wb+`, `ab+`)
- Same as text modes but **no newline translation**.
- On Windows: `\n` ↔ `\r\n` translation is disabled.
- Always use binary mode for non-text data (images, executables, structs).

### Interview Questions on File Modes

**Q1:** What happens if you open a non-existent file with `"r"` mode?  
**A:** `fopen()` returns `NULL`. The file is NOT created.

**Q2:** What is the difference between `"w"` and `"a"` mode?  
**A:** `"w"` truncates the file (existing content lost); `"a"` preserves content and always writes at end.

**Q3:** Why use binary mode on Linux if Linux doesn't translate newlines?  
**A:** Portability. Code compiled on Windows would behave differently without `b`. Using `rb`/`wb` ensures consistent byte-level behavior across platforms.

**Q4:** Can you seek to an arbitrary position in `"a"` mode?  
**A:** You can call `fseek()`, but all writes are still forced to end-of-file regardless.

---

## 4. Standard File Functions In Depth

### fopen() — Open a File

```c
FILE *fopen(const char *path, const char *mode);
// Returns: FILE* on success, NULL on failure
```

### fclose() — Close a File

```c
int fclose(FILE *stream);
// Returns: 0 on success, EOF on failure
```

### fprintf() — Formatted Write to File

```c
int fprintf(FILE *stream, const char *format, ...);
// Like printf() but writes to a file
// Returns: number of characters written, negative on error
```
```c
FILE *fp = fopen("out.txt", "w");
fprintf(fp, "Name: %s, Age: %d\n", "Alice", 30);
fclose(fp);
```

### fscanf() — Formatted Read from File

```c
int fscanf(FILE *stream, const char *format, ...);
// Like scanf() but reads from a file
// Returns: number of items successfully read, EOF on end-of-file
```
```c
char name[50]; int age;
fscanf(fp, "%s %d", name, &age);
```

### fgetc() — Read One Character

```c
int fgetc(FILE *stream);
// Returns: character as unsigned char cast to int, or EOF
```
```c
int ch;
while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
}
```

### fputc() — Write One Character

```c
int fputc(int c, FILE *stream);
// Returns: character written, or EOF on error
```
```c
fputc('A', fp);
```

### fgets() — Read a Line (Safe)

```c
char *fgets(char *str, int n, FILE *stream);
// Reads at most n-1 characters, stops at newline or EOF
// Always null-terminates str
// Returns: str on success, NULL on EOF or error
```
```c
char line[256];
while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
}
```

### fputs() — Write a String

```c
int fputs(const char *str, FILE *stream);
// Writes string (without appending newline)
// Returns: non-negative on success, EOF on error
```
```c
fputs("Hello, World!\n", fp);
```

### fread() — Binary Read (Block Read)

```c
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
// Reads count items of size bytes each into ptr
// Returns: number of items successfully read
```
```c
int arr[10];
size_t items = fread(arr, sizeof(int), 10, fp);
```

### fwrite() — Binary Write (Block Write)

```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
// Writes count items of size bytes each from ptr
// Returns: number of items successfully written
```
```c
int arr[10] = {1,2,3,4,5,6,7,8,9,10};
fwrite(arr, sizeof(int), 10, fp);
```

### fseek() — Move File Pointer

```c
int fseek(FILE *stream, long offset, int whence);
// whence: SEEK_SET (from start), SEEK_CUR (from current), SEEK_END (from end)
// Returns: 0 on success, non-zero on failure
```
```c
fseek(fp, 0, SEEK_SET);   // Go to beginning
fseek(fp, 10, SEEK_CUR);  // Move 10 bytes forward
fseek(fp, -5, SEEK_END);  // 5 bytes before end
```

### ftell() — Get Current File Position

```c
long ftell(FILE *stream);
// Returns: current byte offset from beginning, -1L on error
```
```c
long pos = ftell(fp);
printf("Current position: %ld\n", pos);
```

### rewind() — Go to Beginning

```c
void rewind(FILE *stream);
// Equivalent to fseek(fp, 0L, SEEK_SET) + clears error flag
```

### fflush() — Flush Buffer

```c
int fflush(FILE *stream);
// Forces buffered output to be written to the OS
// Pass NULL to flush all open output streams
// Returns: 0 on success, EOF on error
```
```c
fflush(fp);       // Flush specific stream
fflush(NULL);     // Flush all streams
fflush(stdout);   // Force terminal output
```

### remove() — Delete a File

```c
int remove(const char *filename);
// Returns: 0 on success, non-zero on failure
```
```c
if (remove("old_data.txt") != 0)
    perror("remove failed");
```

### rename() — Rename or Move a File

```c
int rename(const char *oldname, const char *newname);
// Returns: 0 on success, non-zero on failure
```
```c
rename("temp.txt", "final.txt");
```

### feof() — Test End-of-File

```c
int feof(FILE *stream);
// Returns: non-zero if EOF indicator is set, 0 otherwise
// NOTE: Only TRUE *after* a read has already failed due to EOF
```
```c
// WRONG pattern:
while (!feof(fp)) { fgetc(fp); }  // Reads one extra iteration!

// CORRECT pattern:
int ch;
while ((ch = fgetc(fp)) != EOF) { ... }
```

### ferror() — Test File Error

```c
int ferror(FILE *stream);
// Returns: non-zero if error indicator is set, 0 otherwise
```
```c
if (ferror(fp)) {
    fprintf(stderr, "File error occurred\n");
    clearerr(fp);
}
```

### perror() — Print Error Message

```c
void perror(const char *s);
// Prints s followed by ": " and the system error message for errno
```
```c
FILE *fp = fopen("missing.txt", "r");
if (!fp) perror("fopen");   // Output: "fopen: No such file or directory"
```

### clearerr() — Clear Error and EOF Flags

```c
void clearerr(FILE *stream);
// Clears error and EOF flags so the stream can be used again
```

---

## 5. Text File Operations

### Creating and Writing

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("students.txt", "w");
    if (!fp) { perror("fopen"); return 1; }

    fprintf(fp, "Alice 95\n");
    fprintf(fp, "Bob   87\n");
    fprintf(fp, "Carol 91\n");

    fclose(fp);
    return 0;
}
```

### Appending Data

```c
FILE *fp = fopen("log.txt", "a");
if (!fp) { perror("fopen"); return 1; }
fprintf(fp, "[INFO] Server started at port 8080\n");
fclose(fp);
```

### Reading Data — Line by Line

```c
FILE *fp = fopen("students.txt", "r");
if (!fp) { perror("fopen"); return 1; }

char line[256];
while (fgets(line, sizeof(line), fp) != NULL) {
    printf("%s", line);
}
fclose(fp);
```

### Reading Data — Character by Character

```c
FILE *fp = fopen("file.txt", "r");
int ch;
while ((ch = fgetc(fp)) != EOF) {
    putchar(ch);
}
fclose(fp);
```

### Updating a Text File

Text files do not support in-place update easily. The standard approach is:
1. Read original file.
2. Write to a temporary file with modifications.
3. `remove()` original, `rename()` temp to original.

```c
// Pattern: update a line in a text file
FILE *in = fopen("data.txt", "r");
FILE *out = fopen("data_tmp.txt", "w");
char line[256];
while (fgets(line, sizeof(line), in)) {
    if (strstr(line, "Alice"))
        fprintf(out, "Alice 100\n");  // Replace line
    else
        fputs(line, out);
}
fclose(in);
fclose(out);
remove("data.txt");
rename("data_tmp.txt", "data.txt");
```

### Error Handling Pattern

```c
FILE *fp = fopen("data.txt", "r");
if (!fp) {
    perror("Cannot open data.txt");
    return EXIT_FAILURE;
}
// ... operations ...
if (ferror(fp)) {
    fprintf(stderr, "Error while reading file\n");
    fclose(fp);
    return EXIT_FAILURE;
}
fclose(fp);
```

---

## 6. Binary File Operations

### Why Binary Files are Used

| Factor | Text Files | Binary Files |
|--------|-----------|--------------|
| Size | Larger (extra chars for numbers) | Compact (raw bytes) |
| Speed | Slower (conversion needed) | Faster (direct memory copy) |
| Portability | High (human-readable) | Lower (endianness, alignment) |
| Use case | Config, logs, CSV | Databases, images, firmware |

### Writing a Structure to a Binary File

```c
#include <stdio.h>
#include <string.h>

typedef struct {
    int  id;
    char name[50];
    float salary;
} Employee;

int main(void) {
    Employee emp = {101, "Alice", 75000.0f};

    FILE *fp = fopen("employees.dat", "wb");
    if (!fp) { perror("fopen"); return 1; }

    fwrite(&emp, sizeof(Employee), 1, fp);
    fclose(fp);
    printf("Record written.\n");
    return 0;
}
```

### Reading a Structure from a Binary File

```c
int main(void) {
    Employee emp;

    FILE *fp = fopen("employees.dat", "rb");
    if (!fp) { perror("fopen"); return 1; }

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        printf("ID: %d | Name: %s | Salary: %.2f\n",
               emp.id, emp.name, emp.salary);
    }
    fclose(fp);
    return 0;
}
```

### Performance Comparison

```c
// Text: Writing 1000 integers
fprintf(fp, "%d\n", value);   // Format conversion + newline per write

// Binary: Writing 1000 integers
fwrite(&value, sizeof(int), 1, fp);  // Raw bytes — 3-5x faster
```

### Embedded System Use Cases

- **Data logger:** Write sensor readings as binary structs every second.
- **Firmware update:** Read `.bin` file with `fread()` block by block and flash to MCU.
- **EEPROM backup:** Dump configuration struct to binary file.

---

## 7. File Positioning Functions

### File Pointer Concepts

The **file position indicator** tracks where the next read or write will occur. It is a byte offset from the beginning of the file.

```
File contents:   H  e  l  l  o  ,     W  o  r  l  d  !  \n
Byte offset:     0  1  2  3  4  5  6  7  8  9  10 11 12 13
                 ^
          Position indicator (after fopen)
```

### fseek() — Move to Any Position

```c
int fseek(FILE *fp, long offset, int whence);
```

| `whence` | Meaning | Example |
|----------|---------|---------|
| `SEEK_SET` | From beginning of file | `fseek(fp, 100, SEEK_SET)` → byte 100 |
| `SEEK_CUR` | From current position | `fseek(fp, -5, SEEK_CUR)` → 5 bytes back |
| `SEEK_END` | From end of file | `fseek(fp, 0, SEEK_END)` → end |

### ftell() — Current Position

```c
long ftell(FILE *fp);
// Returns current byte offset from start, -1L on error
```

**Trick: Get file size**
```c
fseek(fp, 0, SEEK_END);
long size = ftell(fp);
rewind(fp);   // Reset to beginning
printf("File size: %ld bytes\n", size);
```

### rewind() — Reset to Beginning

```c
void rewind(FILE *fp);
// = fseek(fp, 0L, SEEK_SET) + clearerr(fp)
```

### Random Access Example — Updating Record n

```c
// Update the 3rd employee record (0-indexed)
int record_num = 2;
Employee emp;

FILE *fp = fopen("employees.dat", "rb+");
fseek(fp, record_num * sizeof(Employee), SEEK_SET);
fread(&emp, sizeof(Employee), 1, fp);

emp.salary += 5000;  // Give a raise

fseek(fp, record_num * sizeof(Employee), SEEK_SET);
fwrite(&emp, sizeof(Employee), 1, fp);
fclose(fp);
```

### Memory Diagram — File Position

```
Binary file (employees.dat):
┌─────────────────┬─────────────────┬─────────────────┐
│   Employee[0]   │   Employee[1]   │   Employee[2]   │
│   (56 bytes)    │   (56 bytes)    │   (56 bytes)    │
└─────────────────┴─────────────────┴─────────────────┘
 offset=0          offset=56         offset=112
                                     ^
                            fseek(fp, 2*56, SEEK_SET)
```

---

## 8. Error Handling

### EOF Concept

`EOF` is a macro defined as `-1` in `<stdio.h>`. It signals the end of file or an error condition. It is **not a character in the file** — it is a sentinel return value.

### Detecting End-of-File Correctly

```c
// WRONG: feof() only returns true AFTER a failed read
while (!feof(fp)) {
    ch = fgetc(fp);   // Last iteration reads garbage!
    process(ch);
}

// CORRECT: Check the return value of the read function
int ch;
while ((ch = fgetc(fp)) != EOF) {
    process(ch);
}
```

### File Opening Errors

```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {
    // errno is set automatically by fopen()
    perror("fopen");          // "fopen: No such file or directory"
    fprintf(stderr, "errno = %d\n", errno);
    exit(EXIT_FAILURE);
}
```

### Common errno Values for File Operations

| `errno` | Meaning |
|---------|---------|
| `ENOENT` | No such file or directory |
| `EACCES` | Permission denied |
| `EEXIST` | File already exists |
| `EMFILE` | Too many open files |
| `ENOSPC` | No space left on device |
| `EROFS`  | Read-only file system |

### Robust Error Handling Pattern

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void) {
    FILE *fp = NULL;
    char *buf = NULL;

    fp = fopen("data.txt", "r");
    if (!fp) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    buf = malloc(1024);
    if (!buf) {
        fclose(fp);
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    while (fgets(buf, 1024, fp)) {
        if (ferror(fp)) {
            fprintf(stderr, "Read error: %s\n", strerror(errno));
            break;
        }
        printf("%s", buf);
    }

    free(buf);
    fclose(fp);
    return EXIT_SUCCESS;
}
```

---

## 9. Advanced Topics

### Buffering

#### Fully Buffered I/O
- Data accumulates in buffer until full or `fflush()`/`fclose()` is called.
- Default for regular files.
- Fastest for throughput.

#### Line Buffered I/O
- Data is written on each newline.
- Default for `stdout` when connected to a terminal.
- `printf("hello\n")` → immediate terminal output.
- `printf("hello")` → may not appear until buffer is flushed.

#### Unbuffered I/O
- Every write goes directly to OS.
- Default for `stderr` (so error messages appear immediately even if program crashes).

```c
// Set buffer type manually:
setvbuf(fp, NULL, _IOFBF, 8192);  // Fully buffered, 8 KB buffer
setvbuf(fp, NULL, _IOLBF, 0);     // Line buffered
setvbuf(fp, NULL, _IONBF, 0);     // Unbuffered
```

### Temporary Files

```c
// tmpfile() — creates a temp file deleted automatically on fclose()
FILE *tmp = tmpfile();
if (!tmp) { perror("tmpfile"); return 1; }
fputs("temp data", tmp);
rewind(tmp);
// ... use tmp ...
fclose(tmp);   // File is deleted here automatically
```

```c
// tmpnam() — generates a unique temporary filename (use carefully)
char tmpname[L_tmpnam];
tmpnam(tmpname);
printf("Temp file: %s\n", tmpname);
// Note: tmpnam() has a TOCTOU race condition; prefer tmpfile() or mkstemp()
```

### File Locking Concepts

On Linux, use `flock()` or `fcntl()` for file locking:

```c
#include <sys/file.h>

int fd = fileno(fp);         // Get file descriptor from FILE*
flock(fd, LOCK_EX);          // Exclusive (write) lock
// ... critical section ...
flock(fd, LOCK_UN);          // Release lock
```

On Windows, use `LockFile()` / `UnlockFile()` from `<windows.h>`.

### Large File Handling

For files > 2 GB on 32-bit systems, use large file support:

```c
// Linux: compile with -D_FILE_OFFSET_BITS=64 or use explicit types
#define _FILE_OFFSET_BITS 64
#include <stdio.h>

FILE *fp = fopen("huge.dat", "rb");
fseeko(fp, offset, SEEK_SET);   // off_t version (64-bit)
off_t pos = ftello(fp);
```

### Performance Optimization

| Technique | Benefit |
|-----------|---------|
| Use large `fread()`/`fwrite()` blocks | Fewer system calls |
| Use `setvbuf()` with large buffer | Fewer OS I/O operations |
| Use binary mode for structured data | Avoid text conversion overhead |
| `mmap()` for random access on Linux | Maps file directly to memory |
| Avoid `fseek()` in loops | Seekable access is expensive |

---

## 10. Structures with Files

### Saving Structure Data

```c
typedef struct {
    int  id;
    char name[50];
    int  age;
    float gpa;
} Student;

void save_student(FILE *fp, Student *s) {
    fwrite(s, sizeof(Student), 1, fp);
}
```

### Reading Structure Data

```c
void load_students(const char *filename) {
    Student s;
    FILE *fp = fopen(filename, "rb");
    if (!fp) { perror("fopen"); return; }

    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("ID: %d | Name: %-20s | Age: %d | GPA: %.2f\n",
               s.id, s.name, s.age, s.gpa);
    }
    fclose(fp);
}
```

### Employee Database Example

```c
#include <stdio.h>
#include <string.h>

#define FILENAME "employees.dat"
#define MAX_NAME 50

typedef struct {
    int   id;
    char  name[MAX_NAME];
    char  dept[30];
    float salary;
} Employee;

// Add employee
void add_employee(Employee *emp) {
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) { perror("fopen"); return; }
    fwrite(emp, sizeof(Employee), 1, fp);
    fclose(fp);
    printf("Employee added.\n");
}

// Display all employees
void list_employees(void) {
    Employee emp;
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) { printf("No records found.\n"); return; }

    printf("%-5s %-20s %-15s %10s\n", "ID", "Name", "Dept", "Salary");
    printf("------------------------------------------------------\n");
    while (fread(&emp, sizeof(Employee), 1, fp) == 1)
        printf("%-5d %-20s %-15s %10.2f\n",
               emp.id, emp.name, emp.dept, emp.salary);
    fclose(fp);
}

// Search by ID
void search_employee(int id) {
    Employee emp;
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) { perror("fopen"); return; }

    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.id == id) {
            printf("Found: %d | %s | %s | %.2f\n",
                   emp.id, emp.name, emp.dept, emp.salary);
            fclose(fp);
            return;
        }
    }
    printf("Employee ID %d not found.\n", id);
    fclose(fp);
}

int main(void) {
    Employee e1 = {101, "Alice",   "Engineering", 85000};
    Employee e2 = {102, "Bob",     "Marketing",   72000};
    Employee e3 = {103, "Charlie", "Engineering", 91000};

    add_employee(&e1);
    add_employee(&e2);
    add_employee(&e3);

    list_employees();
    search_employee(102);
    return 0;
}
```

---

## 11. Dynamic Memory and Files

### Reading a File of Unknown Length

```c
#include <stdio.h>
#include <stdlib.h>

char *read_entire_file(const char *filename, long *out_size) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);

    char *buf = malloc(size + 1);
    if (!buf) { fclose(fp); return NULL; }

    size_t read = fread(buf, 1, size, fp);
    buf[read] = '\0';   // Null-terminate
    fclose(fp);

    if (out_size) *out_size = (long)read;
    return buf;   // Caller must free()
}

int main(void) {
    long size;
    char *content = read_entire_file("notes.txt", &size);
    if (!content) { perror("read_entire_file"); return 1; }

    printf("File (%ld bytes):\n%s\n", size, content);
    free(content);
    return 0;
}
```

### Dynamic Line Array

```c
// Read all lines into a dynamically-allocated array
char **lines = NULL;
int count = 0, capacity = 16;
lines = malloc(capacity * sizeof(char *));

FILE *fp = fopen("data.txt", "r");
char buf[1024];
while (fgets(buf, sizeof(buf), fp)) {
    if (count == capacity) {
        capacity *= 2;
        lines = realloc(lines, capacity * sizeof(char *));
    }
    lines[count] = strdup(buf);   // strdup allocates + copies
    count++;
}
fclose(fp);

// Use lines...
for (int i = 0; i < count; i++) {
    printf("%d: %s", i+1, lines[i]);
    free(lines[i]);
}
free(lines);
```

---

## 12. OS Concepts Related to Files

### File Descriptors

At the OS level, open files are identified by small non-negative integers called **file descriptors (fd)**:

| fd | Default | C Stream |
|----|---------|----------|
| 0 | Standard Input | `stdin` |
| 1 | Standard Output | `stdout` |
| 2 | Standard Error | `stderr` |
| 3+ | User-opened files | `FILE *fp` from `fopen()` |

`fopen()` internally calls the OS `open()` system call, which returns a file descriptor. The `FILE *` struct wraps this fd with buffering.

```c
#include <stdio.h>
int fd = fileno(fp);    // Get file descriptor from FILE*
FILE *fp2 = fdopen(fd, "r");  // Create FILE* from file descriptor
```

### Standard Streams

| Stream | C Name | fd | Purpose |
|--------|--------|----|---------|
| Standard Input | `stdin` | 0 | Read input from user or pipe |
| Standard Output | `stdout` | 1 | Normal program output |
| Standard Error | `stderr` | 2 | Error/diagnostic output |

### Relationship Between OS and C File Handling

```
C Code: fwrite(buf, 1, n, fp)
           │
           ▼
    C Library: Copy data to internal buffer
           │
      Buffer full or fflush()
           │
           ▼
    OS Kernel: write(fd, buf, n)  ← system call
           │
           ▼
    Page Cache (kernel buffer)
           │
      Kernel decides when
           │
           ▼
    Physical storage (disk/flash)
```

---

## 13. Embedded C and Linux File Concepts

### Configuration Files

```c
// Read INI-style config: key=value
void read_config(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) return;
    char line[128];
    while (fgets(line, sizeof(line), fp)) {
        char key[64], value[64];
        if (sscanf(line, "%63[^=]=%63s", key, value) == 2)
            printf("Key='%s' Value='%s'\n", key, value);
    }
    fclose(fp);
}
```

### Log Files

```c
// Thread-safe-style log write
void log_event(const char *logfile, const char *level, const char *msg) {
    FILE *fp = fopen(logfile, "a");
    if (!fp) return;
    // In production: add timestamp using time()
    fprintf(fp, "[%s] %s\n", level, msg);
    fflush(fp);   // Important for logs — write immediately
    fclose(fp);
}
```

### Linux /proc Filesystem

`/proc` is a virtual filesystem exposing kernel data as files:

```c
// Read CPU info
FILE *fp = fopen("/proc/cpuinfo", "r");
char line[256];
while (fgets(line, sizeof(line), fp)) {
    if (strncmp(line, "model name", 10) == 0) {
        printf("%s", line);
        break;
    }
}
fclose(fp);

// Read process memory usage
FILE *fp2 = fopen("/proc/self/status", "r");
while (fgets(line, sizeof(line), fp2)) {
    if (strncmp(line, "VmRSS", 5) == 0)
        printf("Memory: %s", line);
}
fclose(fp2);
```

### Linux /sys Filesystem

`/sys` exposes hardware/driver information:

```c
// Read GPIO value on embedded Linux
FILE *fp = fopen("/sys/class/gpio/gpio17/value", "r");
char val[4];
fgets(val, sizeof(val), fp);
printf("GPIO 17 = %s\n", val);
fclose(fp);

// Set GPIO
FILE *fp2 = fopen("/sys/class/gpio/gpio17/value", "w");
fputs("1", fp2);   // Drive HIGH
fclose(fp2);
```

### Driver Development Examples

In Linux kernel driver code (kernel space, not stdio):

```c
// User space: read from character device
FILE *fp = fopen("/dev/mydevice", "rb");
uint8_t buf[64];
fread(buf, 1, 64, fp);
fclose(fp);
```

### Embedded Data Logging Example

```c
typedef struct {
    uint32_t timestamp;
    float    temperature;
    float    pressure;
    uint8_t  status;
} SensorLog;

void log_sensor_data(const char *path, SensorLog *entry) {
    FILE *fp = fopen(path, "ab");
    if (!fp) return;
    fwrite(entry, sizeof(SensorLog), 1, fp);
    fclose(fp);
}

void dump_sensor_log(const char *path) {
    SensorLog entry;
    FILE *fp = fopen(path, "rb");
    if (!fp) return;
    while (fread(&entry, sizeof(SensorLog), 1, fp) == 1)
        printf("t=%u  temp=%.2f  pres=%.2f  status=%02X\n",
               entry.timestamp, entry.temperature,
               entry.pressure, entry.status);
    fclose(fp);
}
```

---

## 14. 30 Practical C Programs

---

### Beginner Programs (1–10)

---

#### Program 1: Create a File

**Problem:** Create a new text file and write a greeting to it.

**Algorithm:**
1. Open file in `"w"` mode.
2. Write text using `fprintf()`.
3. Close file.

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("hello.txt", "w");
    if (!fp) { perror("fopen"); return EXIT_FAILURE; }

    fprintf(fp, "Hello, File Handling!\n");
    fprintf(fp, "Created from C program.\n");

    fclose(fp);
    printf("File 'hello.txt' created successfully.\n");
    return EXIT_SUCCESS;
}
```

**Sample Output:**
```
File 'hello.txt' created successfully.
```
**File contents (hello.txt):**
```
Hello, File Handling!
Created from C program.
```
**Time Complexity:** O(1)  
**Interview Point:** Discuss what happens if disk is full — `fwrite()`/`fprintf()` returns < expected count; check `ferror()`.

---

#### Program 2: Write to a File

**Problem:** Accept user input and write it to a file.

**Algorithm:**
1. Open file in `"w"` mode.
2. Read lines from user until empty line.
3. Write each line with `fputs()`.
4. Close file.

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("input_data.txt", "w");
    if (!fp) { perror("fopen"); return 1; }

    char line[256];
    printf("Enter lines (empty line to stop):\n");
    while (fgets(line, sizeof(line), stdin)) {
        if (line[0] == '\n') break;
        fputs(line, fp);
    }

    fclose(fp);
    printf("Data written to 'input_data.txt'.\n");
    return 0;
}
```

**Sample Input:** `Hello World\nThis is C\n(empty line)`  
**Sample Output:** `Data written to 'input_data.txt'.`  
**Time Complexity:** O(n) where n = total characters  
**Interview Point:** Difference between `fputs()` and `fprintf()`.

---

#### Program 3: Read a File

**Problem:** Open and display the contents of a text file.

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("hello.txt", "r");
    if (!fp) { perror("fopen"); return 1; }

    char line[256];
    printf("--- File Contents ---\n");
    while (fgets(line, sizeof(line), fp) != NULL)
        printf("%s", line);
    printf("--- End of File ---\n");

    fclose(fp);
    return 0;
}
```

**Time Complexity:** O(n)  
**Interview Point:** Why use `fgets()` over `fscanf()` for reading lines? (`fgets()` is safer — won't overflow, handles spaces.)

---

#### Program 4: Copy a File

**Problem:** Copy the contents of one file to another.

**Algorithm:**
1. Open source in `"rb"`, destination in `"wb"`.
2. Read source in blocks.
3. Write each block to destination.
4. Close both files.

```c
#include <stdio.h>
#define BLOCK 4096

int main(void) {
    FILE *src = fopen("hello.txt", "rb");
    FILE *dst = fopen("copy.txt",  "wb");
    if (!src || !dst) { perror("fopen"); return 1; }

    char buf[BLOCK];
    size_t n;
    while ((n = fread(buf, 1, BLOCK, src)) > 0)
        fwrite(buf, 1, n, dst);

    fclose(src);
    fclose(dst);
    printf("File copied successfully.\n");
    return 0;
}
```

**Time Complexity:** O(n)  
**Interview Point:** Why binary mode for copy? To prevent newline translation corrupting binary files.

---

#### Program 5: Count Characters in a File

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("hello.txt", "r");
    if (!fp) { perror("fopen"); return 1; }

    long chars = 0;
    while (fgetc(fp) != EOF) chars++;

    fclose(fp);
    printf("Total characters: %ld\n", chars);
    return 0;
}
```

**Sample Output:** `Total characters: 44`  
**Interview Point:** Does `EOF` count as a character? No — EOF is a sentinel return value, not a byte.

---

#### Program 6: Count Words in a File

```c
#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *fp = fopen("hello.txt", "r");
    if (!fp) { perror("fopen"); return 1; }

    long words = 0;
    int in_word = 0, ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (isspace(ch)) { in_word = 0; }
        else if (!in_word) { in_word = 1; words++; }
    }

    fclose(fp);
    printf("Total words: %ld\n", words);
    return 0;
}
```

**Time Complexity:** O(n)

---

#### Program 7: Count Lines in a File

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("hello.txt", "r");
    if (!fp) { perror("fopen"); return 1; }

    long lines = 0;
    int ch;
    while ((ch = fgetc(fp)) != EOF)
        if (ch == '\n') lines++;

    fclose(fp);
    printf("Total lines: %ld\n", lines);
    return 0;
}
```

---

#### Program 8: Append to a File

```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("log.txt", "a");
    if (!fp) { perror("fopen"); return 1; }

    fprintf(fp, "New log entry: Operation completed.\n");
    fclose(fp);
    printf("Data appended to 'log.txt'.\n");
    return 0;
}
```

---

#### Program 9: Merge Two Files

**Problem:** Merge contents of file1.txt and file2.txt into merged.txt.

```c
#include <stdio.h>
#define BLOCK 1024

void copy_file(FILE *src, FILE *dst) {
    char buf[BLOCK];
    size_t n;
    while ((n = fread(buf, 1, BLOCK, src)) > 0)
        fwrite(buf, 1, n, dst);
}

int main(void) {
    FILE *f1  = fopen("file1.txt",  "rb");
    FILE *f2  = fopen("file2.txt",  "rb");
    FILE *out = fopen("merged.txt", "wb");

    if (!f1 || !f2 || !out) { perror("fopen"); return 1; }

    copy_file(f1, out);
    copy_file(f2, out);

    fclose(f1); fclose(f2); fclose(out);
    printf("Files merged into 'merged.txt'.\n");
    return 0;
}
```

---

#### Program 10: Reverse File Content

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("hello.txt", "rb");
    if (!fp) { perror("fopen"); return 1; }

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    char *buf = malloc(size);
    if (!buf) { fclose(fp); return 1; }

    for (long i = size - 1; i >= 0; i--) {
        fseek(fp, i, SEEK_SET);
        buf[size - 1 - i] = (char)fgetc(fp);
    }
    fclose(fp);

    FILE *out = fopen("reversed.txt", "wb");
    fwrite(buf, 1, size, out);
    fclose(out);
    free(buf);

    printf("Reversed file written to 'reversed.txt'.\n");
    return 0;
}
```

---

### Intermediate Programs (11–20)

---

#### Program 11: Student Record Management

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define FILENAME "students.dat"

typedef struct { int id; char name[50]; float gpa; } Student;

void add_student(void) {
    Student s;
    printf("ID: "); scanf("%d", &s.id);
    printf("Name: "); scanf("%49s", s.name);
    printf("GPA: "); scanf("%f", &s.gpa);
    FILE *fp = fopen(FILENAME, "ab");
    if (!fp) { perror("fopen"); return; }
    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("Student added.\n");
}

void list_students(void) {
    Student s;
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) { printf("No records.\n"); return; }
    printf("%-5s %-20s %5s\n", "ID", "Name", "GPA");
    printf("--------------------------------\n");
    while (fread(&s, sizeof(Student), 1, fp) == 1)
        printf("%-5d %-20s %5.2f\n", s.id, s.name, s.gpa);
    fclose(fp);
}

int main(void) {
    int choice;
    do {
        printf("\n1.Add  2.List  0.Exit: ");
        scanf("%d", &choice);
        if (choice == 1) add_student();
        else if (choice == 2) list_students();
    } while (choice != 0);
    return 0;
}
```

---

#### Program 12: Employee Record Management

*(See Section 10 for full implementation — extended with delete and update below.)*

```c
// Delete employee by ID (rewrite file without deleted record)
void delete_employee(int del_id) {
    Employee emp;
    FILE *fp  = fopen(FILENAME, "rb");
    FILE *tmp = fopen("_tmp.dat", "wb");
    if (!fp || !tmp) { perror("fopen"); return; }

    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        if (emp.id == del_id) { found = 1; continue; }
        fwrite(&emp, sizeof(Employee), 1, tmp);
    }
    fclose(fp); fclose(tmp);

    if (found) {
        remove(FILENAME);
        rename("_tmp.dat", FILENAME);
        printf("Employee %d deleted.\n", del_id);
    } else {
        remove("_tmp.dat");
        printf("ID not found.\n");
    }
}
```

---

#### Program 13: Search Records in a Binary File

```c
void search_student_by_name(const char *name) {
    Student s;
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) { perror("fopen"); return; }

    int found = 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (strncmp(s.name, name, 49) == 0) {
            printf("Found: ID=%d Name=%s GPA=%.2f\n", s.id, s.name, s.gpa);
            found = 1;
        }
    }
    if (!found) printf("No record found for '%s'.\n", name);
    fclose(fp);
}
```

---

#### Program 14: Update a Record Using Random Access

```c
void update_student_gpa(int id, float new_gpa) {
    Student s;
    FILE *fp = fopen("students.dat", "rb+");
    if (!fp) { perror("fopen"); return; }

    long offset = 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        if (s.id == id) {
            s.gpa = new_gpa;
            fseek(fp, offset, SEEK_SET);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("Updated student %d GPA to %.2f\n", id, new_gpa);
            fclose(fp);
            return;
        }
        offset += sizeof(Student);
    }
    printf("Student ID %d not found.\n", id);
    fclose(fp);
}
```

---

#### Program 15: Delete a Record from a Binary File

*(See Program 12 `delete_employee()` — same pattern)*

---

#### Program 16: Binary File Operations — Write/Read Array

```c
#include <stdio.h>

int main(void) {
    int data[] = {10, 20, 30, 40, 50};
    int n = 5;

    // Write
    FILE *fp = fopen("array.bin", "wb");
    if (!fp) { perror("fopen"); return 1; }
    fwrite(data, sizeof(int), n, fp);
    fclose(fp);

    // Read back
    int buf[5] = {0};
    fp = fopen("array.bin", "rb");
    fread(buf, sizeof(int), n, fp);
    fclose(fp);

    for (int i = 0; i < n; i++)
        printf("buf[%d] = %d\n", i, buf[i]);
    return 0;
}
```

---

#### Program 17: Random Access Records — Jump to nth Record

```c
void get_nth_employee(int n) {
    Employee emp;
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) { perror("fopen"); return; }

    if (fseek(fp, (long)(n - 1) * sizeof(Employee), SEEK_SET) != 0) {
        printf("Invalid record number.\n");
    } else if (fread(&emp, sizeof(Employee), 1, fp) == 1) {
        printf("Record %d: %d | %s | %.2f\n",
               n, emp.id, emp.name, emp.salary);
    } else {
        printf("Record %d does not exist.\n", n);
    }
    fclose(fp);
}
```

---

#### Program 18: File Comparison

```c
#include <stdio.h>

int main(void) {
    FILE *f1 = fopen("file1.txt", "rb");
    FILE *f2 = fopen("file2.txt", "rb");
    if (!f1 || !f2) { perror("fopen"); return 1; }

    int c1, c2, line = 1, col = 1, identical = 1;
    while (1) {
        c1 = fgetc(f1);
        c2 = fgetc(f2);
        if (c1 == EOF && c2 == EOF) break;
        if (c1 != c2) {
            printf("Differ at line %d, col %d: '%c' vs '%c'\n",
                   line, col, (c1==EOF?'?':(char)c1), (c2==EOF?'?':(char)c2));
            identical = 0;
            break;
        }
        if (c1 == '\n') { line++; col = 1; } else col++;
    }
    if (identical) printf("Files are identical.\n");
    fclose(f1); fclose(f2);
    return 0;
}
```

---

#### Program 19: Simple File Encryption (XOR)

```c
#include <stdio.h>
#define KEY 0x5A

void xor_file(const char *input, const char *output) {
    FILE *in  = fopen(input,  "rb");
    FILE *out = fopen(output, "wb");
    if (!in || !out) { perror("fopen"); return; }

    int ch;
    while ((ch = fgetc(in)) != EOF)
        fputc(ch ^ KEY, out);

    fclose(in); fclose(out);
    printf("Done: '%s' -> '%s'\n", input, output);
}

int main(void) {
    xor_file("plain.txt",   "encrypted.bin");  // Encrypt
    xor_file("encrypted.bin", "decrypted.txt"); // Decrypt
    return 0;
}
```

**Interview Point:** XOR encryption is symmetric — applying the same key twice restores original data. Not secure for production; use AES.

---

#### Program 20: Log Management (Rotate Log)

```c
#include <stdio.h>
#include <string.h>

#define LOG_FILE   "app.log"
#define MAX_LINES  100

void write_log(const char *msg) {
    FILE *fp = fopen(LOG_FILE, "a");
    if (!fp) return;
    fprintf(fp, "%s\n", msg);
    fclose(fp);
}

int count_lines(void) {
    FILE *fp = fopen(LOG_FILE, "r");
    if (!fp) return 0;
    int lines = 0; char buf[256];
    while (fgets(buf, sizeof(buf), fp)) lines++;
    fclose(fp);
    return lines;
}

void rotate_log(void) {
    rename(LOG_FILE, "app.log.1");
    printf("Log rotated to app.log.1\n");
}

int main(void) {
    for (int i = 1; i <= 5; i++) {
        char msg[64];
        snprintf(msg, sizeof(msg), "Event #%d occurred", i);
        write_log(msg);
        if (count_lines() >= MAX_LINES) rotate_log();
    }
    printf("Log has %d lines.\n", count_lines());
    return 0;
}
```

---

### Advanced Programs (21–30)

---

#### Program 21: Mini Database System

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DB_FILE "minidb.dat"
#define MAX_KEY 32
#define MAX_VAL 128

typedef struct { char key[MAX_KEY]; char value[MAX_VAL]; } Record;

void db_put(const char *key, const char *value) {
    Record r; strncpy(r.key, key, MAX_KEY-1); strncpy(r.value, value, MAX_VAL-1);
    FILE *fp = fopen(DB_FILE, "ab");
    fwrite(&r, sizeof(Record), 1, fp);
    fclose(fp);
}

const char *db_get(const char *key, char *out) {
    Record r; FILE *fp = fopen(DB_FILE, "rb");
    if (!fp) return NULL;
    while (fread(&r, sizeof(Record), 1, fp) == 1) {
        if (strncmp(r.key, key, MAX_KEY) == 0) {
            strncpy(out, r.value, MAX_VAL);
            fclose(fp); return out;
        }
    }
    fclose(fp); return NULL;
}

int main(void) {
    db_put("name",    "Alice");
    db_put("country", "Canada");
    db_put("role",    "Engineer");

    char val[MAX_VAL];
    if (db_get("country", val)) printf("country = %s\n", val);
    if (db_get("role",    val)) printf("role    = %s\n", val);
    return 0;
}
```

---

#### Program 22: Inventory Management

```c
#include <stdio.h>
#include <string.h>
#define INV_FILE "inventory.dat"

typedef struct {
    int   item_id;
    char  name[60];
    int   quantity;
    float price;
} Item;

void add_item(Item *it) {
    FILE *fp = fopen(INV_FILE, "ab");
    fwrite(it, sizeof(Item), 1, fp);
    fclose(fp);
}

void update_quantity(int id, int qty_change) {
    Item it; FILE *fp = fopen(INV_FILE, "rb+");
    if (!fp) return;
    long off = 0;
    while (fread(&it, sizeof(Item), 1, fp) == 1) {
        if (it.item_id == id) {
            it.quantity += qty_change;
            fseek(fp, off, SEEK_SET);
            fwrite(&it, sizeof(Item), 1, fp);
            break;
        }
        off += sizeof(Item);
    }
    fclose(fp);
}

void report(void) {
    Item it; FILE *fp = fopen(INV_FILE, "rb");
    if (!fp) { printf("No inventory.\n"); return; }
    printf("%-5s %-30s %8s %10s\n", "ID", "Name", "Qty", "Price");
    while (fread(&it, sizeof(Item), 1, fp) == 1)
        printf("%-5d %-30s %8d %10.2f\n",
               it.item_id, it.name, it.quantity, it.price);
    fclose(fp);
}

int main(void) {
    Item a = {1, "Resistor 10K", 500, 0.05f};
    Item b = {2, "LED Red",      1000, 0.10f};
    add_item(&a); add_item(&b);
    update_quantity(1, -50);  // Used 50 resistors
    report();
    return 0;
}
```

---

#### Program 23: Configuration File Parser (INI Format)

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ENTRIES 64

typedef struct { char key[64]; char value[128]; } ConfigEntry;

int parse_config(const char *path, ConfigEntry *entries, int max) {
    FILE *fp = fopen(path, "r");
    if (!fp) return -1;
    char line[256]; int count = 0;
    while (fgets(line, sizeof(line), fp) && count < max) {
        if (line[0] == '#' || line[0] == '\n' || line[0] == '[') continue;
        char *eq = strchr(line, '=');
        if (!eq) continue;
        *eq = '\0';
        char *key = line; char *val = eq + 1;
        val[strcspn(val, "\r\n")] = '\0';
        strncpy(entries[count].key,   key, 63);
        strncpy(entries[count].value, val, 127);
        count++;
    }
    fclose(fp);
    return count;
}

int main(void) {
    // Create sample config
    FILE *fp = fopen("app.ini", "w");
    fprintf(fp, "# App Config\nhost=localhost\nport=8080\ndebug=true\n");
    fclose(fp);

    ConfigEntry entries[MAX_ENTRIES];
    int n = parse_config("app.ini", entries, MAX_ENTRIES);
    for (int i = 0; i < n; i++)
        printf("  %s = %s\n", entries[i].key, entries[i].value);
    return 0;
}
```

---

#### Program 24: CSV File Processing

```c
#include <stdio.h>
#include <string.h>

void process_csv(const char *path) {
    FILE *fp = fopen(path, "r");
    if (!fp) { perror("fopen"); return; }

    char line[512];
    int row = 0;
    while (fgets(line, sizeof(line), fp)) {
        char *token = strtok(line, ",");
        int col = 0;
        printf("Row %d: ", row++);
        while (token) {
            token[strcspn(token, "\r\n")] = '\0';
            printf("[%s] ", token);
            token = strtok(NULL, ",");
            col++;
        }
        printf("\n");
    }
    fclose(fp);
}

int main(void) {
    FILE *fp = fopen("data.csv", "w");
    fprintf(fp, "Name,Age,City\nAlice,30,Toronto\nBob,25,London\n");
    fclose(fp);

    process_csv("data.csv");
    return 0;
}
```

---

#### Program 25: File Indexing — Build an Index of Line Offsets

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("large.txt", "r");
    if (!fp) { perror("fopen"); return 1; }

    // Count lines first
    int n = 0; char buf[1024];
    while (fgets(buf, sizeof(buf), fp)) n++;
    rewind(fp);

    long *offsets = malloc((n + 1) * sizeof(long));
    int idx = 0;
    offsets[idx++] = 0;

    while (fgets(buf, sizeof(buf), fp))
        offsets[idx++] = ftell(fp);

    printf("Index built for %d lines.\n", n);

    // Jump to line 3 directly
    int target = 2;  // 0-indexed
    if (target < n) {
        fseek(fp, offsets[target], SEEK_SET);
        fgets(buf, sizeof(buf), fp);
        printf("Line %d: %s", target + 1, buf);
    }

    free(offsets);
    fclose(fp);
    return 0;
}
```

---

#### Program 26: Large File Processing (Block-by-Block)

```c
#include <stdio.h>
#include <stdlib.h>
#define BLOCK_SIZE (64 * 1024)   // 64 KB blocks

int main(void) {
    FILE *in  = fopen("bigfile.bin", "rb");
    FILE *out = fopen("bigfile_copy.bin", "wb");
    if (!in || !out) { perror("fopen"); return 1; }

    char *buf = malloc(BLOCK_SIZE);
    if (!buf) { return 1; }

    size_t total = 0, n;
    while ((n = fread(buf, 1, BLOCK_SIZE, in)) > 0) {
        fwrite(buf, 1, n, out);
        total += n;
    }

    printf("Processed %zu bytes.\n", total);
    free(buf);
    fclose(in); fclose(out);
    return 0;
}
```

---

#### Program 27: Binary Serialization of Nested Structures

```c
#include <stdio.h>
#include <string.h>

typedef struct { float x, y, z; } Vec3;
typedef struct { int id; char tag[16]; Vec3 position; float mass; } PhysicsBody;

void serialize(const char *path, PhysicsBody *bodies, int n) {
    FILE *fp = fopen(path, "wb");
    fwrite(&n, sizeof(int), 1, fp);               // Write count header
    fwrite(bodies, sizeof(PhysicsBody), n, fp);
    fclose(fp);
}

int deserialize(const char *path, PhysicsBody **out) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return -1;
    int n;
    fread(&n, sizeof(int), 1, fp);
    *out = malloc(n * sizeof(PhysicsBody));
    fread(*out, sizeof(PhysicsBody), n, fp);
    fclose(fp);
    return n;
}

int main(void) {
    PhysicsBody bodies[] = {
        {1, "player",  {0.0f, 1.0f, 0.0f}, 80.0f},
        {2, "boulder", {5.0f, 0.0f, 3.0f}, 200.0f}
    };
    serialize("scene.bin", bodies, 2);

    PhysicsBody *loaded;
    int n = deserialize("scene.bin", &loaded);
    for (int i = 0; i < n; i++)
        printf("Body[%d]: tag=%s pos=(%.1f,%.1f,%.1f) mass=%.1f\n",
               loaded[i].id, loaded[i].tag,
               loaded[i].position.x, loaded[i].position.y, loaded[i].position.z,
               loaded[i].mass);
    free(loaded);
    return 0;
}
```

---

#### Program 28: Device Log Analyzer

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fp = fopen("/var/log/syslog", "r");   // Linux system log
    if (!fp) { fp = fopen("syslog_sample.txt", "r"); }
    if (!fp) { perror("fopen"); return 1; }

    char line[1024];
    int errors = 0, warnings = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, "error") || strstr(line, "ERROR"))   errors++;
        if (strstr(line, "warn")  || strstr(line, "WARNING")) warnings++;
    }
    printf("Errors: %d | Warnings: %d\n", errors, warnings);
    fclose(fp);
    return 0;
}
```

---

#### Program 29: Embedded Data Logger

*(Full implementation from Section 13 — extended with timestamp)*

```c
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#define LOG_PATH "sensor_log.bin"

typedef struct {
    uint32_t timestamp;
    float    temperature;
    float    humidity;
} SensorRecord;

void log_sensor(float temp, float hum) {
    SensorRecord r;
    r.timestamp   = (uint32_t)time(NULL);
    r.temperature = temp;
    r.humidity    = hum;
    FILE *fp = fopen(LOG_PATH, "ab");
    if (fp) { fwrite(&r, sizeof(SensorRecord), 1, fp); fclose(fp); }
}

void print_log(void) {
    SensorRecord r;
    FILE *fp = fopen(LOG_PATH, "rb");
    if (!fp) { printf("No log data.\n"); return; }
    printf("%-12s %-10s %-10s\n", "Timestamp", "Temp(C)", "Humidity(%)");
    while (fread(&r, sizeof(SensorRecord), 1, fp) == 1) {
        char ts[32]; time_t t = r.timestamp;
        strftime(ts, sizeof(ts), "%H:%M:%S", localtime(&t));
        printf("%-12s %-10.2f %-10.2f\n", ts, r.temperature, r.humidity);
    }
    fclose(fp);
}

int main(void) {
    log_sensor(23.5f, 60.1f);
    log_sensor(24.1f, 58.7f);
    log_sensor(22.8f, 63.4f);
    print_log();
    return 0;
}
```

---

#### Program 30: Firmware Metadata Reader

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Simulated firmware header (first 64 bytes of a .bin file)
typedef struct {
    char     magic[4];       // "FW\0\0"
    uint32_t version;        // e.g., 0x01020304 = v1.2.3.4
    uint32_t size;           // Total firmware size in bytes
    uint32_t crc32;          // CRC32 checksum
    char     device[20];     // Target device name
    uint8_t  reserved[32];   // Reserved for future use
} FirmwareHeader;

void create_sample_firmware(void) {
    FirmwareHeader hdr = {
        .magic   = {'F','W',0,0},
        .version = 0x01020304,
        .size    = 65536,
        .crc32   = 0xDEADBEEF,
        .device  = "STM32F4xx"
    };
    FILE *fp = fopen("firmware.bin", "wb");
    fwrite(&hdr, sizeof(FirmwareHeader), 1, fp);
    fclose(fp);
}

void read_firmware_metadata(const char *path) {
    FirmwareHeader hdr;
    FILE *fp = fopen(path, "rb");
    if (!fp) { perror("fopen"); return; }

    if (fread(&hdr, sizeof(FirmwareHeader), 1, fp) != 1) {
        printf("Failed to read header.\n");
        fclose(fp); return;
    }

    if (strncmp(hdr.magic, "FW", 2) != 0) {
        printf("Invalid firmware file!\n");
        fclose(fp); return;
    }

    printf("=== Firmware Metadata ===\n");
    printf("Version : %d.%d.%d.%d\n",
           (hdr.version >> 24) & 0xFF, (hdr.version >> 16) & 0xFF,
           (hdr.version >> 8)  & 0xFF,  hdr.version & 0xFF);
    printf("Size    : %u bytes\n", hdr.size);
    printf("CRC32   : 0x%08X\n", hdr.crc32);
    printf("Device  : %s\n", hdr.device);

    fclose(fp);
}

int main(void) {
    create_sample_firmware();
    read_firmware_metadata("firmware.bin");
    return 0;
}
```

**Sample Output:**
```
=== Firmware Metadata ===
Version : 1.2.3.4
Size    : 65536 bytes
CRC32   : 0xDEADBEEF
Device  : STM32F4xx
```

---

## 15. 50+ Interview Questions & Answers

### Basic Level

**Q1: What is the return type of `fopen()`?**  
A: `FILE *`. Returns `NULL` if the file cannot be opened.

**Q2: What is the difference between `fgetc()` and `getc()`?**  
A: `fgetc()` is always a function. `getc()` may be implemented as a macro. Both read one character.

**Q3: How do you check if a file exists without modifying it?**  
A: Use `fopen()` with `"r"` mode and check if the return is not `NULL`. Close immediately if it is.

**Q4: What does `rewind()` do?**  
A: Moves the file position indicator to the beginning of the file and clears the error and EOF flags.

**Q5: What is EOF and what is its value?**  
A: `EOF` is a macro (typically `-1`) indicating end-of-file or an error from read functions.

**Q6: How do you delete a file in C?**  
A: Use `remove("filename")`. Returns 0 on success.

**Q7: What is the purpose of `fflush()`?**  
A: Forces any buffered unwritten data to be written to the OS/disk. Critical for ensuring data persistence.

**Q8: What happens if you call `fclose()` twice on the same pointer?**  
A: Undefined behavior — may crash or corrupt data. Always set `fp = NULL` after `fclose()`.

**Q9: What is the difference between `"r"` and `"r+"` mode?**  
A: `"r"` is read-only; `"r+"` allows both reading and writing without truncating.

**Q10: What function gives the size of a file?**  
A: No direct function. Use `fseek(fp, 0, SEEK_END)` followed by `ftell(fp)`.

---

### Intermediate Level

**Q11: Why should you use binary mode for writing structures?**  
A: To avoid newline translation on Windows (`\n` → `\r\n`) and to write raw bytes without any character conversion.

**Q12: What is the problem with using `while (!feof(fp))`?**  
A: `feof()` returns true only *after* a failed read, so the loop body executes one extra time. Always test the read function's return value directly.

**Q13: How do you update a specific record in a binary file without rewriting the whole file?**  
A: Use `fseek()` to position to the record offset (`n * sizeof(Record)`), then `fwrite()` the updated record. Open in `"rb+"` mode.

**Q14: Explain the difference between `fwrite()` and `write()` (POSIX).**  
A: `fwrite()` is C standard library (buffered). `write()` is a POSIX system call (unbuffered, kernel level). `fwrite()` calls `write()` internally when flushing.

**Q15: What is internal buffering and why does it matter?**  
A: The C library holds data in a RAM buffer before writing to disk. This reduces system calls and improves performance. It also means data may not reach disk until `fflush()` or `fclose()`.

**Q16: How do you get a file descriptor from a `FILE *`?**  
A: `int fd = fileno(fp);`

**Q17: What is the SEEK_END anchor in `fseek()`?**  
A: Positions relative to the end of the file. Negative offsets move backward from the end.

**Q18: Can you use `fprintf()` and `fwrite()` on the same file?**  
A: Yes, but avoid mixing them carelessly. `fprintf()` is text-oriented; `fwrite()` is binary. On text files mixing is fine; on binary files, `fprintf()` may insert unwanted newline translations.

**Q19: What does `clearerr()` do?**  
A: Clears the EOF and error flags for a stream, allowing continued use after an error.

**Q20: What is `BUFSIZ`?**  
A: A macro defined in `<stdio.h>` for the default buffer size used by `setbuf()` and the C library (commonly 8192 bytes).

**Q21: How do you redirect `stdout` to a file in C?**  
A: `freopen("out.txt", "w", stdout);` — after this, all `printf()` output goes to `out.txt`.

**Q22: What is the difference between `fputs()` and `fprintf(fp, "%s", str)`?**  
A: `fputs()` is simpler (no formatting) and slightly faster. `fprintf()` supports format specifiers.

**Q23: How do you determine if an error occurred vs. EOF after `fgets()` returns NULL?**  
A: Check `ferror(fp)` for an error; check `feof(fp)` for EOF.

**Q24: What is the return value of `fread()` if the file ends mid-block?**  
A: It returns the number of *complete* items read (could be 0 if the file has fewer than `size` bytes remaining). Check `feof()` and `ferror()` to distinguish.

**Q25: Explain file position after `fopen()` in `"a"` mode.**  
A: Initially positioned at end-of-file (implementation-specific), but all writes are forced to the end regardless of `fseek()`.

---

### Advanced Level

**Q26: Explain the relationship between buffered and unbuffered I/O in terms of system calls.**  
A: Buffered I/O (stdio) accumulates data in user-space RAM, reducing `write()` system calls. Unbuffered I/O calls `write()` for every operation. System calls are expensive (context switch); buffering reduces their frequency dramatically.

**Q27: What is a file descriptor leak and how do you prevent it?**  
A: A file descriptor leak occurs when a file is opened but never closed. Every process has a maximum fd limit (1024 on many Linux systems). Prevention: always pair `fopen()` with `fclose()`, use `goto` cleanup patterns in C.

**Q28: How does `mmap()` compare to `fread()` for file access on Linux?**  
A: `mmap()` maps file pages directly into virtual address space — no user-space copy. Ideal for large files with random access. `fread()` requires copying kernel page cache → user buffer. `mmap()` is faster for random access; `fread()` with large blocks is better for sequential reads.

**Q29: Explain structure alignment issues in binary files.**  
A: Compilers add padding to align struct members. A struct compiled with different compilers or different alignment settings may produce different binary layouts. Use `#pragma pack(1)` or `__attribute__((packed))` to eliminate padding for binary file portability.

```c
#pragma pack(push, 1)
typedef struct { char a; int b; char c; } Packed;  // 6 bytes
#pragma pack(pop)

typedef struct { char a; int b; char c; } Normal;   // 12 bytes (typical)
```

**Q30: What is `tmpfile()` and why is it safer than `tmpnam()`?**  
A: `tmpfile()` creates and opens a temp file atomically — no window for a race condition. `tmpnam()` only generates a name; another process could create that file before you open it (TOCTOU vulnerability). Prefer `tmpfile()` or POSIX `mkstemp()`.

**Q31: How do you implement a robust file write that ensures data is on disk?**  
A: `fwrite()` → `fflush()` → `fsync(fileno(fp))`. `fflush()` moves data from C library buffer to kernel buffer. `fsync()` forces kernel buffer to physical storage.

**Q32: What happens to buffered data if a program crashes (SIGSEGV)?**  
A: Buffered but not flushed data is lost. `stderr` (unbuffered) output survives; `stdout` (fully buffered) output may not. This is why error messages should go to `stderr`.

**Q33: How do you handle binary files across little-endian and big-endian systems?**  
A: Serialize multi-byte integers in a defined byte order (e.g., little-endian) and use `htonl()`/`ntohl()` or manual byte-swapping when reading on a different-endian system.

---

### Embedded C Interviews

**Q34: How do you open a serial port device file in C on Linux?**  
A: `FILE *fp = fopen("/dev/ttyS0", "rw");` or use POSIX `open()` with `O_RDWR | O_NOCTTY` for proper terminal configuration.

**Q35: What is the role of `/proc/sys/vm/dirty_writeback_centisecs`?**  
A: Controls how often (in centiseconds) kernel flushes dirty pages to disk. Relevant for embedded systems where you need deterministic write timing.

**Q36: Why is `fflush()` critical in embedded data loggers?**  
A: Embedded systems may lose power suddenly. Without `fflush()`, buffered sensor data in RAM is lost. On power failure, only already-flushed data survives.

**Q37: How would you write a firmware update routine that reads a binary file?**  
A: Open file in `"rb"`, use `fread()` in blocks matching flash page size, erase flash page, write block, verify CRC. Always verify before jumping to new firmware.

**Q38: What is a device file and how does C interact with it?**  
A: Device files (`/dev/ttyS0`, `/dev/spidev0.0`) are kernel interfaces that look like files. You can `open()`/`read()`/`write()` them using standard file functions to communicate with hardware.

---

### Linux System Programming Interviews

**Q39: What is the difference between a file stream (FILE*) and a file descriptor (int fd)?**  
A: `FILE *` is a C library abstraction with buffering. `fd` (file descriptor) is a kernel-level integer handle. `FILE *` wraps `fd` with a user-space buffer and functions like `fprintf()`.

**Q40: How does `dup2()` relate to file I/O in C?**  
A: `dup2(oldfd, newfd)` duplicates `oldfd` to `newfd`. Used to redirect stdin/stdout/stderr at the fd level. Example: `dup2(filefd, STDOUT_FILENO)` redirects stdout to a file.

**Q41: What is the `/proc/self/fd/` directory?**  
A: Contains symbolic links for every open file descriptor of the current process. Useful for debugging fd leaks.

**Q42: How do you atomically create a file only if it doesn't exist?**  
A: Use `open()` with `O_CREAT | O_EXCL` flags. This is atomic at the kernel level; `fopen()` with `"w"` is not atomic.

---

### Linux Device Driver Interviews

**Q43: How does a user-space C program communicate with a character device driver?**  
A: Open `/dev/mydevice` → `read()`/`write()`/`ioctl()`. The kernel driver implements `file_operations` (`.open`, `.read`, `.write`, `.ioctl`).

**Q44: What is `sysfs` and how do you read/write it from C?**  
A: `sysfs` (mounted at `/sys`) exposes kernel object attributes as files. Read/write like normal files: `fopen("/sys/class/gpio/gpio17/value", "w")`.

**Q45: What is the relationship between `fread()` and the kernel's `read()` system call?**  
A: `fread()` calls `read()` when its buffer needs refilling. Multiple `fread()` calls may map to a single `read()` system call.

---

## 16. Tricky Interview Questions

**Q: What is the difference between text and binary files? Will reading a binary file in text mode cause problems?**  
A: In text mode, on Windows, `\r\n` sequences are converted to `\n` on read and `\n` to `\r\n` on write. For binary files (images, executables), this translation corrupts data. On Linux, text and binary modes are identical — but always use binary mode for non-text data for portability.

---

**Q: How does `"a+"` mode behave for reads and writes?**  
A: Reads can occur from anywhere (position the pointer with `fseek()`). Writes always go to end-of-file, regardless of the current position indicator. The pointer is *moved* to EOF before each write.

---

**Q: If `ftell()` returns 100 after writing 10 bytes, what does that mean?**  
A: The file position is 100 bytes from the beginning. You wrote starting at offset 90. `ftell()` reflects the *current* position, not the number of bytes written in this call.

---

**Q: What is the EOF misconception?**  
A: Many developers think `feof()` becomes true *before* reading the last byte. In reality, EOF is set only *after* a read attempt fails because no bytes remain. This causes the classic "double last line" bug when using `while (!feof(fp))`.

---

**Q: How does buffering affect `fprintf()` output order vs. `write()`?**  
A: `fprintf()` output may appear out of order relative to `write()` calls if the `FILE*` buffer hasn't been flushed. Mixing `FILE*` functions with raw `write()` on the same fd requires careful `fflush()` management.

---

**Q: What is the result of `fread(buf, 5, 3, fp)` on a 12-byte file?**  
A: `fread()` attempts to read 3 items of 5 bytes each (15 bytes total). Only 12 bytes exist, so 2 complete items (10 bytes) are read. Returns 2. The remaining 2 bytes are left unread. `feof()` is NOT set until another read is attempted.

---

**Q: Does `fseek()` with `SEEK_END` work on all file types?**  
A: Not on all streams. It is defined for binary files. For text files, the result of `fseek(fp, offset, SEEK_END)` where `offset != 0` is implementation-defined. Use `SEEK_SET` with a previously `ftell()`-captured offset for text files.

---

**Q: Two processes open the same file with `"a"` mode. Is the output interleaved or appended correctly?**  
A: On Linux/POSIX, `O_APPEND` (which underlies `"a"` mode) uses an atomic seek-and-write at the kernel level, so concurrent appends from multiple processes are safe — each write lands at the end. On Windows, behavior may differ.

---

**Q: Why can struct padding break binary file compatibility between compilers?**  
A: Compilers may insert different amounts of padding to satisfy alignment requirements. A struct with `char` + `int` may be 8 bytes on one compiler (3 bytes padding) or 5 bytes with `#pragma pack(1)`. Reading a file written by a packed struct with an unpacked reader produces garbage.

---

## 17. Real-World Case Studies

### Case Study 1: Banking Application

**Scenario:** Store and retrieve account transactions.

**Design:**
- Each account has a binary file: `acc_1001.dat`
- Records: `{timestamp, type, amount, balance_after}`
- Append transactions in `"ab"` mode.
- Generate statements by reading all records.
- Use `flock()` for concurrent access from multiple terminals.

**Key considerations:**
- Never open in `"wb"` — that would truncate all history!
- Use `fsync()` after each transaction to ensure durability.
- Checksum each record to detect corruption.

---

### Case Study 2: Student Management System

**Scenario:** Manage 10,000 student records with fast search.

**Design:**
- Binary file: `students.dat` (fixed-size records → random access by student ID).
- Index file: `students.idx` (sorted array of `{id, offset}` for binary search).
- Insert: append to `.dat`, insert into sorted `.idx`.
- Lookup: binary search `.idx` → `fseek()` to offset in `.dat`.

**Benefit:** O(log n) search instead of O(n) linear scan.

---

### Case Study 3: Embedded Data Logger

**Scenario:** Raspberry Pi reads temperature every 10 seconds and logs it.

**Design:**
- Binary log file: `sensor.log` with fixed-size `SensorRecord` entries.
- Rotate log when file exceeds 1 MB.
- On power loss: only current unflushed buffer entry may be lost (at most 10 seconds of data).
- Watchdog timer restarts logging automatically.

---

### Case Study 4: Linux Log Analyzer

**Scenario:** Parse `/var/log/auth.log` to detect brute-force SSH attacks.

**Design:**
- Read file line by line with `fgets()`.
- Count "Failed password" occurrences per source IP using a hash map.
- IPs with > 10 failures in 60 seconds → alert.
- Tail-follow mode: remember last `ftell()` position, sleep, seek back, read new lines.

---

### Case Study 5: Inventory Management System

**Scenario:** Retail store tracks ~50,000 SKUs with real-time stock updates.

**Design:**
- Binary file with fixed-size `Item` structs.
- In-memory index maps SKU→file offset at startup.
- Sales update: find item offset → `fseek()` → read → update quantity → `fseek()` back → `fwrite()`.
- Daily backup: copy binary file to timestamped `.bak`.

---

## 18. Common Mistakes

### 1. Forgetting fclose()
```c
// WRONG
FILE *fp = fopen("data.txt", "w");
fprintf(fp, "data");
// fp never closed — buffer may not be flushed!

// CORRECT
FILE *fp = fopen("data.txt", "w");
fprintf(fp, "data");
fclose(fp);
```

### 2. Incorrect fopen Modes
```c
// WRONG — opens for reading, not writing
FILE *fp = fopen("out.txt", "r");
fprintf(fp, "data");   // Undefined behavior!

// CORRECT
FILE *fp = fopen("out.txt", "w");
fprintf(fp, "data");
fclose(fp);
```

### 3. Misuse of EOF
```c
// WRONG — reads one extra time
while (!feof(fp)) {
    int ch = fgetc(fp);
    process(ch);  // ch = EOF on last iteration!
}

// CORRECT
int ch;
while ((ch = fgetc(fp)) != EOF)
    process(ch);
```

### 4. Buffer Overflow
```c
// WRONG — fscanf can overflow buf
char buf[10];
fscanf(fp, "%s", buf);   // "ThisIsVeryLongToken" → overflow!

// CORRECT
fscanf(fp, "%9s", buf);  // Limit to 9 chars + null terminator
// Or use fgets:
fgets(buf, sizeof(buf), fp);
```

### 5. fread()/fwrite() Mistakes
```c
// WRONG — arguments swapped
fread(buf, count, size, fp);   // Should be: fread(buf, size, count, fp)

// CORRECT
fread(buf, sizeof(Element), count, fp);
// Also: ALWAYS check return value:
size_t n = fread(buf, sizeof(int), 10, fp);
if (n < 10) { /* handle short read */ }
```

### 6. File Pointer Errors
```c
// WRONG — using FILE* after fclose
fclose(fp);
fprintf(fp, "oops");   // Undefined behavior!

// CORRECT
fclose(fp);
fp = NULL;   // Nullify immediately
```

### 7. Not Handling NULL from fopen
```c
// WRONG
FILE *fp = fopen("missing.txt", "r");
fgets(buf, 100, fp);   // CRASH — fp is NULL!

// CORRECT
FILE *fp = fopen("missing.txt", "r");
if (!fp) { perror("fopen"); return EXIT_FAILURE; }
```

---

## 19. Best Practices

### Secure File Handling

| Practice | Reason |
|----------|--------|
| Always validate `fopen()` return | Prevents NULL dereference crashes |
| Limit file path input length | Prevents buffer overflows |
| Use `%9s` not `%s` in `fscanf()` | Prevents input buffer overflow |
| Validate file content before use | Prevents injection attacks |
| Use `mkstemp()` not `tmpnam()` | Prevents TOCTOU race conditions |
| Check write return values | Detects disk-full conditions |

### Error Checking Pattern
```c
FILE *fp = fopen(path, "wb");
if (!fp) { perror("fopen"); return -1; }

size_t written = fwrite(data, sizeof(*data), count, fp);
if (written != count) {
    fprintf(stderr, "Write error: %s\n", strerror(errno));
    fclose(fp);
    return -1;
}

if (fclose(fp) != 0) {
    perror("fclose");  // fclose can fail too! (e.g., disk full on flush)
    return -1;
}
```

### Resource Management (goto cleanup pattern)
```c
int process_file(const char *path) {
    FILE *fp = NULL;
    char *buf = NULL;
    int   ret = -1;

    fp = fopen(path, "r");
    if (!fp) { perror("fopen"); goto cleanup; }

    buf = malloc(4096);
    if (!buf) { goto cleanup; }

    // ... do work ...
    ret = 0;   // Success

cleanup:
    free(buf);
    if (fp) fclose(fp);
    return ret;
}
```

### Portable Code Development
- Always use binary mode (`"rb"`/`"wb"`) for non-text data.
- Use `sizeof()` instead of hardcoded sizes.
- Avoid relying on struct layout — use `#pragma pack` or serialization.
- Use `int64_t` / `uint32_t` from `<stdint.h>` for binary file fields.

### Performance Optimization
- Read/write in large blocks (4 KB–64 KB) to minimize system calls.
- Use `setvbuf()` to increase buffer size for sequential large files.
- Use `mmap()` (Linux) for large files with random access patterns.
- Pre-allocate file space with `posix_fallocate()` to avoid fragmentation.

---

## 20. Memory Diagrams & Flowcharts

### File I/O Architecture Diagram

```
┌─────────────────────────────────────────────────────┐
│                  Your C Program                     │
│  ┌──────────┐   ┌──────────┐   ┌──────────────────┐ │
│  │ FILE *fp │──▶│  Buffer  │──▶│ stdio Functions  │ │
│  │  (heap)  │   │ (8 KB)   │   │ fread/fwrite etc │ │
│  └──────────┘   └──────────┘   └─────────┬────────┘ │
└──────────────────────────────────────────┼──────────┘
                                           │ System Call
                             ┌─────────────▼────────────┐
                             │       OS Kernel           │
                             │  ┌──────────────────────┐ │
                             │  │   Page Cache (RAM)   │ │
                             │  └──────────┬───────────┘ │
                             │             │ I/O Request  │
                             └─────────────┼─────────────┘
                                           │
                             ┌─────────────▼────────────┐
                             │   Physical Storage        │
                             │  (HDD / SSD / Flash)      │
                             └──────────────────────────┘
```

### fopen() Flowchart

```
fopen(path, mode)
      │
      ▼
 Does file exist?
  ├─ "r"/"r+": YES required → NO? → return NULL
  ├─ "w"/"w+": NO: create, YES: truncate
  └─ "a"/"a+": NO: create, YES: preserve
      │
      ▼
  OS open() system call → get file descriptor (fd)
      │
      ▼
  Allocate FILE struct in heap
      │
      ▼
  Allocate I/O buffer (BUFSIZ bytes)
      │
      ▼
  Return FILE* pointer
```

### fseek() / ftell() Memory Diagram

```
Binary File: employees.dat
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
│ Record 0  │ Record 1  │ Record 2  │ ...
│ (56 bytes)│ (56 bytes)│ (56 bytes)│
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
 ^0          ^56         ^112        ^168

fseek(fp, 2 * 56, SEEK_SET)  →  position = 112
ftell(fp)                    →  returns 112
fread(&emp, 56, 1, fp)       →  reads Record 2, position = 168
```

### Buffered Write Flowchart

```
fwrite(data, size, count, fp)
        │
        ▼
  Fit in buffer?
  ├─ YES → Copy to buffer, update buffer pointer
  └─ NO  → Flush existing buffer via write() syscall
             then copy new data to buffer (or write directly if large)
        │
fflush(fp) / fclose(fp)
        │
        ▼
  write() system call
        │
        ▼
  Kernel Page Cache updated
        │
fsync(fd) (optional but recommended for critical data)
        │
        ▼
  Physical disk write
```

---

## 21. Learning & Interview Preparation Roadmap

### Beginner (0–1 year)

**Topics to master:**
- [ ] fopen(), fclose(), fprintf(), fscanf()
- [ ] fgetc(), fputc(), fgets(), fputs()
- [ ] All file modes (r, w, a, r+, w+, a+)
- [ ] Error checking with NULL and perror()
- [ ] Text file read/write/append

**Suggested programs:** Programs 1–10 from this guide  
**Time:** 2–4 weeks

---

### Intermediate (1–3 years)

**Topics to master:**
- [ ] Binary file operations (fread/fwrite with structs)
- [ ] File positioning (fseek, ftell, rewind)
- [ ] Random access database patterns
- [ ] Error handling (ferror, feof, clearerr)
- [ ] Buffering concepts (setvbuf, fflush)
- [ ] tmpfile(), remove(), rename()

**Suggested programs:** Programs 11–20 from this guide  
**Time:** 1–2 months

---

### Experienced (3–5 years)

**Topics to master:**
- [ ] Large file handling (fseeko, ftello, 64-bit offsets)
- [ ] File locking (flock, fcntl)
- [ ] Dynamic reading (malloc + fread for unknown-size files)
- [ ] Performance tuning (block sizes, setvbuf)
- [ ] Serialization and deserialization
- [ ] Temporary file security (mkstemp vs tmpnam)

**Suggested programs:** Programs 21–30 from this guide  
**Time:** 2–3 months

---

### Embedded Engineers

**Focus areas:**
- [ ] Binary file I/O for sensor data logging
- [ ] Reading/writing to `/sys` and `/proc` on embedded Linux
- [ ] Firmware binary file reading (header validation, CRC checking)
- [ ] Flash storage constraints (write alignment, wear leveling awareness)
- [ ] Power-loss-safe logging (fflush after each record)
- [ ] Fixed-size struct serialization for flash/EEPROM backup

**Key programs:** 24, 27, 29, 30

---

### Linux Developers

**Focus areas:**
- [ ] File descriptors vs. FILE streams (fileno, fdopen)
- [ ] `/proc` and `/sys` filesystem reading
- [ ] POSIX file locking (fcntl LOCK_EX)
- [ ] Atomic file operations (O_CREAT | O_EXCL)
- [ ] `mmap()` for performance-critical file access
- [ ] Redirecting stdin/stdout/stderr with `freopen()`

**Key programs:** 23, 24, 25, 28

---

### System Programmers

**Focus areas:**
- [ ] Deep understanding of buffering layers
- [ ] fsync() / fdatasync() for durability guarantees
- [ ] posix_fallocate() for pre-allocating space
- [ ] Sendfile() for zero-copy file transfers
- [ ] File system internals (inodes, block allocation)
- [ ] Signal safety of file I/O functions

---

### Summary Table

| Level | Key Functions | Key Programs |
|-------|--------------|--------------|
| Beginner | fopen, fclose, fprintf, fgetc, fgets | 1–10 |
| Intermediate | fread, fwrite, fseek, ftell, ferror | 11–20 |
| Advanced | fseeko, flock, mkstemp, setvbuf, mmap | 21–30 |
| Embedded | fflush, fread binary, /sys writes | 29, 30 |
| Linux | fileno, fdopen, freopen, /proc reads | 28, 25 |

---

*End of File Handling in C — Complete Training Manual*  
*Cover: Theory · Programs · Interview Q&A · Embedded · Linux · Best Practices*
