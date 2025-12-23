# CHIP-8 Emulator Makefile

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Executable name
TARGET = chip8_sdl2

# Source files
SOURCES = main.cpp src/Chip8.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Detect OS
UNAME_S := $(shell uname -s)

# SDL2 configuration
# Try pkg-config first (Linux)
SDL2_CFLAGS := $(shell pkg-config --cflags sdl2 2>/dev/null)
SDL2_LIBS := $(shell pkg-config --libs sdl2 2>/dev/null)

# If pkg-config fails, try platform-specific defaults
ifeq ($(SDL2_CFLAGS),)
  ifeq ($(UNAME_S),Darwin)
   
    SDL2_CFLAGS = -I/opt/homebrew/include -I/usr/local/include
    SDL2_LIBS = -L/opt/homebrew/lib -L/usr/local/lib -lSDL2
  else ifeq ($(UNAME_S),Linux)
  
    SDL2_CFLAGS = -I/usr/include/SDL2
    SDL2_LIBS = -lSDL2
  else
  
    SDL2_CFLAGS = -I/usr/include/SDL2
    SDL2_LIBS = -lSDL2main -lSDL2
  endif
endif

# Include flags
INCLUDES = -Isrc -Icore $(SDL2_CFLAGS)

# Linker flags
LDFLAGS = $(SDL2_LIBS)

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean build artifacts
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "Clean complete"

# Rebuild everything
rebuild: clean all

# Run test_opcode.ch8 (example)
test: $(TARGET)
	./$(TARGET) 10 2 test_opcode.ch8



install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	@echo "Installed $(TARGET) to /usr/local/bin"

uninstall:
	rm -f /usr/local/bin/$(TARGET)
	@echo "Uninstalled $(TARGET)"


debug: CXXFLAGS = -std=c++11 -Wall -Wextra -g -O0 -DDEBUG
debug: $(TARGET)


info:
	@echo "Compiler: $(CXX)"
	@echo "Flags: $(CXXFLAGS)"
	@echo "SDL2 CFLAGS: $(SDL2_CFLAGS)"
	@echo "SDL2 LIBS: $(SDL2_LIBS)"
	@echo "Sources: $(SOURCES)"
	@echo "Objects: $(OBJECTS)"
	@echo "Target: $(TARGET)"
	@echo "OS: $(UNAME_S)"

.PHONY: all clean rebuild test install uninstall debug info

