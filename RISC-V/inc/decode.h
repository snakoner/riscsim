#pragma once

#include <cstdint>
#include <iostream>
#include "RV32I.h"

#define slice(val, start, stop) (((val) >> (start)) & ((1 << (stop-start+1)) - 1))

typedef enum {
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
} OpcodeMap;

DecodeStatus decode(uint32_t code, RV32I &instr, RV32_reg &rd, RV32_reg &rs1, RV32_reg &rs2, uint32_t &imm);

typedef enum {
	DECODE_SUCCESS,
	DECODE_LOAD_ERROR,
	DECODE_MISC_MEM_ERROR,
	DECODE_OP_IMM_ERROR,
	DECODE_STORE_ERROR,
	DECODE_OP_ERROR,
	DECODE_BRANCH_ERROR,

	DECODE_ERROR
} DecodeStatus;