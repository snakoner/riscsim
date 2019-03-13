#include "..\config.h"
#include "..\inc\decode.h"

DecodeStatus decode(uint32_t code, RV32I &instr, RV32_reg &rd, RV32_reg &rs1, RV32_reg &rs2, uint32_t &imm) {
	OpcodeMap opcode = (OpcodeMap)slice(code, 0, 6);

	switch (opcode) {
	case OpcodeMap::LOAD: {
		uint8_t funct3 = slice(code, 12, 14);

		rd = slice(code, 7, 11);
		rs1 = slice(code, 15, 19);
		imm = slice(code, 20, 31);

		switch (funct3) {
		case 0:
			instr = RV32I::LB;
			return DECODE_SUCCESS;
		case 1:
			instr = RV32I::LH;
			return DECODE_SUCCESS;
		case 2:
			instr = RV32I::LW;
			return DECODE_SUCCESS;
		case 4:
			instr = RV32I::LBU;
			return DECODE_SUCCESS;
		case 5:
			instr = RV32I::LHU;
			return DECODE_SUCCESS;
		default:
			return DECODE_LOAD_ERROR;
		}
	}
	case OpcodeMap::MISC_MEM: {
		uint8_t funct3 = slice(code, 12, 14);
		switch (funct3) {
		case 0:
			instr = RV32I::FENCE;
			imm = slice(code, 20, 27);
			return DECODE_SUCCESS;
		case 1:
			instr = RV32I::FENCE_I;
			return DECODE_SUCCESS;
		default:
			return DECODE_MISC_MEM_ERROR;
		}
	}
	case OpcodeMap::OP_IMM: {
		uint8_t funct3 = slice(code, 12, 14);

		rd = slice(code, 7, 11);
		rs1 = slice(code, 15, 19);
		imm = slice(code, 25, 31);

		switch (funct3) {
		case 0:
			instr = RV32I::ADDI;
			return DECODE_SUCCESS;
		case 2:
			instr = RV32I::SLTI;
			return DECODE_SUCCESS;
		case 3:
			instr = RV32I::SLTIU;
			return DECODE_SUCCESS;
		case 4:
			instr = RV32I::XORI;
			return DECODE_SUCCESS;
		case 6:
			instr = RV32I::ORI;
			return DECODE_SUCCESS;
		case 7:
			instr = RV32I::ANDI;
			return DECODE_SUCCESS;
		default:
			return DECODE_OP_IMM_ERROR;
		}
	}
	case OpcodeMap::AUIPC: {
		instr = RV32I::AUIPC;
		rd = slice(code, 7, 11);
		imm = slice(code, 12, 31);
		return DECODE_SUCCESS;
	}
	case OpcodeMap::STORE: {
		uint8_t funct3 = slice(code, 12, 14);

		rs1 = slice(code, 15, 19);
		rs2 = slice(code, 20, 24);
		imm = slice(code, 7, 11) + (slice(code, 25, 31) << 5);

		switch (funct3) {
		case 0:
			instr = RV32I::SB;
			return DECODE_SUCCESS;
		case 1:
			instr = RV32I::SH;
			return DECODE_SUCCESS;
		case 3:
			instr = RV32I::SW;
			return DECODE_SUCCESS;
		default:
			return DECODE_STORE_ERROR;
		}
	}
	case OpcodeMap::OP: {
		uint8_t funct3 = slice(code, 12, 14);
		uint8_t funct7 = slice(code, 25, 31);

		rd = slice(code, 7, 11);
		rs1 = slice(code, 15, 19);
		rs2 = slice(code, 20, 24);

		switch (funct7) {
		case 0: {
			switch (funct3) {
			case 0:
				instr = RV32I::ADD;
				return DECODE_SUCCESS;
			case 1:
				instr = RV32I::SLL;
				return DECODE_SUCCESS;
			case 2:
				instr = RV32I::SLT;
				return DECODE_SUCCESS;
			case 3:
				instr = RV32I::SLTU;
				return DECODE_SUCCESS;
			case 4:
				instr = RV32I::XOR;
				return DECODE_SUCCESS;
			case 5:
				instr = RV32I::SRL;
				return DECODE_SUCCESS;
			case 6:
				instr = RV32I::OR;
				return DECODE_SUCCESS;
			case 7:
				instr = RV32I::AND;
				return DECODE_SUCCESS;
			default:
				return DECODE_OP_ERROR;
			}
		}
		case 0x20: {
			switch (funct3) {
			case 0:
				instr = RV32I::SUB;
				return DECODE_SUCCESS;
			case 5:
				instr = RV32I::SRA;
				return DECODE_SUCCESS;
			default:
				return DECODE_OP_ERROR;
			}
		}
		default:
			return DECODE_OP_ERROR;
		}
	}
	case OpcodeMap::LUI: {
		instr = RV32I::AUIPC;
		rd = slice(code, 7, 11);
		imm = slice(code, 12, 31);
		return DECODE_SUCCESS;
	}
	case OpcodeMap::BRANCH:
		uint8_t funct3 = slice(code, 12, 14);

		rs1 = slice(code, 15, 19);
		rs2 = slice(code, 20, 24);
		imm = 0;
			
		switch (funct3) {
		case 0:
			instr = RV32I::BEQ;
			return DECODE_SUCCESS;
		case 1:
			instr = RV32I::BNE;
			return DECODE_SUCCESS;
		case 4:
			instr = RV32I::BLT;
			return DECODE_SUCCESS;
		case 5:
			instr = RV32I::BGE;
			return DECODE_SUCCESS;
		case 6:
			instr = RV32I::BLTU;
			return DECODE_SUCCESS;
		case 7:
			instr = RV32I::BGEU;
			return DECODE_SUCCESS;
		default:
			return DECODE_BRANCH_ERROR;
		}
	// ÄÎÏÈÑÀÒÜ!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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