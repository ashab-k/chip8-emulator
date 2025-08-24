#include "../core/Chip8.h"
#include <fstream>

const unsigned int START_ADDRESS = 0x200;
void Chip8::LoadROM(char const* filename){
    std::ifstream file(filename , std::ios::binary | std::ios::ate);

    if (file.is_open()){
        //get size of file and allocate a buffer
        std::streampos size = file.tellg();
        char * buffer = new char[size];

        //go to the start of the file and fill the buffer 
        file.seekg(0 , std::ios::beg);
        file.read(buffer, size);
        file.close();

        //load the rom into the memory
        for(long i = 0 ; i < size ; ++i){
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
    }
}

const unsigned int FONTSET_SIZE = 80;

uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

const unsigned int FONTSET_START_ADDRESS = 0x50;

    Chip8::Chip8(){
        pc = START_ADDRESS;
        randByte = std::uniform_int_distribution<uint8_t>(0, 255U);

        for (unsigned int i = 0 ; i < FONTSET_SIZE ; ++i){
            memory[FONTSET_START_ADDRESS + i] = fontset[i];
        }
}

void Chip8::OP_00E0(){
    memset(video, 0 , sizeof(video));
}
