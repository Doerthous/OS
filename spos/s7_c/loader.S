.section .text
.code16
loader:
		#文本模式
		movb $0x0, %ah
		movb $0x3, %al
		int	 $0x10

		# 关中断
		cli

		# 加载 GDTR
		lgdt GDTPTR

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
		ljmp $0x10, $protect_mode

.code32
protect_mode:

#将内核复制到0x10-0000(1m)处
.equ KERNEL_SIZE, 0x200/4			# /4是每次复制4字节
move_kernel:
		movl $KERNEL_SIZE, %ecx
		movl $0x100000, %ebx
		movl $0xd200, %eax			# 内核代码在软盘0x5200处(0xd200=0x5200+0x8000)
copy:
		movl (%eax), %edx
		movl %edx, (%ebx)
		addl $4, %eax
		addl $4, %ebx
		loop copy

		# 跳到内核执行
		ljmp $0x10, $0x100000		
		
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
