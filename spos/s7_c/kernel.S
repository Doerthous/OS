.text
.code32
.extern _cstart

.global kernel_entry
kernel_entry:
		call _cstart

inf_loop:
		jmp inf_loop
