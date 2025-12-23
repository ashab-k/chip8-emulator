#ifndef CHIP8_H
#define CHIP8_H
#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32

#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include <cstdint>

class Chip8
{
public:
	uint8_t registers[16];
	uint8_t memory[4096];
	uint16_t index;
	uint16_t pc;
	uint16_t stack[16];
	uint8_t sp;
	uint8_t delayTimer;
	uint8_t soundTimer;
	uint8_t keypad[16];
	uint32_t video[64 * 32];
	uint16_t opcode;

	std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randDist;

	static const unsigned int START_ADDRESS = 0x200;
	static const unsigned int FONTSET_SIZE = 80;
	static const unsigned int FONTSET_START_ADDRESS = 0x50;

	static uint8_t fontset[FONTSET_SIZE];

	typedef void (Chip8::*Chip8Func)();

	// Function pointer tables for instruction dispatch
	Chip8Func table[0xF + 1];
	Chip8Func table0[0xE + 1];
	Chip8Func table8[0xE + 1];
	Chip8Func tableE[0xE + 1];
	Chip8Func tableF[0x65 + 1];

	// Constructor
	Chip8();

	// Table dispatch functions
	void Table0();
	void Table8();
	void TableE();
	void TableF();
	void OP_NULL();

	// ROM loading
	void LoadROM(char const* filename);

	// CHIP-8 Instructions
	void OP_00E0(); // CLS - clear the display
	void OP_00EE(); // RET - return from a subroutine
	void OP_1nnn(); // JP addr - jump to location nnn
	void OP_2nnn(); // CALL addr - call the subroutine at nnn
	void OP_3xkk(); // SE Vx, byte - skip next instruction if Vx = kk
	void OP_4xkk(); // SNE Vx, byte - skip next instruction if Vx != kk
	void OP_5xy0(); // SE Vx, Vy - skip next instruction if Vx = Vy
	void OP_6xkk(); // LD Vx, byte - set Vx = kk
	void OP_7xkk(); // ADD Vx, byte - set Vx = Vx + kk
	void OP_8xy0(); // LD Vx, Vy - set Vx = Vy
	void OP_8xy1(); // OR Vx, Vy - set Vx = Vx OR Vy
	void OP_8xy2(); // AND Vx, Vy - set Vx = Vx AND Vy
	void OP_8xy3(); // XOR Vx, Vy - set Vx = Vx XOR Vy
	void OP_8xy4(); // ADD Vx, Vy - set Vx = Vx + Vy, set VF = carry
	void OP_8xy5(); // SUB Vx, Vy - set Vx = Vx - Vy, set VF = NOT borrow
	void OP_8xy6(); // SHR Vx {, Vy} - set Vx = Vx SHR 1
	void OP_8xy7(); // SUBN Vx, Vy - set Vx = Vy - Vx, set VF = NOT borrow
	void OP_8xyE(); // SHL Vx {, Vy} - set Vx = Vx SHL 1
	void OP_9xy0(); // SNE Vx, Vy - skip next instruction if Vx != Vy
	void OP_Annn(); // LD I, addr - set I = nnn
	void OP_Bnnn(); // JP V0, addr - jump to location nnn + V0
	void OP_Cxkk(); // RND Vx, byte - set Vx = random byte AND kk
	void OP_Dxyn(); // DRW Vx, Vy, nibble - display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
	void OP_Ex9E(); // SKP Vx - skip next instruction if key with the value of Vx is pressed
	void OP_ExA1(); // SKNP Vx - skip next instruction if key with the value of Vx is not pressed
	void OP_Fx07(); // LD Vx, DT - set Vx = delay timer value
	void OP_Fx0A(); // LD Vx, K - wait for a key press, store the value of the key in Vx
	void OP_Fx15(); // LD DT, Vx - set delay timer = Vx
	void OP_Fx18(); // LD ST, Vx - set sound timer = Vx
	void OP_Fx1E(); // ADD I, Vx - set I = I + Vx
	void OP_Fx29(); // LD F, Vx - set I = location of sprite for digit Vx
	void OP_Fx33(); // LD B, Vx - store BCD representation of Vx in memory locations I, I+1, and I+2
	void OP_Fx55(); // LD [I], Vx - store registers V0 through Vx in memory starting at location I
	void OP_Fx65(); // LD Vx, [I] - read registers V0 through Vx from memory starting at location I

	// Main emulation cycle
	void Cycle();
};

#endif // CHIP8_H