.text
.code16

# 注: 所有符号都链接到0xc200, 见loader.lds
loader:
		movw $0, %ax
		movw %ax, %es # 因为boot的时候修改了es,所以此处需还原

		# bios中断 int 0x10, 0x13
		movw 	$MSG, %bp 			
		movw	$(MSG_END - MSG), %cx
		movb	$18, %dh
		movb 	$25, %dl
		movb	$0, %bh
		movb 	$0x07, %bl
		movb	$1, %al
		movb	$0x13, %ah
		int 	$0x10
inf_loop:
		jmp	inf_loop

.data
MSG:	
		.asciz	"Hello loader"
MSG_END:


