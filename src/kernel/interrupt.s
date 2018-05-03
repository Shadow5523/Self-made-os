.global as_keyboard_interrupt
.extern keyboard_interrupt

as_keyboard_interrupt:
	push    %es
	push    %ds
	pushal
	mov     %esp, %eax
	push    %eax
	mov     %ss, %ax
	mov     %ax, %ds
	mov     %ax, %es
	call    keyboard_interrupt
	pop     %eax
	popal
	pop     %ds
	pop     %es
	sti
	iretl
