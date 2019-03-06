

inline void add_op(uint32_t *rd, uint32_t op1, uint32_t op2, uint32_t &pc){
	*rd = op1 + op2;
	pc += 4;
}

inline void sub_op(uint32_t *rd, uint32_t op1, uint32_t op2, uint32_t &pc){
	*rd = op1 - op2;
	pc += 4;
}

inline void slt_op(uint32_t *rd, uint32_t op1, uint32_t op2, uint32_t &pc){
	*rd = (op1 < op2)?1:0;
	pc += 4;
}

inline void or_op(uint32_t *rd, uint32_t op1, uint32_t op2, uint32_t &pc){
	*rd = op1 | op2;
	pc += 4;
}

