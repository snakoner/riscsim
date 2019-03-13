#include "..\inc\pipeline.h"
#include "..\inc\RV32I.h"
#include "..\inc\exec.h"

#define slice(val, start, stop) (((val) >> (start)) & ((1 << (stop-start+1)) - 1))

void decode(uint32_t instruction, RV32I& instr, RV32_reg& rd, RV32_reg& rs1, RV32_reg& rs2, uint32_t& imm)
{
	uint8_t op = slice(instruction, 0, 6);
}

process_result pipeline(uint32_t *bytecode) {
	hart.reset();
	puts("Start process");
	hart.pc = bytecode;

	RV32I instr;
	RV32_reg rd;
	RV32_reg rs1;
	RV32_reg rs2;
	uint32_t imm;

	for (;;) {
		uint32_t code = *(hart.pc)++;
		
		decode(code, instr, rd, rs1, rs2, imm);

		switch (instr) {
		case RV32I::LUI: {
			lui(rd, imm);
			break;
		}
		case RV32I::AUIPC: {
			auipc(rd, imm);
			break;
		}
		case RV32I::JAL: {
			jal(rd, imm);
			break;
		}
		case RV32I::JALR: {
			jalr(rd, rs1, imm);
			break;
		}
		case RV32I::BEQ: {
			beq(imm, rs1, rs2);
			break;
		}
		case RV32I::BNE: {
			bne(imm, rs1, rs2);
			break;
		}
		case RV32I::BLT: {
			blt(imm, rs1, rs2);
			break;
		}
		case RV32I::BGE: {
			bge(imm, rs1, rs2);
			break;
		}
		case RV32I::BLTU: {
			bltu(imm, rs1, rs2);
			break;
		}
		case RV32I::BGEU: {
			bgeu(imm, rs1, rs2);
			break;
		}
		case RV32I::LB: {
			lb(rd, rs1, imm);
			break;
		}
		case RV32I::LH: {
			lh(rd, rs1, imm);
			break;
		}
		case RV32I::LW: {
			lw(rd, rs1, imm);
			break;
		}
		case RV32I::LBU: {
			lbu(rd, rs1, imm);
			break;
		}
		case RV32I::LHU: {
			lhu(rd, rs1, imm);
			break;
		}
		case RV32I::SB: {
			sb(rs1, rs2, imm);
			break;
		}
		case RV32I::SH: {
			sh(rs1, rs2, imm);
			break;
		}
		case RV32I::SW: {
			sw(rs1, rs2, imm);
			break;
		}
		case RV32I::ADDI: {
			addi(rd, rs1, imm);
			break;
		}
		case RV32I::SLTI: {
			slti(rd, rs1, imm);
			break;
		}
		case RV32I::SLTIU: {
			sltiu(rd, rs1, imm);
			break;
		}
		case RV32I::XORI: {
			xori(rd, rs1, imm);
			break;
		}
		case RV32I::ORI: {
			ori(rd, rs1, imm);
			break;
		}
		case RV32I::ANDI: {
			andi(rd, rs1, imm);
			break;
		}
		case RV32I::SLLI: {
			slli(rd, rs1, imm);
			break;
		}
		case RV32I::SRLI: {
			srli(rd, rs1, imm);
			break;
		}
		case RV32I::SRAI: {
			srai(rd, rs1, imm);
			break;
		}
		case RV32I::ADD: {
			add(rd, rs1, rs2);
			break;
		}
		case RV32I::SUB: {
			sub(rd, rs1, rs2);
			break;
		}
		case RV32I::SLL: {
			sll(rd, rs1, rs2);
			break;
		}
		case RV32I::SLT: {
			slt(rd, rs1, rs2);
			break;
		}
		case RV32I::SLTU: {
			sltu(rd, rs1, rs2);
			break;
		}
		case RV32I::XOR: {
			xor (rd, rs1, rs2);
			break;
		}
		case RV32I::SRL: {
			srl(rd, rs1, rs2);
			break;
		}
		case RV32I::SRA: {
			sra(rd, rs1, rs2);
			break;
		}
		case RV32I::OR: {
			or (rd, rs1, rs2);
			break;
		}
		case RV32I::AND: {
			and (rd, rs1, rs2);
			break;
		}
		case RV32I::FENCE: {
			fence(rd);
			break;
		}
		case RV32I::FENCE_I: {
			fence_i(rd, rs1, imm);
			break;
		}
		case RV32I::ECALL: {
			ecall(rd, rs1, imm);
			break;
		}
		case RV32I::EBREAK: {
			ebreak(rd, rs1, imm);
			break;
		}
		case RV32I::CSRRW: {
			csrrw(rd, rs1, imm);
			break;
		}
		case RV32I::CSRRS: {
			csrrs(rd, rs1, imm);
			break;
		}
		case RV32I::CSRRC: {
			csrrc(rd, rs1, imm);
			break;
		}
		case RV32I::CSRRWI: {
			csrrwi(rd, rs1, imm);
			break;
		}
		case RV32I::CSRRSI: {
			csrrsi(rd, rs1, imm);
			break;
		}
		case RV32I::CSRRCI: {
			csrrci(rd, rs1, imm);
			break;
		}
		default:
			return ERROR_UNKNOWN_INSTRUCTION;
		}
	}
}