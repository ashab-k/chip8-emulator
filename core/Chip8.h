
#ifndef  CHIP8_H
#define CHIP8_H
#define VIDEO_WIDTH 64
#define VIDEO_HEIGHT 32

#include <iostream>
#include <chrono>
#include <random>


class Chip8
{
public:
	uint8_t registers[16]{};
	uint8_t memory[4096]{};
	uint16_t index{};
	uint16_t pc{};
	uint16_t stack[16]{};
	uint8_t sp{};
	uint8_t delayTimer{};
	uint8_t soundTimer{};
	uint8_t keypad[16]{};
	uint32_t video[64 * 32]{};
	uint16_t opcode;
	uint8_t randByte;

	std::default_random_engine randGen;
	std::uniform_int_distribution<uint8_t> randByte;

	Chip8():randGen(std::chrono::system_clock::now().time_since_epoch().count()){
		table[0x0] = &Chip8::Table0;
		table[0x1] = &Chip8::OP_1nnn;
		table[0x2] = &Chip8::OP_2nnn;
		table[0x3] = &Chip8::OP_3xkk;
		table[0x4] = &Chip8::OP_4xkk;
		table[0x5] = &Chip8::OP_5xy0;
		table[0x6] = &Chip8::OP_6xkk;
		table[0x7] = &Chip8::OP_7xkk;
		table[0x8] = &Chip8::Table8;
		table[0x9] = &Chip8::OP_9xy0;
		table[0xA] = &Chip8::OP_Annn;
		table[0xB] = &Chip8::OP_Bnnn;
		table[0xC] = &Chip8::OP_Cxkk;
		table[0xD] = &Chip8::OP_Dxyn;
		table[0xE] = &Chip8::TableE;
		table[0xF] = &Chip8::TableF;

		for (size_t i = 0; i <= 0xE; i++){
			table0[i] = &Chip8::OP_NULL;
			table8[i] = &Chip8::OP_NULL;
			tableE[i] = &Chip8::OP_NULL;
		}

		table0[0x0] = &Chip8::OP_00E0;
		table0[0xE] = &Chip8::OP_00EE;

		table8[0x0] = &Chip8::OP_8xy0;
		table8[0x1] = &Chip8::OP_8xy1;
		table8[0x2] = &Chip8::OP_8xy2;
		table8[0x3] = &Chip8::OP_8xy3;
		table8[0x4] = &Chip8::OP_8xy4;
		table8[0x5] = &Chip8::OP_8xy5;
		table8[0x6] = &Chip8::OP_8xy6;
		table8[0x7] = &Chip8::OP_8xy7;
		table8[0xE] = &Chip8::OP_8xyE;

		tableE[0x1] = &Chip8::OP_ExA1;
		tableE[0xE] = &Chip8::OP_Ex9E;

		for (size_t i = 0; i <= 0x65; i++){
			tableF[i] = &Chip8::OP_NULL;
		}

		tableF[0x07] = &Chip8::OP_Fx07;
		tableF[0x0A] = &Chip8::OP_Fx0A;
		tableF[0x15] = &Chip8::OP_Fx15;
		tableF[0x18] = &Chip8::OP_Fx18;
		tableF[0x1E] = &Chip8::OP_Fx1E;
		tableF[0x29] = &Chip8::OP_Fx29;
		tableF[0x33] = &Chip8::OP_Fx33;
		tableF[0x55] = &Chip8::OP_Fx55;
		tableF[0x65] = &Chip8::OP_Fx65;
	}
	
	void Table0(){
		((*this).*(table0[opcode & 0x000Fu]))();
	}

	void Table8(){
		((*this).*(table8[opcode & 0x000Fu]))();
	}

	void TableE(){
		((*this).*(tableE[opcode & 0x000Fu]))();
	}

	void TableF(){
		((*this).*(tableF[opcode & 0x00FFu]))();
	}

	void OP_NULL()
	{}

	typedef void (Chip8::*Chip8Func)();
	Chip8Func table[0xF + 1];
	Chip8Func table0[0xE + 1];
	Chip8Func table8[0xE + 1];
	Chip8Func tableE[0xE + 1];
	Chip8Func tableF[0x65 + 1]; 

    
    void LoadROM(char const* filename);
	void OP_00E0(); //CLS ; clear the display
	void OP_00EE(); //RET ; return from a subroutine
	void OP_1nnn(); //JP addr ; jump to location nnn
	void OP_2nnn(); //CALL addr ; call the subroutine at nnn
	void OP_3xkk(); // SE Vx , byte ; skip next instuction if Vx = kk
	void OP_4xkk(); // SNE Vx, byte ; skip next instruction if Vx != kk
	void OP_5xy0(); // SE Vx, Vy ; skip next instruction if Vx = Vy
	void OP_6xkk(); // LD Vx, byte ; set Vx = kk
	void OP_7xkk(); // ADD Vx, byte ; set Vx = Vx + kk
	void OP_8xy0(); // LD Vx, Vy ; set Vx = Vy
	void OP_8xy1(); // OR Vx, Vy ; set Vx = Vx OR Vy
	void OP_8xy2(); // AND Vx, Vy ; set Vx = Vx AND Vy
	void OP_8xy3(); // XOR Vx, Vy ; set Vx = Vx XOR Vy
	void OP_8xy4(); // ADD Vx, Vy ; set Vx = Vx + Vy, set VF = carry
	void OP_8xy5(); // SUB Vx, Vy ; set Vx = Vx - Vy, set VF = NOT borrow
	void OP_8xy6(); // SHR Vx {, Vy} ; set Vx = Vx SHR 1
	void OP_8xy7(); // SUBN Vx, Vy ; set Vx = Vy - Vx, set VF = NOT borrow
	void OP_8xyE(); // SHL Vx {, Vy} ; set Vx = Vx SHL 1
	void OP_9xy0(); // SNE Vx, Vy ; skip next instruction if Vx != Vy
	void OP_Annn(); // LD I, addr ; set I = nnn
	void OP_Bnnn(); // JP V0, addr ; jump to location nnn + V0
	void OP_Cxkk(); // RND Vx, byte ; set Vx = random byte AND kk
	void OP_Dxyn(); // DRW Vx, Vy, nibble ; display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
	void OP_Ex9E(); // SKP Vx ; skip next instruction if key with the value of Vx is pressed
	void OP_ExA1(); // SKNP Vx ; skip next instruction if key with the value of Vx is not pressed
	void OP_Fx07(); // LD Vx, DT ; set Vx = delay timer value
	void OP_Fx0A(); // LD Vx, K ; wait for a key press, store the value of the key in Vx
	void OP_Fx15(); // LD DT, Vx ; set delay timer = Vx
	void OP_Fx18(); // LD ST, Vx ; set sound timer = Vx
	void OP_Fx1E(); // ADD I, Vx ; set I = I + Vx
	void OP_Fx29(); // LD F, Vx ; set I = location of sprite for digit Vx
	void OP_Fx33(); // LD B, Vx ; store BCD representation of Vx in memory locations I, I+1, and I+2
	void OP_Fx55(); // LD [I], Vx ; store registers V0 through Vx in memory starting at location I
	void OP_Fx65(); // LD Vx, [I] ; read registers V0 through Vx from memory starting at location I

	void Cycle();

};


#endif // ! CHIP8_H