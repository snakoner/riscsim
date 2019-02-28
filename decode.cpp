#include <iostream>

#define slice(val, start, stop) (((val) >> (start)) & ((1 << (stop-start+1)) - 1))

//тип инструкции зависит от опкода
typedef enum{
	R_Type,
	I_Type,
	S_Type,
	B_Type,
	U_Type,
	J_Type
}InstrType;

class Decode{
	public:
		uint8_t opcode;
		uint8_t rd;
		uint8_t funct3;
		uint8_t rs1;
		uint8_t rs2;
		uint8_t funct7;
		uint32_t imm;
		InstrType inst_type;

		Decode():opcode(0), rd(0), funct3(0), rs1(0), rs2(0), funct7(0), imm(0), inst_type(R_Type){}
		Decode(uint8_t opcode, uint8_t rd, uint8_t funct3, uint8_t rs1, uint8_t rs2, uint8_t funct7, uint32_t imm, InstrType inst_type);
		uint8_t get_opcode(){return opcode;};
		uint8_t get_rd(){return rd;};
		uint8_t get_funct3(){return funct3;};	
		uint8_t get_rs1(){return rs1;};	
		uint8_t get_rs2(){return rs2;};	
		uint8_t get_funct7(){return funct7;};	
		uint32_t get_imm(){return imm;};	
		InstrType get_inst_type(){return inst_type;};
	
		
};


Decode::Decode(uint8_t opcode_, uint8_t rd_, uint8_t funct3_, 
						uint8_t rs1_, uint8_t rs2_, uint8_t funct7_, uint32_t imm_, InstrType inst_type_){
	opcode = opcode_;
	rd = rd_;
	funct3 = funct3_;
	rs1 = rs1_;
	rs2 = rs2_;
	funct7 = funct7_;
	imm = imm_;
	inst_type = inst_type_;
}



void decode_R_type(Decode &obj, uint32_t instr){
	obj.opcode = slice(instr, 0, 6);
	obj.rd = slice(instr, 7, 11);
	obj.funct3 = slice(instr, 12, 14);
	obj.rs1 = slice(instr, 15, 19);
	obj.rs2 = slice(instr, 20, 24);
	obj.funct7 = slice(instr, 25, 31);
}

void decode_I_type(Decode &obj, uint32_t instr){
	
	obj.opcode = slice(instr, 0, 6);
	obj.rd = slice(instr, 7, 11);
	obj.funct3 = slice(instr, 12, 14);
	obj.rs1 = slice(instr, 15, 19);
	obj.imm = slice(instr, 20, 31);
}

void set_type_and_decode(Decode &obj, uint32_t instr){
	uint8_t opcode = slice(instr, 0, 6);
	switch(opcode){
		case 0b0000000:{ //R_type
			decode_R_type(obj, instr);
			std::cout << "R_type instruction" << std::endl;
			break;
		}
		case 0b0000011:{//I_type
			decode_I_type(obj, instr);
			std::cout << "I_type instruction" << std::endl;
			break;
		}
		case 0b0100011:{//S_type
			break;
		}
		case 0b1100011:{//b_type
			break;
		}

	}
}



int main(int argc, char const *argv[])
{
	Decode obj;
	uint32_t instr = 0xdeadbe03;
	set_type_and_decode(obj, instr);
	return 0;
}


