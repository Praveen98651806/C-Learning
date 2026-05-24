# ⚙️ Setup Guide for Windows

> Get your C development environment ready on Windows

---

## Option 1: Visual Studio Code (Recommended)

### Step 1: Install GCC Compiler

#### For Windows:

1. **Download MinGW-w64:**
   - Visit: https://www.mingw-w64.org/
   - Click "Downloads"
   - Choose "MinGW-W64-builds" or "Online Installer"

2. **Or use Chocolatey (Easier):**
   ```powershell
   # Open PowerShell as Administrator
   choco install mingw
   ```

3. **Verify Installation:**
   ```powershell
   gcc --version
   gdb --version
   ```

### Step 2: Install VS Code

1. Download from: https://code.visualstudio.com/
2. Install and open VS Code

### Step 3: Install VS Code Extensions

1. Open Extensions (Ctrl+Shift+X)
2. Install:
   - **C/C++** by Microsoft
   - **Code Runner** by Jun Han
   - **Debugger for C** (optional)

### Step 4: Configure VS Code

1. Create `.vscode/tasks.json` in your workspace:

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "compile C",
            "type": "shell",
            "command": "gcc",
            "args": [
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}.exe",
                "${file}",
                "-Wall",
                "-g"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"],
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": false,
                "panel": "shared"
            }
        },
        {
            "label": "run C program",
            "type": "shell",
            "command": "${fileDirname}/${fileBasenameNoExtension}.exe",
            "dependsOn": "compile C",
            "group": {
                "kind": "test",
                "isDefault": true
            },
            "presentation": {
                "echo": true,
                "reveal": "always",
                "focus": true,
                "panel": "new"
            }
        }
    ]
}
```

2. Create `.vscode/launch.json` for debugging:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "C Debug",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "compile C"
        }
    ]
}
```

---

## Option 2: Code::Blocks (Alternative)

1. Download from: http://www.codeblocks.org/
2. Install (includes MinGW)
3. Create new project
4. Write code and compile!

---

## Option 3: Online Compilers (Quick Testing)

- **Repl.it**: https://repl.it/languages/c
- **Ideone**: https://ideone.com/
- **OnlineGDB**: https://www.onlinegdb.com/

---

## How to Compile and Run

### Via Terminal

```powershell
# Navigate to your C-Learning folder
cd C:\Users\9fu97v\Documents\Study\C-Learning\01_Fundamentals

# Compile
gcc -o calculator.exe 01_calculator.c

# Run
.\calculator.exe

# With warnings
gcc -Wall -o calculator.exe 01_calculator.c
```

### Via VS Code

1. Open any `.c` file
2. Press `Ctrl+Shift+B` to compile
3. Press `Ctrl+Shift+D` to debug (if configured)

---

## Commands You'll Use Often

```powershell
# Compile
gcc -o program.exe program.c

# Compile with all warnings
gcc -Wall -o program.exe program.c

# Compile with debugging info
gcc -g -o program.exe program.c

# Run program
.\program.exe

# Run with input redirection
.\program.exe < input.txt

# Compile multiple files
gcc -o program.exe file1.c file2.c file3.c

# Valgrind (memory leak detection) - requires installation
valgrind ./program

# GDB debugging
gdb program.exe
```

---

## GDB Debugging Quick Reference

```bash
# Start GDB
gdb program.exe

# Useful commands inside GDB:
(gdb) run                  # Run program
(gdb) run < input.txt      # Run with input
(gdb) break main           # Set breakpoint at main
(gdb) break filename.c:10  # Set breakpoint at line 10
(gdb) continue             # Continue execution
(gdb) step                 # Step into function
(gdb) next                 # Step over function
(gdb) print variable_name  # Print variable value
(gdb) list                 # List source code
(gdb) quit                 # Quit debugger
```

---

## Project Structure After Setup

```
C:\Users\9fu97v\Documents\Study\C-Learning\
├── ROADMAP.md
├── HOW_TO_STUDY.md
├── PROGRESS_TRACKER.md
│
├── 01_Fundamentals\
│   ├── THEORY.md
│   ├── EXERCISES.md
│   ├── 01_calculator.c
│   ├── 01_calculator.exe (after compilation)
│   └── ...more examples
│
├── 02_Functions_Scope\
│   └── ...
│
└── ...more folders
```

---

## Troubleshooting

### Error: "gcc is not recognized"

**Solution:**
1. Check if MinGW is installed: `gcc --version`
2. If not, install MinGW-w64
3. Add to PATH:
   - Search "Environment Variables" in Windows
   - Edit PATH and add: `C:\Program Files\mingw-w64\bin` (adjust path as needed)

### Error: "cannot find -lm"

**Solution:** Add `-lm` flag:
```powershell
gcc program.c -lm -o program.exe
```

### Program won't run

**Solution:**
1. Use full path: `C:\Users\9fu97v\Documents\Study\C-Learning\01_Fundamentals\calculator.exe`
2. Or just: `.\calculator.exe` (if in same directory)

### VS Code debugging not working

**Solution:**
1. Ensure GDB is installed: `gdb --version`
2. Recheck `.vscode/launch.json` configuration
3. Try using Code Runner extension instead

---

## Next Steps

1. ✅ Choose your IDE (VS Code recommended)
2. ✅ Install compiler (GCC/MinGW)
3. ✅ Verify installation
4. ✅ Compile first program
5. ✅ Start learning!

---

## Verification Checklist

- [ ] GCC compiler installed
- [ ] IDE installed (VS Code / Code::Blocks)
- [ ] Can compile a C program
- [ ] Can run a compiled program
- [ ] Can read compiler errors
- [ ] Debugger works (optional but recommended)

---

**You're all set! 🚀 Begin with the fundamentals!**

