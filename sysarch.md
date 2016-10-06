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

## Memory Map
| Address Space | Size | Usage  |
|:--------------|:---- |:-------|
| 0x0000-0x7fff | 32kb | user   |
| 0x8000-0xffff | 32kb | kernel |
