
#ifndef  CHIP8_H
#define CHIP8_H

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
	}
	
    
    void LoadROM(char const* filename);
	void OP_00E0(); //CLS ; clear the display
	void OP_00EE(); //RET ; return from a subroutine
	void OP_1nnn(); //JP addr ; jump to location nnn
	void OP_2nnn(); //CALL addr ; call the subroutine at nnn
	 

};


#endif // ! CHIP8_H