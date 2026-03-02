# Project Title (C)

> **Short description**: One sentence about what this project does and why it exists.  
> *(Students: Replace this block with your own description.)*

---

## 📁 Project Structure

```
.
├── Makefile              # Build targets: build, run, test, clean, etc.
├── src/                  # C source files and headers
│   ├── main.c
│   ├── module.c
│   └── module.h
├── bin/                  # Compiled binaries (output of build)
│   └── app               # Example executable name
├── test/                 # Test sources (e.g., Unity/CMocka) + fixtures
│   ├── test_main.c
│   └── fixtures/
├── data/                 # Input datasets / sample inputs (no secrets)
│   ├── sample-input.txt
│   └── README.md         # Describe data sources and formats
└── doc/                  # Documentation (design notes, Doxygen config)
    └── design.md
```

> **Notes**
> - `bin/` is generated—usually excluded from version control.
> - Place configuration and design decisions in `doc/`.

---

## 🛠 Prerequisites

- **Compiler**: `gcc` (or `clang`)
- **Make**: GNU Make
- **(Optional)**: `valgrind`, `doxygen`

Check versions:

```bash
gcc --version
make --version
```

---

## 🚀 Quick Start (Build / Run / Test)

```bash
# Build (creates ./bin/app by default)
make

# Run
./bin/app

# Tests
make test

# Memory check
make memcheck
```

---

## 🧭 How to Use This Template (Students)

### 1) Use this template

### 2) Personalize the Project

- Rename the project in this README.
- Fill in the description, inputs/outputs, and known issues.
- Replace sample files in `src/` and `test/` with your implementation.
- **Modify** this README as your project evolves.

### 3) Branching & Commits (Recommended Workflow)

```bash
# Create a feature branch
git checkout -b feature/<short-name>
# Work & commit small, focused changes
git add .
git commit -m "feat: short description"
# Push and open a Pull Request (PR)
git push -u origin feature/<short-name>
```


### 4) Give the TA Access to Your Fork

> **Required for grading.** Add the TA as a **collaborator** to *your forked repository*.

1. On GitHub, open **Settings → Collaborators** (or **Settings → Collaborators and teams**).
2. Click **Add people**, enter the TA's GitHub username (IlKaLUT), choose **Write** access (or as instructed), and **Add**.
3. If the repo is **private**, ensure the TA accepts the email invite.
4. (Optional) If your course uses an organization, you may instead add the TA via **Manage access** or your course team. Follow the course's instructions if they differ.

> Also share the **repository URL** and, if required, the **commit/tag** of the submitted version.

---

## 📚 Documentation

- High-level design: `doc/design.md`
- API docs: generate with Doxygen

```bash
# Generate docs
doxygen doc/Doxyfile
```

---

## 📏 Coding Standards

- **C standard**: C99 
- **Compiler flags**: `-Wall -pedantic`

---

## 🧪 Testing

- Place test sources in `test/`. Choose a C test framework (e.g., Unity, CMocka) or write simple assertion-based tests.
- Document how to run tests here.

```bash
make test
```

---

## 🗂️ Version History

> *(Update this table as you progress. Use semantic versioning if possible.)*

| Version | Date       | Author      | Changes                                               |
|--------:|------------|-------------|-------------------------------------------------------|
| 0.1.0   | 2026-03-01 | Your Name   | Initial scaffold: folders, Makefile, sample main      |

Tag releases:
```bash
git tag -a v0.1.0 -m "Initial scaffold"
git push origin v0.1.0
```

---

## 👤 Author & Course

- **Authors**: Your Name 
- **Course**: Course Name
- **Institution**: LUT University

---

## 📄 License

> *(Choose a license or keep the repository private if unsure.)*

