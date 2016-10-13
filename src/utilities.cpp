#include "../include/utilities.h"

OPERAND(op)
{
	return (inst & op_mask) >> op_shift;
}

OPERAND(ra)
{
	return (inst & ra_mask) >> ra_shift;
}

OPERAND(rb)
{
	return (inst & rb_mask) >> rb_shift;
}

OPERAND(rc)
{
	return inst & rc_mask;
}

OPERAND(i7)
{
	return inst & i7_mask | (inst & i7_sign ? ~i7_mask : 0);
}

OPERAND(i10)
{
	return (inst & i10_mask) << i10_shift;
}
