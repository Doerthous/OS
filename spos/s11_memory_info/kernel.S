#include "../include/BIOS.inc"

.text
.code32
.extern _cstart
.extern _kernel_base, _kernel_end

.global kernel_entry
kernel_entry:
		movl $_stack_top, %ebp
		movl $_stack_bottom, %esp
		pushl	(MEMINFONR)
		pushl	$MEMINFO
		pushl $_kernel_end
		pushl $_kernel_base
		call _cstart

inf_loop:
		jmp inf_loop
	
.global _load_gdt
_load_gdt:
    movw    4(%esp), %ax
    movw    %ax, 6(%esp)
    lgdt    6(%esp)
    ret

.global _load_idt
_load_idt:
	movw	4(%esp), %ax
	movw	%ax, 6(%esp)
	lidt	6(%esp)
	ret

.global _sti
_sti:
	sti
	ret

.global _cli
_cli:
	cli
	ret

.global _hlt
_hlt:
	hlt
	ret
	
.global _switch_to_seg
_switch_to_seg:
    lcall   *4(%esp)            # lcall EA, EA->EIP, EA+4->CS
    ret

.global _int80syscall
_int80syscall:
	pushw	%ds
	pushw	%es
	pushw	%fs
	pushal
	#call	_HelloWorld
	popal
	popw	%fs
	popw	%es
	popw	%ds
	iret

.global _exception_divide_error
_exception_divide_error:
    #pushl $0
    #pushl $0
	movl	$0, %eax
    jmp exception_common

.global _exception_debug
_exception_debug:
    #pushl $0
    #pushl $1
	movl	$1, %eax
    jmp exception_common

.global _exception_nmi
_exception_nmi:
    #pushl $0
    #pushl $2
    movl	$2, %eax
	jmp exception_common

.global _exception_breakpoint
_exception_breakpoint:
    #pushl $0
    #pushl $3
    movl	$3, %eax
	jmp exception_common

.global _exception_overflow
_exception_overflow:
    #pushl $0
    #pushl $4
    movl	$4, %eax
	jmp exception_common

.global _exception_bounds_check
_exception_bounds_check:
    #pushl $0
    #pushl $5
    movl	$5, %eax
	jmp exception_common

.global _exception_inval_opcode
_exception_inval_opcode:
    #pushl $0
    #pushl $6
    movl	$6, %eax
	jmp exception_common

.global _exception_copr_not_avail
_exception_copr_not_avail:
    #pushl $0
    #pushl $7
    movl	$7, %eax
	jmp exception_common

.global _exception_double_fault
_exception_double_fault:
    #pushl $8
    movl	$8, %eax
	jmp exception_common

.global _exception_copr_seg_overrun
_exception_copr_seg_overrun:
    #pushl $0
    #pushl $9
    movl	$9, %eax
	jmp exception_common

.global _exception_inval_tss
_exception_inval_tss:
    #pushl $10
    movl	$10, %eax
	jmp exception_common

.global _exception_segment_not_present
_exception_segment_not_present:
    #pushl $11
    movl	$11, %eax
	jmp exception_common

.global _exception_stack_fault
_exception_stack_fault:
    #pushl $12
    movl	$12, %eax
	jmp exception_common

.global _exception_general_protection
_exception_general_protection:
    #pushl $13
    movl	$13, %eax
	jmp exception_common

.global _exception_page_fault
_exception_page_fault:
    #pushl $14
    movl	$14, %eax
	jmp exception_common

.global _exception_intel_reserved
_exception_intel_reserved:
    #pushl $0
    #pushl $15
    movl	$15, %eax
	jmp exception_common

.global _exception_copr_error
_exception_copr_error:
    #pushl $0
    #pushl $16
    movl	$16, %eax
	jmp exception_common

.global _exception_alignment_check
_exception_alignment_check:
    #pushl $17
    movl	$17, %eax
	jmp exception_common

.global _exception_machine_check
_exception_machine_check:
    #pushl $0
    #pushl $18
    movl	$18, %eax
	jmp exception_common

.global _exception_simd_fp
_exception_simd_fp:
    #pushl $0
    #pushl $19
    movl	$19, %eax
	jmp exception_common


.extern _exception
exception_common:
    pushal
    pushl	%fs
    pushl	%ds
    pushl	%es
	pushl	%eax
	call _exception
	popl	%eax
	popl	%es
	popl	%ds
	popl	%fs
	popal
    iret

#define INT0_15(irq) ;\
.global _intx ## irq ;\
_intx ## irq ## : ;\
	pushw	%ds ;\
	pushw	%es ;\
	pushw	%fs ;\
	pushal ;\
	movl	$irq, %eax ;\
	pushl	%eax ;\
	movl	(_g_int_vector + irq * 4), %eax ;\
	call	*%eax ;\
	popl	%eax ;\
	popal ;\
	popw	%fs ;\
	popw	%es ;\
	popw	%ds ;\
	iret ;\

INT0_15(0)
INT0_15(1)
INT0_15(2)
INT0_15(3)
INT0_15(4)
INT0_15(5)
INT0_15(6)
INT0_15(7)
INT0_15(8)
INT0_15(9)
INT0_15(10)
INT0_15(11)
INT0_15(12)
INT0_15(13)
INT0_15(14)
INT0_15(15)



# IO部分
# 添加于2016/11/10
# 参见《30天制作操作系统》
.global _io_in8
_io_in8:					# int io_in8(int port);
	movl	4(%esp), %edx
	movl	$0, %eax
	in		%dx, %al
	ret
.global _io_in16
_io_in16:					# int io_in16(int port);
	movl	4(%esp), %edx
	movl	$0, %eax
	in		%dx, %ax
	ret
.global _io_in32
_io_in32:					# int io_in32(int port);
	movl	4(%esp), %edx
	movl	$0, %eax
	in		%dx, %eax
	ret
.global _io_out8
_io_out8:					# void io_out8(int port, int data);
	movl	4(%esp), %edx	# port
	movb	8(%esp), %al	# data
	out		%al, %dx
	ret
.global _io_out16
_io_out16:					# void io_out16(int port, int data);
	movl	4(%esp), %edx	# port
	movw	8(%esp), %ax	# data
	out		%ax, %dx
	ret
.global _io_out32
_io_out32:					# void io_out32(int port, int data);
	movl	4(%esp), %edx	# port
	movl	8(%esp), %eax	# data
	out		%eax, %dx
	ret

.align 16
.data
_stack_top:
    .space 0x2000
_stack_bottom:

