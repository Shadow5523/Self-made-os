.global as_keyboard_interrupt
.global as_software_interrupt

.extern keyboard_interrupt
.extern syscall_interrupt

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


as_software_interrupt:
	 pushl %esp
	 pushl %ebp
	 pushl %esi
	 pushl %edi
	 pushl %edx
	 pushl %ecx
	 pushl %ebx
	 pushl %eax
	 call syscall_interrupt	
	 popl %eax
	 popl %ebx
	 popl %ecx
	 popl %edx
	 popl %edi
	 popl %esi
	 popl %ebp
	 popl %esp
	 iretl
	
