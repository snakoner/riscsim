#include "..\inc\exec.h"

inline void lui(RV32_reg rd, uint32_t imm)
{
	*(RV32_REG_BASE + rd) = (uint32_t)hart.pc + imm;
}

inline void auipc(RV32_reg rd, uint32_t imm)
{
	*(RV32_REG_BASE + rd) = imm;
}

inline void jal(RV32_reg rd, uint32_t imm)
{
	uint32_t x = imm >> 21;
	uint32_t y = ((x << 21) ^ imm) >> 12;
	uint32_t offset = x * y;
	*(RV32_REG_BASE + rd) = (uint32_t)hart.pc + 4;
	hart.pc = (uint32_t *)((uint32_t)hart.pc + offset);
}

inline void jalr(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void beq(uint32_t imm, RV32_reg rs1, RV32_reg rs2);
inline void bne(uint32_t imm, RV32_reg rs1, RV32_reg rs2);
inline void blt(uint32_t imm, RV32_reg rs1, RV32_reg rs2);
inline void bge(uint32_t imm, RV32_reg rs1, RV32_reg rs2);
inline void bltu(uint32_t imm, RV32_reg rs1, RV32_reg rs2);
inline void bgeu(uint32_t imm, RV32_reg rs1, RV32_reg rs2);
inline void lb(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void lh(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void lw(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void lbu(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void lhu(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void sb(RV32_reg rs1, RV32_reg rs2, uint32_t imm);
inline void sh(RV32_reg rs1, RV32_reg rs2, uint32_t imm);
inline void sw(RV32_reg rs1, RV32_reg rs2, uint32_t imm);
inline void addi(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void slti(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void sltiu(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void xori(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void ori(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void andi(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void slli(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void srli(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void srai(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void add(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void sub(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void sll(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void slt(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void sltu(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void xor(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void srl(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void sra(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void or (RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void and(RV32_reg rd, RV32_reg rs1, RV32_reg rs2);
inline void fence(uint32_t imm);
inline void fence_i(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void ecall(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void ebreak(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void csrrw(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void csrrs(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void csrrc(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void csrrwi(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void csrrsi(RV32_reg rd, RV32_reg rs1, uint32_t imm);
inline void csrrci(RV32_reg rd, RV32_reg rs1, uint32_t imm);