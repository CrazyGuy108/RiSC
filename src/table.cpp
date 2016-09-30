#include "../include/table.h"

TokenException::TokenException()
	: RiscException{} {}

TokenException::TokenException(const char* msg)
	: RiscException{ msg } {}