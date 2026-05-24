# C Programming + Linux Learning Repository

**Dual-track learning: C Programming + Linux for Semiconductor Companies**
**Chip Experience: QCA6490 (WiFi 6E/BT) | NXP Patriot**

---

## Your Mission

Transition to a Semiconductor Company (Qualcomm, NXP, MediaTek) with strong
C programming + Linux internals skills. Both tracks run in parallel.

---

## Two Learning Tracks — Run in Parallel

### Track 1: C Programming
- [QUICK_START.md](QUICK_START.md) — Start here for C
- [ROADMAP.md](ROADMAP.md) — 12-week C learning path
- [PROGRESS_TRACKER.md](PROGRESS_TRACKER.md) — Track C progress

### Track 2: Linux Learning (NEW)
- [Linux_Learning/LINUX_QUICK_START.md](Linux_Learning/LINUX_QUICK_START.md) — **START HERE for Linux**
- [Linux_Learning/LINUX_ROADMAP.md](Linux_Learning/LINUX_ROADMAP.md) — 10-week Linux learning path
- [Linux_Learning/LINUX_PROGRESS.md](Linux_Learning/LINUX_PROGRESS.md) — Track Linux progress
- [Linux_Learning/10_Semiconductor_Chip_Work/QCA6490_NXP_GUIDE.md](Linux_Learning/10_Semiconductor_Chip_Work/QCA6490_NXP_GUIDE.md) — Your chips on Linux

### Supporting Files
- [SETUP_GUIDE.md](SETUP_GUIDE.md) - Environment setup for Windows
- [HOW_TO_STUDY.md](HOW_TO_STUDY.md) - Daily learning methodology

---

## Linux Learning Folder Structure

```
Linux_Learning/
├── LINUX_ROADMAP.md             ← 10-week plan + C/Linux parallel table
├── LINUX_QUICK_START.md         ← Day 1 setup + first commands
├── LINUX_PROGRESS.md            ← Track your progress
├── 01_Basics/                   ← Week 1: Commands, /proc, /sys, grep, awk
├── 02_Shell_Scripting/          ← Week 2: Bash, log parsers, build scripts
├── 03_File_System_Permissions/  ← Week 3: FHS, sysfs, device files
├── 04_Processes_Signals/        ← Week 4: fork, threads, IPC (full C overlap)
├── 05_Networking/               ← Week 5: Sockets, nl80211 (QCA6490 stack)
├── 06_Build_Systems/            ← Week 6: Make, CMake, cross-compilation
├── 07_Kernel_Drivers/           ← Week 8: Kernel modules, char devices (THE BIG ONE)
├── 08_Debugging_Tools/          ← Week 7: GDB, strace, ftrace, valgrind
├── 09_Embedded_Linux/           ← Week 9: Yocto, U-Boot, Device Tree
└── 10_Semiconductor_Chip_Work/  ← Week 10: QCA6490 ath11k, NXP drivers
```

---

## C Learning Folder Structure

### Getting Started
- [QUICK_START.md](QUICK_START.md) - **START HERE for C**
- [SETUP_GUIDE.md](SETUP_GUIDE.md) - Environment setup for Windows
- [HOW_TO_STUDY.md](HOW_TO_STUDY.md) - Daily learning methodology
- [ROADMAP.md](ROADMAP.md) - 12-week structured learning path

### Progress Tracking
- [PROGRESS_TRACKER.md](PROGRESS_TRACKER.md) - Weekly progress updates
- [This README.md](README.md) - You are here

### Phase 1: Fundamentals (Week 1-2)
```
01_Fundamentals/
├── THEORY.md ← Read this first
├── EXERCISES.md ← 15 practice problems
├── 01_calculator.c ← Example code
└── 02_multiplication_table.c ← Example code
```

### Phase 4: Pointers ⭐ (Week 4-6) - CRITICAL
```
04_Pointers/
├── CRITICAL_GUIDE.md ← In-depth pointer guide (MUST READ)
├── 01_basic_pointers.c ← Fundamentals
└── 02_function_pointers.c ← Advanced
```

### Other Phases
- `02_Functions_Scope/` - Functions and scope (Week 2-3)
- `03_Arrays_Strings/` - Arrays and strings (Week 3-4)
- `05_Dynamic_Memory/` - malloc/free (Week 6-7)
- `06_Structures/` - Structs and unions (Week 7-8)
- `07_FileIO/` - File operations (Week 8-9)
- `08_Preprocessor/` - Macros and debugging (Week 9-10)
- `09_Data_Structures/` - Linked lists, trees, etc. (Week 10-12)

### Categories
- `Practice_Problems/` - Easy, Medium, Hard problems
- `Interview_Questions/` - Company-specific Q&A samples

---

## 📊 12-Week Learning Path

| Week | Phase | Topics | Status |
|------|-------|--------|--------|
| 1-2 | Fundamentals | Variables, Operators, Loops | ⬜ Not Started |
| 2-3 | Functions & Scope | Functions, Scope, Stack | ⬜ Not Started |
| 3-4 | Arrays & Strings | 1D/2D Arrays, Strings | ⬜ Not Started |
| **4-6** | **Pointers ⭐** | **Critical for embedded systems** | ⬜ Not Started |
| 6-7 | Dynamic Memory | malloc/free, Heap management | ⬜ Not Started |
| 7-8 | Structures | Structs, Unions | ⬜ Not Started |
| 8-9 | File I/O | File operations | ⬜ Not Started |
| 9-10 | Preprocessor | Macros, Debugging | ⬜ Not Started |
| **10-12** | **Data Structures ⭐** | **Linked lists, Trees, Graphs** | ⬜ Not Started |

---

## 🎓 Daily Schedule (3-4 hours)

```
9:00-9:45   Theory       (Read THEORY.md)
9:45-10:30  Examples     (Study .c files)
10:30-12:00 Practice     (Solve exercises)
12:00-12:15 Review       (Summarize learning)
```

---

## 📋 Quick Navigation

### To Begin Learning
1. Open [QUICK_START.md](QUICK_START.md) ← Start here
2. Follow setup instructions in [SETUP_GUIDE.md](SETUP_GUIDE.md)
3. Read [ROADMAP.md](ROADMAP.md) to understand overall structure

### To Learn a Topic
1. Go to phase folder (e.g., `01_Fundamentals/`)
2. Read `THEORY.md` for concepts
3. Study `.c` example files
4. Solve problems in `EXERCISES.md`

### To Track Progress
- Update [PROGRESS_TRACKER.md](PROGRESS_TRACKER.md) every week
- Check confidence levels after each phase

### For Study Tips
- Read [HOW_TO_STUDY.md](HOW_TO_STUDY.md) for methodology
- Avoid common mistakes documented there

---

## ✨ Key Features of This Repository

✅ **Structured:** 9 phases with clear progression  
✅ **Comprehensive:** 300+ exercises + code examples  
✅ **Practical:** Real-world examples for Wi-Fi/embedded systems  
✅ **Interview-Focused:** Data structures heavily covered  
✅ **Windows-Friendly:** Setup guide for Windows users  
✅ **Mentored:** Detailed theory and common mistakes covered  
✅ **Trackable:** Progress tracker included  

---

## 🎯 Learning Objectives

By the end of 12 weeks, you will:

- ✅ Master C fundamentals and advanced concepts
- ✅ Write pointer-heavy embedded systems code
- ✅ Implement all data structures from scratch
- ✅ Debug efficiently using GDB
- ✅ Solve 300+ coding problems
- ✅ Pass semiconductor company interviews
- ✅ Understand system-level programming
- ✅ Be ready for Wi-Fi driver development

---

## 🚀 Quick Start (Right Now!)

1. Open [QUICK_START.md](QUICK_START.md)
2. Follow the 4 first steps
3. Begin Phase 1 today
4. Commit 3-4 hours daily
5. Update progress weekly

---

## 📚 Resources Included

Each phase includes:
- **THEORY.md** - Comprehensive concept explanations
- **EXERCISES.md** - 10-40 practice problems with solutions
- **Example .c files** - Well-commented code examples
- **Progress checklist** - Phase completion criteria

---

## 💡 Success Tips

1. **Code daily** - Even 30 min > 5 hours once a week
2. **Type everything** - Never copy-paste
3. **Debug manually** - Use printf() first, then GDB
4. **Teach others** - Explain concepts out loud
5. **Test edge cases** - Don't just test happy path
6. **Update tracker** - Weekly progress tracking
7. **Stay consistent** - 12 weeks of dedication

---

## ⚠️ Critical Warnings

❌ Don't skip Pointer phase (Week 4-6)  
❌ Don't rush through phases  
❌ Don't copy-paste code  
❌ Don't skip exercises  
❌ Don't move forward if struggling  

---

## 🎓 Your Target Companies

| Company | Salary* | Tech Stack |
|---------|---------|-----------|
| Qualcomm | 8-12 LPA | C, Embedded Systems |
| Intel | 7-11 LPA | C, VLSI, Firmware |
| AMD | 7-10 LPA | C, GPU Architecture |
| Broadcom | 7-10 LPA | C, Networking |
| Nvidia | 8-12 LPA | C, GPU Programming |
| Marvell | 6-9 LPA | C, Embedded Systems |
| Infineon | 6-9 LPA | C, Embedded Systems |

*Estimated 2026 Bangalore salaries

---

## 📖 External Resources

### Books
- "The C Programming Language" by Kernighan & Ritchie
- "C Programming" by Balaguruswamy

### Websites
- GeeksforGeeks
- TutorialsPoint
- YouTube: Neso Academy

### Online Judges
- LeetCode
- HackerRank
- CodeSignal

---

## 📞 Support

If you get stuck:
1. Check [HOW_TO_STUDY.md](HOW_TO_STUDY.md) for common mistakes
2. Review examples in phase folder
3. Search GeeksforGeeks for specific topics
4. Check GDB tutorial in SETUP_GUIDE.md

---

## ✍️ Author Notes

This C learning repository is specifically designed for:
- ✅ Professionals transitioning to embedded systems
- ✅ Wi-Fi team members learning system programming
- ✅ Semiconductor company interview preparation
- ✅ Windows developers using GCC

The curriculum emphasizes:
- Practical embedded systems understanding
- Deep pointer mastery (essential for drivers/firmware)
- Complete data structures implementation
- Interview-focused problem solving

---

## 📅 Timeline

**Current Date:** March 2026  
**Target Start:** This week  
**Estimated Completion:** 3 months  
**Target Interview Prep:** Month 3-4  
**Target Company Join:** Month 4-5  

---

## 🏆 Milestone Checkpoints

- [x] Repository created
- [ ] Week 1: Phase 1 fundamentals
- [ ] Week 2: Phase 1 exercises complete
- [ ] Week 6: Pointer mastery achieved
- [ ] Week 12: Data structures perfected
- [ ] Week 13: Interview prep begins
- [ ] Month 4: Ready for interviews
- [ ] Month 5: Join semiconductor company

---

## 🎉 Ready?

### START HERE → [QUICK_START.md](QUICK_START.md)

---

**Good luck! You've got this! 🚀**

Remember: *Consistency beats intensity. Every day counts.*

---

**Last Updated:** March 16, 2026  
**Status:** 🟢 Active - Ready for Learning

