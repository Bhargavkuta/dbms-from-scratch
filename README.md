# AstraDB

A relational database management system built from scratch in C++20.

## Project Structure

```text
AstraDB/
├── CMakeLists.txt
├── CMakePresets.json
├── README.md
├── include/
│   └── astra/        # Public engine headers
├── src/              # Engine implementation & CLI entrypoint
├── tests/            # Unit & integration tests (CTest)
├── docs/             # Architecture & design notes
└── data/             # Runtime database files
```

## Prerequisites

- CMake 3.20+
- C++20 compiler (GCC 13+ / MinGW-w64, Clang, or MSVC / Visual Studio 2022)

## Build & Run

### Using CMake Presets (recommended)

```bash
# MinGW GCC (Debug)
cmake --preset mingw-debug
cmake --build --preset mingw-debug
ctest --preset mingw-debug
./build/mingw-debug/astra
```

On Windows PowerShell, run `.\build\mingw-debug\astra.exe`. Available presets are listed in `CMakePresets.json` (`mingw-debug`, `mingw-release`, `msvc`).

### Standard CMake Commands

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

*(For multi-config generators like Visual Studio, pass `-C Debug` to `ctest` and `--config Debug` to `cmake --build`.)*

