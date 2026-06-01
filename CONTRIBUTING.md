# Contributing to Firstwords

Thank you for your interest in contributing! This document will guide you through the process of reporting issues, proposing changes, and submitting code.

## Code of Conduct

We follow the [Contributor Covenant Code of Conduct](https://www.contributor-covenant.org/version/2/1/code_of_conduct/). Please read it before participating.

## How Can I Contribute?

### Reporting Bugs

- **Check existing issues** first to avoid duplicates.
- Use the **Bug Report** issue template (if available) and include:
  - Your OS and version (currently macOS is the primary target, but contributions for portability are welcome).
  - Steps to reproduce the bug.
  - Expected vs actual behaviour.
  - Any relevant console output or error messages.

### Suggesting Features

- Open a **Feature Request** issue. Describe:
  - The problem your idea solves.
  - A clear description of the proposed solution.
  - Any alternatives you’ve considered.
- Label it with `enhancement`.

### Pull Requests

1. **Fork** the repository and create your branch from `main`.
2. **Follow the coding style** described below.
3. **Test your changes** – at minimum, build and run the application.
4. **Write clear commit messages**.
5. **Open a Pull Request** and fill in the template (if provided). Link any relevant issues.

## Development Setup

### Prerequisites

- **C++17** (or later) compatible compiler (Clang on macOS, GCC on Linux, MSVC on Windows)
- **CMake 3.15+**
- Libraries:
  - [SQLiteCpp](https://github.com/SRombauts/SQLiteCpp) (wraps SQLite3)
  - [nlohmann/json](https://github.com/nlohmann/json) (header‑only, already in `thirdparty/`)
  - `AutoSaveStorage` and `utils` are custom project headers located in `include/` and `thirdparty/`.

### Build Instructions

```bash
git clone https://github.com/YOUR_USERNAME/BabyAI.git
cd BabyAI
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make -j$(nproc)   # or "cmake --build ."