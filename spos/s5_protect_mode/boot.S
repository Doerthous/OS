.code16
.section .text

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

# 读取扇区到0x0820:0内存
# 软盘结构 80（磁道）x18（扇区）x512 bytes(扇区的大小)x2（双面） = 1440 x1024 bytes = 1440 KB = 1.44MB
# ch: 磁道号, 需要读入CYLS条磁道
# dh: 磁头号, 1.44M软盘双面  
# cl: 扇区号, 1.44M软盘一条磁道18个扇区
.equ CYLS, 10 								# 读入内存的磁道数
		movw	$0, %ax						# 初始化
		movw	%ax, %ds
		movw	%ax, %ss
		movw	%ax, %es
		movw	$0x8200, %sp

		#假设整个软盘读到0x8000内存处
		movw	$0x0820, %ax				# 0x8200跳过引导扇区			
		movw	%ax, %es
		movb	$0, %ch						# 磁道号
		movb	$0, %dh						# 磁头号
		movb	$2, %cl 					# 扇区号, 从2开始跳过了引导扇区
read_a_section:
		movw	$0, %si						# 失败次数
retry:
		movb	$0x02, %ah					# int 0x13, ah = 0x02 读取磁盘扇区
		movb	$1, %al						# 扇区数
		movw	$0, %bx						# es:bx 数据缓冲区地址
		movb	$0x00, %dl					# dh/dl 磁头号/驱动器号(0x00,0x01为软盘,0x80,0x81为硬盘)
		int		$0x13
		jnc		next_section				
		addw	$1, %si 					# 读取失败
		cmp		$5, %si
		jae		inf_loop
		movb	$0x00, %ah					# int 0x13, ah = 0x00 磁盘复位
		movb	$0x00, %dl
		int		$0x13
		jmp		retry
next_section:
		movw	%es, %ax					# 缓冲区增加一个扇区大小(0x200, 512B)
		addw	$0x0020, %ax
		movw	%ax, %es					
		addb	$1, %cl 					# 下一个扇区
		cmp		$18, %cl 					# cl <= 18, 1.44M软盘一条磁道只有18个扇区
		jbe		read_a_section				
		movb	$1, %cl 					# 重置扇区到1号扇区
		addb	$1, %dh 					# 下一个磁面
		cmp		$2, %dh						# dh < 2, 1.44M软盘有双面
		jb		read_a_section				
		movb	$0, %dh						# 重置磁头到0号磁头
		addb	$1, %ch						# 下一条磁道
		cmp		$CYLS, %ch					# 需要读取的磁道数
		jb		read_a_section				# ch < CYLS,
		ljmp	$0,$0xc200					# 跳到loader执行(loader代码在软盘0x4200处, 0xc200=0x4200+0x8000)

inf_loop:
		jmp inf_loop	
					
		.org	510				# 填充字节
		.word	0xaa55			# 最后两个字节55AA，AT&T汇编文件最后是newline
		.org	0x168000		# 1.44M 软盘
