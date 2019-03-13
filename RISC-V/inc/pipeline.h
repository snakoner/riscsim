#pragma once

enum process_result {
	SUCCESS,
	ERROR_DIVISION_BY_ZERO,
	ERROR_UNKNOWN_INSTRUCTION,
};

process_result pipeline(uint32_t *bytecode);