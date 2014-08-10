Virtue
===

####Pseudo-SIMD Instruction bytecode serialization schema

This is a "Pseudo-SIMD" instruction set in that it embodies the definition of Singular Instruction Multiple Data.  However the serialized instructions bear no resembelance to actual SIMD instructions whatsoever.

_OPCODE_ 
	- determines which instruction
	- the opcode determines the number of operands for which to look (0, 1 or 2)
	- 6 bits
	- there are 64 possible instructions

_R/I/M_ 
	- determine whether the first operand is a register, immediate or memory address
	- 2 bits
	- 0 = register
	- 1 = immediate
	- 2 = memory

_Register_
	- only present if the R/I/M field designates that the operand is a register 
	- a number between 0 and 31 determining which register r00-r31 is used
_Memory_
	- a memory address
	- 4B possible addresses == 4GB of memory

Initialization lists:

Since the assembler is vector-valued, it is possible for several immediate values to be passed.
Therefore, if the R/I/M field designated that the operand is an immediate value, the first value 
to follow is an integer describing the number of immediate values.

Lists		
	- a 32 bit integer

 Immediate		
	- a constant value (integer or floating point number). 
	- integers are always promoted to floating point numbers of the specified precision
	- 

 
| xxxxxx | xx    | xxxxx | xxxxx... | xxxxx... | xxxxx...            |
| ~~~~~~ | ~~~~~ | ~~~~~ | ~~~~~~~~ | ~~~~~~~~ | ~~~~~~~~~~~~~~~~~~~ |
| 6      | 2     | 5     | 32       | 32       | sizeof(precision_t) |
| opcode | r/i/m | reg   | mem      | list     | imm                 |


Operand/Opcode Lookup Table
===

####push
The only parameter to push may be any register, memory or immediate value to be placed on the top of the stack.

```
push_imm
push_mem
push_reg
```

####pop
Pop always takes a register as the first operand; the second operand may be any register, memory or immediate value designating the size to pop off the stack.
```
pop_reg_imm
pop_reg_mem
pop_reg_reg
```










