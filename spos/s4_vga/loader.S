.text
.code16

# 注: 所有符号都链接到0xc200, 见loader.lds
loader:
		# int 0x80, ah = 0, al = 3 80x25 16色文本
		# 显存地址b8000, 一个字符占两个字节,一个是字符,一个是显示属性
		movb $0x0, %ah
		movb $0x3, %al
		int	 $0x10

		movw $0xb800, %ax
		movw %ax, %es
		movw $MSG, %si 
		movw $0, %di
show_msg:
		movb (%si), %al
		movb %al, %es:(%di)
		addw $2, %di
		addw $1, %si
		cmpw $MSG_END, %si
		jne show_msg

inf_loop:
		jmp	inf_loop

.data
MSG:	
		.asciz	"VGA 80x25 16 colors mode"
MSG_END:


