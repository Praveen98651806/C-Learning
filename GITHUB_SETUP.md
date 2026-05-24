# GitHub Setup Documentation

## Account Details
- **GitHub Username:** Praveen98651806
- **GitHub Profile:** https://github.com/Praveen98651806
- **Repository:** https://github.com/Praveen98651806/C-Learning
- **Email:** 5599praveen@gmail.com

---

## Steps We Completed

### Step 1: Configure Git Locally
Set your identity so commits show your name:
```powershell
git config --global user.name "Praveen Kumar"
git config --global user.email "5599praveen@gmail.com"
```

### Step 2: Create `.gitignore`
Created a `.gitignore` file to exclude unnecessary files from being tracked:
- Compiled binaries: `*.exe`, `*.o`, `*.obj`
- IDE files: `.vscode/`
- Build directories: `build/`, `bin/`
- MinGW folder: `mingw64/`
- OS files: `Thumbs.db`, `.DS_Store`

### Step 3: Initialize Git Repository
```powershell
cd "c:\Users\9fu97v\Documents\Study\C-Learning"
git init
```

### Step 4: Initial Commit
```powershell
git add .
git commit -m "Initial commit: C Learning study materials"
```
- **69 files** committed including all C source files, markdown guides, and learning materials.

### Step 5: Create GitHub Account
- Signed up at https://github.com/signup
- **Username:** Praveen98651806
- **Email:** 5599praveen@gmail.com

### Step 6: Create Repository on GitHub
- Clicked **"+"** → **"New repository"**
- Repository name: `C-Learning`
- No README initialized (already had one locally)

### Step 7: Push to GitHub
```powershell
git remote add origin https://github.com/Praveen98651806/C-Learning.git
git branch -M main
git push -u origin main
```

---

## Daily Git Workflow

Every time you write new code or make changes:

```powershell
# 1. Check what changed
git status

# 2. Stage all changes
git add .

# 3. Commit with a message
git commit -m "describe what you did"

# 4. Push to GitHub
git push
```

### Example commit messages:
- `"Add pointers exercise"`
- `"Complete arrays chapter"`
- `"Fix factorial bug"`

---

## Useful Git Commands

| Command | Description |
|---------|-------------|
| `git status` | See changed/untracked files |
| `git log --oneline` | View commit history |
| `git add .` | Stage all changes |
| `git add filename.c` | Stage a specific file |
| `git commit -m "message"` | Save a snapshot |
| `git push` | Upload to GitHub |
| `git pull` | Download latest from GitHub |
| `git diff` | See what changed in files |
