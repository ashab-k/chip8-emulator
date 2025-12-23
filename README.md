# CHIP-8 Emulator

A CHIP-8 emulator implementation in C++ using SDL2 for graphics and input handling.

## Overview

This project implements a CHIP-8 virtual machine emulator. CHIP-8 is an interpreted programming language that was originally used on 8-bit microcomputers in the 1970s. The emulator recreates the CHIP-8 virtual machine, allowing you to run classic CHIP-8 programs and games.

## Building

### Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- SDL2 development libraries
- Make (usually pre-installed on Unix systems)

### Installing SDL2

**macOS:**

```bash
brew install sdl2
```

**Linux (Ubuntu/Debian):**

```bash
sudo apt-get install libsdl2-dev
```

**Linux (Fedora):**

```bash
sudo dnf install SDL2-devel
```

**Windows:**
Download SDL2 development libraries from [libsdl.org](https://www.libsdl.org/download-2.0.php)

### Building with Makefile (Recommended)

The project includes a Makefile that automatically detects your system and SDL2 installation. Simply run:

```bash
make
```

This will:

- Detect your operating system (macOS, Linux, Windows)
- Automatically find SDL2 using `pkg-config` or platform-specific paths
- Compile all source files
- Link everything into the `chip8_sdl2` executable

### Manual Compilation

If you prefer to compile manually or the Makefile doesn't work on your system:

**Using g++/clang++ directly:**

```bash
g++ -std=c++11 main.cpp src/Chip8.cpp -o chip8_sdl2 $(pkg-config --cflags --libs sdl2)
```

**Using clang++:**

```bash
clang++ -std=c++11 main.cpp src/Chip8.cpp -o chip8_sdl2 $(pkg-config --cflags --libs sdl2)
```

**On macOS with Homebrew SDL2:**

```bash
clang++ -std=c++11 main.cpp src/Chip8.cpp -o chip8_sdl2 -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
```

**On Windows (MinGW):**

```bash
g++ -std=c++11 main.cpp src/Chip8.cpp -o chip8_sdl2.exe -I<SDL2_PATH>/include -L<SDL2_PATH>/lib -lSDL2main -lSDL2
```

## Running

The emulator requires three command-line parameters:

```bash
./chip8_sdl2 <Scale> <Delay> <ROM>
```

### Parameters

1. **Scale** (integer)

   - Window size multiplier
   - Original CHIP-8 resolution is 64x32 pixels
   - Example: `Scale = 10` creates a 640x320 pixel window
   - Recommended values: 8-20 depending on your screen size
   - Higher values = larger window, easier to see

2. **Delay** (integer, milliseconds)

   - Cycle delay between instruction executions
   - Controls emulation speed/timing
   - Lower values = faster emulation
   - Recommended values: 1-5 for normal speed, 10-20 for slower/debugging
   - Example: `Delay = 2` waits 2ms between cycles

3. **ROM** (file path)
   - Path to the CHIP-8 ROM file (.ch8)
   - ROM files are loaded into memory starting at address 0x200
   - Example: `test_opcode.ch8` or `tetris.ch8`

### Example Usage

**Run test_opcode.ch8:**

Using Makefile (easiest):

```bash
make test
```

Or manually:

```bash
./chip8_sdl2 10 2 test_opcode.ch8
```

This runs the test ROM with:

- Window scale of 10x (640x320 pixels)
- 2ms delay between cycles
- ROM file: `test_opcode.ch8`

## Project Structure

```
chip8-emulator/
├── core/
│   └── Chip8.h          # CHIP-8 emulator core header
├── src/
│   ├── Chip8.cpp        # CHIP-8 instruction implementations
│   └── platform.h       # SDL2 platform abstraction layer
├── main.cpp             # Main entry point and emulation loop
├── Makefile             # Build configuration
├── test_opcode.ch8      # Test ROM file
└── chip8_sdl2          # Compiled executable (after building)
```
