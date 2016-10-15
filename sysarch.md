# System Architecture for RiSC
Written by me, based almost entirely off of MIPS.

## Register Usage
The only difference here is that there is no argument, global pointer, or saved register(s).
The same caller-preserved vs callee-preserved conventions apply here.
| Name  | Usage           |
|:----  |:--------------- |
| r0    | Always zero     |
| r1    | Return value    |
| r2-r4 | General purpose |
| r5    | Stack pointer   |
| r6    | Frame pointer   |
| r7    | Return address  |

## Syscalls
Unlike MIPS, syscalls are done by a `jalr` opcode with a nonzero immediate field as opposed to a separate opcode with various implementation-defined results.
The two registers given to the `jalr` instruction are also used as the syscall operands, usually with rA being a destination/source register and rB being just a source register.
There can only be up to 127 different syscalls because of the size of the immediate field.
Invalid syscalls will throw an exception.
| ID | Name | Description                  |
|:-- |:---- |:---------------------------- |
| 1  | Halt | Stop machine and print state |
