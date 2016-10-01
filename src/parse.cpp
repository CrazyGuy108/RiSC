#include "../include/parse.h"

inst_t reg(const char* name)
{
	static const Table<inst_t> regs
	{
		{ "r0",	0x0000 },
		{ "r1",	0x0001 },
		{ "r2",	0x0002 },
		{ "r3",	0x0003 },
		{ "r4",	0x0004 },
		{ "r5",	0x0005 },
		{ "r6",	0x0006 },
		{ "r7",	0x0007 }
	};

	return regs[name];
}

inst_t imm(const char* name)
{
	char* endp;
	long value{ strtol(name, &endp, 0) };

	return endp == name ? symbols[name] : (inst_t)value;
}

line_t compile(size_t argc, char** argv, uint16_t line)
{
	static const Table<operation_t> ops
	{
		{ ".fill",  &fill },
		{ ".space", &space },
		{ "add",    &add },
		{ "addi",   &addi },
		{ "beq",    &beq },
		{ "halt",   &halt },
		{ "jalr",   &jalr },
		{ "lli",    &lli },
		{ "lui",    &lui },
		{ "lw",	    &lw },
		{ "movi",   &movi },
		{ "nand",   &nand },
		{ "nop",    &nop },
		{ "sw",	    &sw }
	};

	if (argc > 0)
	{
		size_t index{ 0 };
		size_t len{ 0 };
		while (argv[0][len] != '\0')
			++len;

		if (argv[0][len - 1] == ':')
		{
			argv[0][len - 1] = '\0'; // overwrite colon with null character
			symbols.insert(argv[0], line); // the value in this case would be i, the current line number
			index = 1;
		}

		return ops[argv[index]](argc, (const char**)argv, line);
	}
	else
		; // error: undetected blank line (could be a label on a blank line)
}