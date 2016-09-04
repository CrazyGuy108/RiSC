# Assembler
The assembler is mainly split into 2 parts.

The first part has to do with building the symbol table and resolving any other words like that. Second goes through what the first part did and compiles everything into the executable bytecode.

Here's what I have for how everything would work:

1. Load the file to read from.
2. Build the symbol table.
	1. Symbols are identified as words that end with a colon.
	2. Exceptions such as redefining a symbol, or more than one symbol in a given line, can be thrown.
3. Using a ton of bitwise operations, assemble the bytecode line by line and write to the specified file.
	1. After the symbol table is built, the assembler can proceed to go through and compile.
	2. Exceptions thrown can include undefined/missing operands, opcodes, and immediates.
