# Contributing Guide

## Code Formatting

This project requires **`clang-format` version 22** to pass the automated GitHub Actions CI checks.

### 1. Install `clang-format`

**macOS:**
```bash
brew install llvm
```

**Ubuntu / Linux:**
```bash
wget [https://apt.llvm.org/llvm.sh](https://apt.llvm.org/llvm.sh)
chmod +x llvm.sh
sudo ./llvm.sh 22
sudo apt-get install -y clang-format-22
```

### 2. Format your code
We provide Makefile targets to handle formatting easily.
* Apply formatting (Run before committing):
```bash
make format
```

* Verify formatting (What the CI runs):
```bash
make format-check
```

Note for Linux users: If your system installed the tool as clang-format-22, you can tell the Makefile to use it like this:
make format CLANG_FORMAT=clang-format-22
