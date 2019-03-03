#include <iostream>

#define slice(val, start, stop) (((val) >> (start)) & ((1 << (stop-start+1)) - 1))

//тип инструкции зависит от опкода

typedef enum{
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
	SLTU,
	XOR,
	SRL,
	SRA,
	OR,
	AND,
	FENCE,
	FENCEI,
	ECALL,
	EBREAK,
	CSRRW,
	CSRRS,
	CSRRC,
	CSRRWI,
	CSRRSI,
	CSRRCI
}Instruction;


class Decode{
	public:
		uint8_t rd;
		uint8_t rs1;
		uint8_t rs2;
		uint32_t imm;
		uint8_t shamt;
		Instruction instr;

		Decode():rd(0), rs1(0), rs2(0), imm(0), instr(ADD){}
		Decode(uint8_t rd_, uint8_t rs1_, uint8_t rs2_, uint32_t imm_, uint8_t shamt, Instruction instr_);
	
		
};


Decode::Decode(uint8_t rd_, uint8_t rs1_, uint8_t rs2_, uint32_t imm_, uint8_t shamt, Instruction instr_)
{
	rd = rd_;
	rs1 = rs1_;
	rs2 = rs2_;
	imm = imm_;
	shamt = shamt_;
	instr = instr_;
}

void decode_R_type(Decode &obj, uint32_t instr){
	obj.rd = slice(instr, 7, 11);
	obj.rs1 = slice(instr, 15, 19);
	obj.rs2 = slice(instr, 20, 24);
}

void decode_I_type(Decode &obj, uint32_t instr){
	obj.rd = slice(instr, 7, 11);
	obj.rs1 = slice(instr, 15, 19);
	obj.imm = slice(instr, 20, 31);
}

void decode_S_type(Decode &obj, uint32_t instr){
}
void decode_B_type(Decode &obj, uint32_t instr){
}

void decode_U_type(Decode &obj, uint32_t instr){
	obj.rd = slice(instr, 7, 11);
	obj.imm = slice(instr, 12, 31);
}
void decode_J_type(Decode &obj, uint32_t instr){
	obj.rd = slice(instr, 7, 11);
	obj.imm = slice(instr, 12, 31); //check
}


void set_type_and_decode(Decode &obj, uint32_t instr){
	uint8_t opcode = slice(instr, 0, 6);
	if (opcode == 0b0110111){
		decode_U_type(obj, instr);
		obj.Instruction = LUI;
	}
	else if(opcode == 0b0010111){
		decode_U_type(obj, instr);
		obj.Instruction = AUIPC;
	}
	else if(opcode == 0b1101111){
		decode_J_type(obj, instr);
		obj.Instruction = JAL;
	}
	else if(opcode == 1100111){
		decode_I_type(obj, instr);
		obj.Instruction = JALR;
	}
	else if(opcode == 1100011){
		decode_B_type(obj, instr);
		uint8_t funct3 = slice(instr, 12,14);
		switch(funct3){
			case 0b000:{
				obj.Instruction = BEQ;
				break; 			}
			case 0b001:{
				obj.Instruction = BNE;
				break; 			}
			case 0b100:{
				obj.Instruction = BLT;
				break;  		}
			case 0b101:{
				obj.Instruction = BGE;
				break;  		}
			case 0b110:{
				obj.Instruction = BLTU;
				break; 			}
			case 0b111:{
				obj.Instruction = BGEU;
				break; 			}

		}
	}
	else if (opcode == 0b0000011){
		decode_I_type(obj, instr);
		uint8_t funct3 = slice(instr, 12,14);
		switch(funct3){
			case 0b000:{
				obj.Instruction = LB;
				break;		}
			case 0b001:{
				obj.Instruction = LH;
				break;    	}
			case 0b010:{
				obj.Instruction = LW;
				break;    	}
			case 0b100:{
				obj.Instruction = LBU;
				break;    	}
			case 0b101:{
				obj.Instruction = LHU;
				break;   	}
		}
	}
	else if (opcode == 0b0100011){
		decode_S_type(obj, instr);
		uint8_t funct3 = slice(instr, 12,14);
		switch(funct3){
			case 0b000:{
				obj.Instruction = SB;
				break;		}
			case 0b001:{
				obj.Instruction = SH;
				break;    	}
			case 0b010:{
				obj.Instruction = SW;
				break;    	}
		}
	}
	else if (opcode == 0b0100011){
		decode_I_type(obj, instr);
		uint8_t funct3 = slice(instr, 12,14);
		switch(funct3){
			case 0b000:{
				obj.Instruction = ADDI;
				break;		}
			case 0b001:{
				obj.Instruction = SLTI;
				break;    	}
			case 0b011:{
				obj.Instruction = SLTIU;
				break;    	}
			case 0b100:{
				obj.Instruction = XORI;
				break;		}	
			case 0b110:{
				obj.Instruction = ORI;
				break;		}
			case 0b111:{
				obj.Instruction = ANDI;
				break;		}
	}
	else if (opcode == 0b0010011){
		decode_I_type(obj, instr);
		uint8_t funct3 = slice(instr, 12,14);
		switch(funct3){
			case 0b001:{
				obj.Instruction = SLLI;
				break;		}
			case 0b101:{
				uint8_t funct7 = slice(instr, 25, 31);
				if (funct7 == 0b0000000)
					obj.Instruction = SRLI;
				else if (funct7 == 0b0100000)
					obj.Instruction = SRAI;
				break;		}

		}
	}
	else if (opcode == 0b0110011){
		decode_R_type(obj, instr);
		uint8_t funct3 = slice(instr, 12,14);
		switch(funct3){
			case 0b000:{
				uint8_t funct7 = slice(instr, 25, 31);
				if (funct7 == 0b0000000)
					obj.Instruction = ADD;
				else if (funct7 == 0b0100000)
					obj.Instruction = SUB;
				break;		}
			case 0b101:{
				uint8_t funct7 = slice(instr, 25, 31);
				if (funct7 == 0b0000000)
					obj.Instruction = SRL;
				else if (funct7 == 0b0100000)
					obj.Instruction = SRA;
				break;		}
			case 0b001:{
				obj.Instruction = SLL;
				break;
				}
			case 0b010:{
				obj.Instruction = SLT;
				break;	
			}
			case 0b011:{
				obj.Instruction = SLTU;
			}
			case 0b100:{
				obj.Instruction = XOR;
			}
		
			case 0b110:{
				obj.Instruction = OR;
			}
			case 0b111:{
				obj.Instruction = AND;
			}
		}
	}
}


int main(int argc, char const *argv[])
{
	Decode obj;
	uint32_t instr = 0xdeadbe00;
	set_type_and_decode(obj, instr);

	return 0;
}


