# Assembler Documentation

## Opcodes
| Name | Meaning                | Usage         | Description                                                                    |
| ---- | ---------------------- | ------------- | ------------------------------------------------------------------------------ |
| add  | Add                    | add rA rB rC  | Adds rB and rC, storing the result in rA.                                      |
| addi | Add Immediate          | addi rA rB I7 | Adds rB and I7, storing the result in rA.                                      |
| nand | Bitwise NAND           | nand rA rB rC | Bitwise NAND on rB and rC, storing the result in rA.                           |
| lui  | Load Upper Immediate   | lui rA I10    | Stores I10 into the upper 10 bits of rA.                                       |
| sw   | Save Word              | sw rA rB I7   | Saves rA into memory location referenced by rB+I7.                             |
| lw   | Load Word              | lw rA rB I7   | Loads memory location referenced by rB+I7 into rA.                             |
| beq  | Branch If Equal        | beq rA rB I7  | If rA and rB are equal, PC will be offsetted by I7.                            |
| jalr | Jump And Link Register | jalr rA rB I7 | Jump to rB, but store PC+1 into rA first. If I7!=0, this is a syscall instead. |

## Syntax
The syntax of an assembly language is pretty straightforward.
The following table explains the meaning of the operands of each opcode.

| Name | Description                                   |
| ---- | --------------------------------------------- |
| rA   | First register specified by the instruction.  |
| rB   | Second register specified by the instruction. |
| rC   | Third register specified by the instruction.  |
| I7   | Signed 7-bit immediate.                       |
| I10  | Unsigned 10-bit immediate.                    |

In most sanely designed programming languages, there is a way to put comments into your code.
This is done by typing a pound sign (#).
Everything from that pound sign to the next line of code is completely ignored by the assembler.
The advantage is that it helps to document what your code is doing, especially in assembly since not everything is as readable and unambiguous as, say, Python for example.

Note: In the `beq` instruction, I7 can be a label name, which will be covered within the next sentence.
A label in assembly is a reference point for the program to go out of normal sequential execution and restart that sequential process at that new point in the program.
They can be declared by typing the name of your label and ending it with a colon.
The following assembly code demonstrates its use.

```
      addi r1 r0 5   # r1 = 5
loop: addi r1 r1 -1  # decrement r1
      beq r1 r0 exit # if r1==0, exit the loop
      beq r0 r0 loop # else, go back to the start
exit: halt           # stop machine
```
