.text
.code32
.extern _cstart

.global kernel_entry
kernel_entry:
		movl $_stack_top, %ebp
		movl $_stack_bottom, %esp
		call _cstart

inf_loop:
		jmp inf_loop
		
.data
_stack_top:
    .space 0x2000
_stack_bottom:

