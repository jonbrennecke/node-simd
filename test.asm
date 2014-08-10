pop r13, 6	; pop top 6 numbers from the stack into eax
			; sizeof(eax) == 6

push r13	; push eax to the top of the stack
			; the stack is incremented by sizeof(eax)

