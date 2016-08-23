# Assembler
The assembler is mainly split into 2 parts.

The first part has to do with building the symbol table and resolving any other words like that. Second goes through what the first part did and compiles everything into the executable bytecode.

Here's what I have for how everything would work:

1. Open the file to read from using command line argument.
	1. If file not found, ask for the name instead.
2. Go through every word and identify+resolve symbols, opcodes, and operands.
	1. How it will resolve the operands depends initially on the opcode.
	2. Exceptions can be thrown which should be handled by main and respond accordingly.
3. Using a ton of bitwise operations, assemble the bytecode line by line and output to the specified file.
	1. Same as 1.1.
	2. By now, everything should be ready to compile, since all symbols and words have been resolved.