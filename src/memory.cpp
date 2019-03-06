#include "memory.h"

#define MEMORY_SIZE 4096


void Memory::init_mem(void){
	for(int i = 0; i < MEMORY_SIZE; i++)
		mem[i] = 0x00;
}
int Memory::store(int addr, int8_t data){
		if(addr >= MEMORY_SIZE)
			return 0;
		else
			mem[addr] = data;
		return 1;
}
int8_t Memory::load(int addr){
	if(addr >= MEMORY_SIZE)
		exit(1);
	else
		return mem[addr];
}

