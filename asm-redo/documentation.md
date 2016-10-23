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

| Name | Description                                   |
| ---- | --------------------------------------------- |
| rA   | First register specified by the instruction.  |
| rB   | Second register specified by the instruction. |
| rC   | Third register specified by the instruction.  |
| I7   | Signed 7-bit immediate.                       |
| I10  | Unsigned 10-bit immediate.                    |
