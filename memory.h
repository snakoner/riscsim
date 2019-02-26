#ifndef MEMORY_H
#define MEMORY_H


#include <iostream>

#define MEMORY_SIZE 4096

class Memory
{
	private:
		int8_t 	mem[MEMORY_SIZE];
	public:
		Memory(){};
		//~Memory();
		void 	init_mem();
		int 	store(int addr, int8_t data);
		int8_t 	load(int addr);

};

#endif