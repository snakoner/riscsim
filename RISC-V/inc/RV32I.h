#pragma once

#include <cstdint>
#include <cstdio>

typedef uint8_t	RV32_reg;

class RV32 {
public:
	const uint32_t x0;
	uint32_t x1;
	uint32_t x2;
	uint32_t x3;
	uint32_t x4;
	uint32_t x5;
	uint32_t x6;
	uint32_t x7;
	uint32_t x8;
	uint32_t x9;
	uint32_t x10;
	uint32_t x11;
	uint32_t x12;
	uint32_t x13;
	uint32_t x14;
	uint32_t x15;
	uint32_t x16;
	uint32_t x17;
	uint32_t x18;
	uint32_t x19;
	uint32_t x20;
	uint32_t x21;
	uint32_t x22;
	uint32_t x23;
	uint32_t x24;
	uint32_t x25;
	uint32_t x26;
	uint32_t x27;
	uint32_t x28;
	uint32_t x29;
	uint32_t x30;
	uint32_t x31;
	uint32_t *pc;

	RV32() : x0(0) { reset(); }
	void reset()
	{
		puts("Reset RV32 state");
		x1 = 0;
		x2 = 0;
		x3 = 0;
		x4 = 0;
		x5 = 0;
		x6 = 0;
		x7 = 0;
		x8 = 0;
		x9 = 0;
		x10 = 0;
		x11 = 0;
		x12 = 0;
		x13 = 0;
		x14 = 0;
		x15 = 0;
		x16 = 0;
		x17 = 0;
		x18 = 0;
		x19 = 0;
		x20 = 0;
		x21 = 0;
		x22 = 0;
		x23 = 0;
		x24 = 0;
		x25 = 0;
		x26 = 0;
		x27 = 0;
		x28 = 0;
		x29 = 0;
		x30 = 0;
		x31 = 0;
	}
};

static RV32 hart;

typedef enum {
	LUI,
	AUIPC,
	JAL,
	JALR,
	BEQ,
	BNE,
	BLT,
	BGE,
	BLTU,
	BGEU,
	LB,
	LH,
	LW,
	LBU,
	LHU,
	SB,
	SH,
	SW,
	ADDI,
	SLTI,
	SLTIU,
	XORI,
	ORI,
	ANDI,
	SLLI,
	SRLI,
	SRAI,
	ADD,
	SUB,
	SLL,
	SLT,
	SLTU,
	XOR,
	SRL,
	SRA,
	OR,
	AND,
	FENCE,
	FENCE_I,
	ECALL,
	EBREAK,
	CSRRW,
	CSRRS,
	CSRRC,
	CSRRWI,
	CSRRSI,
	CSRRCI
} RV32I;