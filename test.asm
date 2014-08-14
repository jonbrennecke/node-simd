pop r13, 6		; pop top 6 numbers from the stack into r13
				; sizeof(r13) == 6


push r13		; push eax to the top of the stack
				; the stack is incremented by sizeof(r13)


mul r13, r12	; multiply each element of r13 by the corresponding element in r12
				; the result is stored in r01

mul r13, 8		; multiply each element of r13 by 8.0

div r13, r12	; divide each element of r13 by the corresponding element in r12
				; the result is stored in r01

div r13, 8		; divide each element of r13 by 8.0

mov r13, r12	; clear r13 and mov r12 into r13


