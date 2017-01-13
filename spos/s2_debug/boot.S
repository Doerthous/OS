.text
.code16

# 下面是 FAT12 磁盘的头
jmp		boot_entry
nop

#################################            FAT12            ################################
# FAT BPB结构
BS_OEMName: 	.ascii		"ForrestY"		# OEM String, 必须 8 个字节
BPB_BytsPerSec:	.word		512				# 每扇区字节数
BPB_SecPerClus:	.byte		1				# 每簇多少扇区
BPB_RsvdSecCnt:	.word		1				# Boot 记录占用多少扇区
BPB_NumFATs:	.byte		2				# 共有多少 FAT 表
BPB_RootEntCnt:	.word		224				# 根目录文件数最大值
BPB_TotSec16:	.word		2880			# 逻辑扇区总数
BPB_Media:		.byte		0xF0			# 媒体描述符
BPB_FATSz16:	.word		9				# 每FAT扇区数
BPB_SecPerTrk:	.word		18				# 每磁道扇区数
BPB_NumHeads:	.word		2				# 磁头数(面数)
BPB_HiddSec:	.long		0				# 隐藏扇区数
BPB_TotSec32:	.long		0				# 如果 wTotalSectorCount 是 0 由这个值记录扇区数
BS_DrvNum:		.byte		0				# 中断 13 的驱动器号
BS_Reserved1:	.byte		0				# 未使用
BS_BootSig:		.byte		0x29			# 扩展引导标记 (29h)
BS_VolID:		.long		0				# 卷序列号
BS_VolLab:		.ascii		"Tinix0.01  "	# 卷标, 必须 11 个字节
BS_FileSysType:	.ascii		"FAT12   "		# 文件系统类型, 必须 8个字节
##############################################################################################

# boot入口
# 注: 所有符号都链接到0x7c00, 见boot.lds
boot_entry:
		movw	$0, %ax						# 初始化
		movw	%ax, %ds
		movw	%ax, %ss
		movw	%ax, %es
		movw	$0x8200, %sp

		# int 0x10, ah = 0x13 (bios中断, 显示字符串)
		movw 	$(MSG), %bp 			
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

MSG:	
		.asciz	"Hello boot"
MSG_END:
		.org	510				# 填充字节
		.word	0xaa55			# 最后两个字节55AA，AT&T汇编文件最后是newline
		.org	0x168000		# 1.44M 软盘
