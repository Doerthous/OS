.text
.code16

# ������ FAT12 ���̵�ͷ
jmp		boot_entry
nop

#################################            FAT12            ################################
# FAT BPB�ṹ
BS_OEMName: 	.ascii		"ForrestY"		# OEM String, ���� 8 ���ֽ�
BPB_BytsPerSec:	.word		512				# ÿ�����ֽ���
BPB_SecPerClus:	.byte		1				# ÿ�ض�������
BPB_RsvdSecCnt:	.word		1				# Boot ��¼ռ�ö�������
BPB_NumFATs:	.byte		2				# ���ж��� FAT ��
BPB_RootEntCnt:	.word		224				# ��Ŀ¼�ļ������ֵ
BPB_TotSec16:	.word		2880			# �߼���������
BPB_Media:		.byte		0xF0			# ý��������
BPB_FATSz16:	.word		9				# ÿFAT������
BPB_SecPerTrk:	.word		18				# ÿ�ŵ�������
BPB_NumHeads:	.word		2				# ��ͷ��(����)
BPB_HiddSec:	.long		0				# ����������
BPB_TotSec32:	.long		0				# ��� wTotalSectorCount �� 0 �����ֵ��¼������
BS_DrvNum:		.byte		0				# �ж� 13 ����������
BS_Reserved1:	.byte		0				# δʹ��
BS_BootSig:		.byte		0x29			# ��չ������� (29h)
BS_VolID:		.long		0				# �����к�
BS_VolLab:		.ascii		"Tinix0.01  "	# ����, ���� 11 ���ֽ�
BS_FileSysType:	.ascii		"FAT12   "		# �ļ�ϵͳ����, ���� 8���ֽ�
##############################################################################################

# boot���
# ע: ���з��Ŷ����ӵ�0x7c00, ��boot.lds
boot_entry:
		movw	$0, %ax						# ��ʼ��
		movw	%ax, %ds
		movw	%ax, %ss
		movw	%ax, %es
		movw	$0x8200, %sp

		# int 0x10, ah = 0x13 (bios�ж�, ��ʾ�ַ���)
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
		.org	510				# ����ֽ�
		.word	0xaa55			# ��������ֽ�55AA��AT&T����ļ������newline
		.org	0x168000		# 1.44M ����