#pragma once

#include <cstdint>
#include <iostream>

#define slice(val, start, stop) (((val) >> (start)) & ((1 << (stop-start+1)) - 1))

enum InstrType {
	R_type,
	I_type,
	S_type,
	B_type,
	U_type,
	J_type
};

enum OpcodeMap {
	LOAD		= 0x03,
	LOAD_FP		= 0x07,
	custom_0	= 0x0B,
	MISC_MEM	= 0x0F, 
	OP_IMM		= 0x13,
	AUIPC		= 0x17,
	OP_IMM_32	= 0x1B,

	STORE		= 0x23,
	STORE_FP	= 0x27,
	custom_1	= 0x2B,
	AMO			= 0x2F,
	OP			= 0x33,
	LUI			= 0x37,
	OP_32		= 0x3B,

	MADD		= 0x43,
	MSUB		= 0x47,
	NMSUB		= 0x4B,
	NMADD		= 0x4F,
	OP_FP		= 0x53,
	reserved_0	= 0x57,
	custom_2	= 0x5B,

	BRANCH		= 0x63,
	JALR		= 0x67,
	reserved_1	= 0x6B,
	JAL			= 0x6F,
	SYSTEM		= 0x73,
	reserved_2	= 0x77,
	custom_3	= 0x7B
};

enum RV32G {
// RV32I
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
	CSRRCI,

// RV64I
	LWU,
	LD,
	SD,
	SLLI,
	SRLI,
	SRAI,
	ADDIW,
	SLLIW,
	SRLIW,
	SRAIW,
	ADDW,
	SUBW,
	SLLW,
	SRLW,
	SRAW,

// RV32M
	MUL,
	MULH,
	MULHSU,
	MULHU,
	DIV,
	DIVU,
	REM,
	REMU,

// RV64M
	MULW,
	DIVW,
	DIVUW,
	REMW,
	REMUW,

// RV32A
	LR_W,
	SC_W,
	AMOSWAP_W,
	AMOADD_W,
	AMOXOR_W,
	AMOAND_W,
	AMOOR_W,
	AMOMIN_W,
	AMOMAX_W,
	AMOMINU_W,
	AMOMAXU_W
};

class Decode {
	InstrType type;
	uint8_t funct7;
	uint8_t funct3;
	OpcodeMap opcode;

	void RType(uint32_t);
	void IType(uint32_t);
	void SType(uint32_t);
	void BType(uint32_t);
	void UType(uint32_t);
	void JType(uint32_t);

public:
	RV32G instr;
	uint8_t rs2;
	uint8_t rs1;
	uint8_t rd;
	uint32_t imm;

	Decode(uint32_t);
};

struct DecodeError {
	char msg[128];

	DecodeError() : msg("Unknown decode error") {}
	DecodeError(const char *str);
};