# System Architecture for RiSC
Written by me, based almost entirely off of MIPS.

## Register Usage
| Name  | Usage           |
|:----  |:--------------- |
| r0    | always zero     |
| r1    | return value    |
| r2-r4 | general purpose |
| r5    | stack pointer   |
| r6    | frame pointer   |
| r7    | return address  |

## Syscalls
Unlike MIPS, syscalls are done by a `jalr` opcode with a nonzero immediate field as opposed to a separate opcode with various implementation-defined results.
The two registers given to the `jalr` instruction are also used as the syscall operands, usually with rA being a destination/source register and rB being just a source register.
There can only be up to 127 different syscalls because of the size of the immediate field.
Invalid syscalls will throw an exception.
| ID | Name | Description                  |
|:-- |:---- |:---------------------------- |
| 1  | Halt | Stop machine and print state |
