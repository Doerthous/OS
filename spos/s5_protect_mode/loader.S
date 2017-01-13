.section .text
.code16
loader:
		#文本模式
		movb	$0x0, %ah
		movb	$0x3, %al
		int		$0x10

		# 关中断
		cli

		# 加载 GDTR
		lgdt	GDTPTR

		# 打开地址线A20
		in	$0x92, %al
		or	$2, %al
		out	%al, $0x92


		# 准备切换到保护模式
		movl %cr0, %eax
		or $1, %eax
		movl %eax, %cr0

		#将以下段寄存器切到data段
		movw $0x8, %ax
		movw %ax, %ds
		movw %ax, %es
		movw %ax, %gs
		movw %ax, %fs
		movw %ax, %ss

		# 切换到保护模式 0x10 -> cs
		ljmp	$0x10, $protect_mode

.code32
protect_mode:

		movl $0xb8000, %eax
		movw $MSG, %si 
show_msg:
		movb (%si), %bl
		movb %bl, (%eax)
		addl $2, %eax
		addw $1, %si
		cmpw $MSG_END, %si
		jne show_msg

inf_loop:
		jmp	inf_loop

		
.data
#临时GDT
TGDT:
		.long	0x00000000
		.long	0x00000000			#empty GDTE
		.long	0x0000ffff
		.long	0x00cf9200			#data 4G
		.long	0x0000ffff
		.long	0x00cf9a00			#code 4G
GDTPTR:
		.word TGDT-GDTPTR				# Temp gdt limit
		.long TGDT						# Temp gdt base

MSG:	
		.ascii "Protect mode                                                                    "
		.ascii "In this mode, you can access the memory whose address is higher than 1M"
MSG_END:
