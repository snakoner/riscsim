#include "..\inc\decode.h"

Decode::Decode(uint32_t code) {
	opcode = (OpcodeMap)slice(code, 0, 6);
	try {
		switch (opcode)
		{
		case OpcodeMap::LOAD:
			IType(code);
			switch (funct3)
			{
			case 0:
				instr = RV32G::LB;
				break;
			case 1:
				instr = RV32G::LH;
				break;
			case 2:
				instr = RV32G::LW;
				break;
			case 3:
				throw DecodeError("Decode Error: This LOAD instruction is not implemented yet");
				break;
			case 4:
				instr = RV32G::LBU;
				break;
			case 5:
				instr = RV32G::LHU;
				break;
			case 6:
				throw DecodeError("Decode Error: This LOAD instruction is not implemented yet");
				break;
			default:
				throw DecodeError("Decode Error: Incorrect LOAD instruction");
				break;
			}
			break;
		case OpcodeMap::LOAD_FP:
			throw DecodeError("Decode Error: LOAD-FP instruction set is not implemented yet");
			break;
		case OpcodeMap::MISC_MEM:
			IType(code);
			switch (funct3)
			{
			case 0:
				instr = RV32G::FENCE;
				break;
			case 1:
				instr = RV32G::FENCE_I;
				break;
			default:
				throw DecodeError("Decode Error: Incorrect MISC_MEM instruction");
				break;
			}
			break;
		case OpcodeMap::OP_IMM:
			IType(code);
			switch (funct3)
			{
			case 0:
				instr = RV32G::ADDI;
				break;
			case 1:
				throw DecodeError("Decode Error: This OP-IMM instruction is not implemented yet");
				break;
			case 2:
				instr = RV32G::SLTI;
				break;
			case 3:
				instr = RV32G::SLTIU;
				break;
			case 4:
				instr = RV32G::XORI;
				break;
			case 5:
				throw DecodeError("Decode Error: This OP-IMM instruction is not implemented yet");
				break;
			case 6:
				instr = RV32G::ORI;
				break;
			case 7:
				instr = RV32G::ANDI;
				break;
			default:
				throw DecodeError("Decode Error: Incorrect OP-IMM instruction");
				break;
			}
			break;
		case OpcodeMap::AUIPC:
			UType(code);
			instr = RV32G::AUIPC;
			break;
		case OpcodeMap::OP_IMM_32:
			throw DecodeError("Decode Error: OP-IMM-32 instruction set is not implemented yet");
			break;
		case OpcodeMap::STORE:
			SType(code);
			switch (funct3)
			{
			case 0:
				instr = RV32G::SB;
				break;
			case 1:
				instr = RV32G::SH;
				break;
			case 3:
				instr = RV32G::SW;
				break;
			default:
				throw DecodeError("Decode Error: Incorrect STORE instruction");
				break;
			}
			break;
		case OpcodeMap::STORE_FP:
			throw DecodeError("Decode Error: STORE-FP instruction set is not implemented yet");
			break;
		case OpcodeMap::AMO:
			throw DecodeError("Decode Error: AMO instruction set is not implemented yet");
			break;
		case OpcodeMap::OP:
			RType(code);
			switch (funct3)
			{
			case 0:
				instr = (funct7) ? RV32G::SUB : RV32G::ADD;
				break;
			case 1:
				instr = RV32G::SLL;
				break;
			case 2:
				instr = RV32G::SLT;
				break;
			case 3:
				instr = RV32G::SLTU;
				break;
			case 4:
				instr = RV32G::XOR;
				break;
			case 5:
				instr = (funct7) ? RV32G::SRA : RV32G::SRL;
				break;
			case 6:
				instr = RV32G::OR;
				break;
			case 7:
				instr = RV32G::AND;
				break;
			default:
				throw DecodeError("Decode Error: Incorrect OP instruction");
				break;
			}
			break;
		case OpcodeMap::LUI:
			UType(code);
			instr = RV32G::LUI;
			break;
		case OpcodeMap::OP_32:
			throw DecodeError("Decode Error: OP-32 instruction set is not implemented yet");
			break;
		case OpcodeMap::MADD:
			throw DecodeError("Decode Error: MADD instruction set is not implemented yet");
			break;
		case OpcodeMap::MSUB:
			throw DecodeError("Decode Error: MSUB instruction set is not implemented yet");
			break;
		case OpcodeMap::NMSUB:
			throw DecodeError("Decode Error: NMSUB instruction set is not implemented yet");
			break;
		case OpcodeMap::NMADD:
			throw DecodeError("Decode Error: NMADD instruction set is not implemented yet");
			break;
		case OpcodeMap::OP_FP:
			throw DecodeError("Decode Error: OP_FP instruction set is not implemented yet");
			break;
		case OpcodeMap::BRANCH:
			BType(code);
			switch (funct3)
			{
			case 0:
				instr = RV32G::BEQ;
				break;
			case 1:
				instr = RV32G::BNE;
				break;
			case 4:
				instr = RV32G::BLT;
				break;
			case 5:
				instr = RV32G::BGE;
				break;
			case 6:
				instr = RV32G::BLTU;
				break;
			case 7:
				instr = RV32G::BGEU;
				break;
			default:
				throw DecodeError("Decode Error: Incorrect BRANCH instruction");
				break;
			}
			break;
		case OpcodeMap::JALR:
			IType(code);
			if (funct3) {
				throw DecodeError("Decode Error: Incorrect JALR instruction");
			}
			else {
				instr = RV32G::JALR;
			}
			break;
		case OpcodeMap::JAL:
			JType(code);
			instr = RV32G::JAL;
			break;
		case OpcodeMap::SYSTEM:
			IType(code);
			switch (funct3)
			{
			case 0:
				if (rd || rs1) {
					throw DecodeError("Decode Error: Incorrect ECALL\EBREAK instruction");
				}
				else {
					instr = (funct7) ? RV32G::EBREAK : RV32G::ECALL;
				}
				break;
			case 1:
				instr = RV32G::CSRRW;
				break;
			case 2:
				instr = RV32G::CSRRS;
				break;
			case 3:
				instr = RV32G::CSRRC;
				break;
			case 5:
				instr = RV32G::CSRRWI;
				break;
			case 6:
				instr = RV32G::CSRRSI;
				break;
			case 7:
				instr = RV32G::CSRRCI;
				break;
			default:
				throw DecodeError("Decode Error: Incorrect BRANCH instruction");
				break;
			}
			break;
		default:
			throw DecodeError("Decode Error: Wrong opcode");
			break;
		}
	}
	catch (DecodeError err) {
		std::cout << err.msg << std::endl;
	}
}

void Decode::RType(uint32_t code) {
	type = R_type;
	rd = slice(code, 7, 11);
	funct3 = slice(code, 12, 14);
	rs1 = slice(code, 15, 19);
	rs2 = slice(code, 20, 24);
	funct7 = slice(code, 25, 31);
}

void Decode::IType(uint32_t code) {
	type = I_type;
	rd = slice(code, 7, 11);
	funct3 = slice(code, 12, 14);
	rs1 = slice(code, 15, 19);
	imm = slice(code, 20, 31);
}

void Decode::SType(uint32_t code) {
	type = S_type;
	rd = slice(code, 7, 11);
	funct3 = slice(code, 12, 14);
	rs1 = slice(code, 15, 19);
	rs2 = slice(code, 20, 24);
	imm = slice(code, 25, 31);
}

void Decode::BType(uint32_t code) {
	type = B_type;
	rd = slice(code, 7, 11);
	funct3 = slice(code, 12, 14);
	rs1 = slice(code, 15, 19);
	rs2 = slice(code, 20, 24);
	imm = slice(code, 25, 31);
}

void Decode::UType(uint32_t code) {
	type = J_type;
	rd = slice(code, 7, 11);
	imm = slice(code, 31, 12);
}

void Decode::JType(uint32_t code) {
	type = J_type;
	rd = slice(code, 7, 11);
	imm = slice(code, 31, 12);
}

DecodeError::DecodeError(const char *str) {
	strcpy(msg, str);
}