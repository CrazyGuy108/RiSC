#include "../include/table.h"

TokenException::TokenException()
	: RiscException{} {}

TokenException::TokenException(const char* msg, const char* token)
	: RiscException{ msg }, token{ token } {}