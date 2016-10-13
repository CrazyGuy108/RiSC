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
	
}

OPERAND(i10)
{

}
