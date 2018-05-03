.global load_idtr

load_idtr:
	mov     4(%esp), %eax
	lidt    (%eax)
	ret
