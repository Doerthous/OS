#include <spidt.h>

// gate
void set_gateDesc(struct gate_descriptor * pDesc, u16 selector,
					u32 offset, u16 attrib)
{
	pDesc->offset0 = offset & 0xffff;
	pDesc->selector = selector;
	pDesc->attrib = attrib;
	pDesc->offset1 = (0xffff0000&offset)>>16;
}

// 中断和异常, IDT
void (*g_int_vector[IDTE_NR])(u32 irq);

void int_default(u32 irq)
{
	char s[24];
	snprintf(s, 24, "interrupt irq: %u\t", irq);
	puts(s);
}

void exception(u32 code)
{
	char s[24];
	snprintf(s, 24, "exception code: %u\t", code);
	puts(s);
}

#define IDT_ECP(name) exception_ ## name
extern idt_handler_t
	IDT_ECP(divide_error),    IDT_ECP(debug),
    IDT_ECP(nmi),             IDT_ECP(breakpoint),
    IDT_ECP(overflow),        IDT_ECP(bounds_check),
    IDT_ECP(inval_opcode),    IDT_ECP(double_fault),
    IDT_ECP(copr_not_avail),  IDT_ECP(copr_seg_overrun),
    IDT_ECP(inval_tss),       IDT_ECP(segment_not_present),
    IDT_ECP(stack_fault),     IDT_ECP(general_protection),
    IDT_ECP(page_fault),      IDT_ECP(intel_reserved),
    IDT_ECP(copr_error),      IDT_ECP(alignment_check),
    IDT_ECP(machine_check),   IDT_ECP(simd_fp);
	
#define IDT_INT(name) intx ## name
extern idt_handler_t
	IDT_INT(0),IDT_INT(1), IDT_INT(2), IDT_INT(3),
    IDT_INT(4),IDT_INT(5), IDT_INT(6), IDT_INT(7),
    IDT_INT(8),IDT_INT(9), IDT_INT(10), IDT_INT(11),
    IDT_INT(12),IDT_INT(13), IDT_INT(14), IDT_INT(15);
	
struct gate_descriptor __idt[IDTE_NR];
void init_idt(u32 base)
{
	base = (u32)__idt;
	struct gate_descriptor * pIDTR = (struct gate_descriptor *)base;

	set_gateDesc(pIDTR+0, 8*2, (u32)&IDT_ECP(divide_error), INT32_GATE);
	set_gateDesc(pIDTR+1, 8*2, (u32)&IDT_ECP(debug), INT32_GATE);
	set_gateDesc(pIDTR+2, 8*2, (u32)&IDT_ECP(nmi), INT32_GATE);
	set_gateDesc(pIDTR+3, 8*2, (u32)&IDT_ECP(breakpoint), INT32_GATE);
	set_gateDesc(pIDTR+4, 8*2, (u32)&IDT_ECP(overflow), INT32_GATE);
	set_gateDesc(pIDTR+5, 8*2, (u32)&IDT_ECP(bounds_check), INT32_GATE);
	set_gateDesc(pIDTR+6, 8*2, (u32)&IDT_ECP(inval_opcode), INT32_GATE);
	set_gateDesc(pIDTR+7, 8*2, (u32)&IDT_ECP(double_fault), INT32_GATE);
	set_gateDesc(pIDTR+8, 8*2, (u32)&IDT_ECP(copr_not_avail), INT32_GATE);
	set_gateDesc(pIDTR+9, 8*2, (u32)&IDT_ECP(copr_seg_overrun), INT32_GATE);
	set_gateDesc(pIDTR+10, 8*2, (u32)&IDT_ECP(inval_tss), INT32_GATE);
	set_gateDesc(pIDTR+11, 8*2, (u32)&IDT_ECP(segment_not_present), INT32_GATE);
	set_gateDesc(pIDTR+12, 8*2, (u32)&IDT_ECP(stack_fault), INT32_GATE);
	set_gateDesc(pIDTR+13, 8*2, (u32)&IDT_ECP(general_protection), INT32_GATE);
	set_gateDesc(pIDTR+14, 8*2, (u32)&IDT_ECP(page_fault), INT32_GATE);
	set_gateDesc(pIDTR+15, 8*2, (u32)&IDT_ECP(intel_reserved), INT32_GATE);
	set_gateDesc(pIDTR+16, 8*2, (u32)&IDT_ECP(copr_error), INT32_GATE);
	set_gateDesc(pIDTR+17, 8*2, (u32)&IDT_ECP(alignment_check), INT32_GATE);
	set_gateDesc(pIDTR+18, 8*2, (u32)&IDT_ECP(machine_check), INT32_GATE);
	set_gateDesc(pIDTR+19, 8*2, (u32)&IDT_ECP(simd_fp), INT32_GATE);
		
	set_gateDesc(pIDTR+0+32, 8*2, (u32)&IDT_INT(0), INT32_GATE);
	set_gateDesc(pIDTR+1+32, 8*2, (u32)&IDT_INT(1), INT32_GATE);
	set_gateDesc(pIDTR+2+32, 8*2, (u32)&IDT_INT(2), INT32_GATE);
	set_gateDesc(pIDTR+3+32, 8*2, (u32)&IDT_INT(3), INT32_GATE);
	set_gateDesc(pIDTR+4+32, 8*2, (u32)&IDT_INT(4), INT32_GATE);
	set_gateDesc(pIDTR+5+32, 8*2, (u32)&IDT_INT(5), INT32_GATE);
	set_gateDesc(pIDTR+6+32, 8*2, (u32)&IDT_INT(6), INT32_GATE);
	set_gateDesc(pIDTR+7+32, 8*2, (u32)&IDT_INT(7), INT32_GATE);
	set_gateDesc(pIDTR+8+32, 8*2, (u32)&IDT_INT(8), INT32_GATE);
	set_gateDesc(pIDTR+9+32, 8*2, (u32)&IDT_INT(9), INT32_GATE);
	set_gateDesc(pIDTR+10+32, 8*2, (u32)&IDT_INT(10), INT32_GATE);
	set_gateDesc(pIDTR+11+32, 8*2, (u32)&IDT_INT(11), INT32_GATE);
	set_gateDesc(pIDTR+12+32, 8*2, (u32)&IDT_INT(12), INT32_GATE);
	set_gateDesc(pIDTR+13+32, 8*2, (u32)&IDT_INT(13), INT32_GATE);
	set_gateDesc(pIDTR+14+32, 8*2, (u32)&IDT_INT(14), INT32_GATE);
	set_gateDesc(pIDTR+15+32, 8*2, (u32)&IDT_INT(15), INT32_GATE);
	 
	set_gateDesc(pIDTR+0x80, 8*2, (u32)int80syscall, INT32_GATE);
	
	load_idt(IDTE_NR*GATEDESCSIZE-1, base);	

	int i = 0;
	for(; i < IDTE_NR; ++i){
		g_int_vector[i] = int_default;
	}
}