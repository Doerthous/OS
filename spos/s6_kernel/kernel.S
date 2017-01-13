.text
.code32

.global kernel_entry
kernel_entry:
		movl $0xb8000, %eax
		movl $MSG, %esi 
show_msg:
		movb (%esi), %bl
		movb %bl, (%eax)
		addl $2, %eax
		addw $1, %si
		cmpl $MSG_END, %esi
		jne show_msg

inf_loop:
		jmp inf_loop

.data
MSG:	
		.asciz "Kernel"
MSG_END:
