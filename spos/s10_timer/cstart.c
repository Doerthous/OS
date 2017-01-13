#include <spio.h>
#include <spstring.h>
#include <spsnprintf.h>
#include <spgdt.h>
#include <spidt.h>
#include <spi8259.h>

void isr_timer(u32 irq){
	io_out8(0x0020, 0x60);   /* 通知主pic "irq-00"已处理 */
	putchar('T');
}
extern void (*g_int_vector[IDTE_NR])(u32 irq);
void cstart(u32 kernelBase, u32 kernelEnd){
	init_gdt(0, kernelEnd - kernelBase);
	init_idt(0);
	init_i8259();
	init_i8253(100);
	g_int_vector[0] = isr_timer;
    i8259_enable_isr(0);
    sti();

	char h[50];
	snprintf(h,50,"kernelBase: 0x%x\nkernelEnd: 0x%x\n", kernelBase, kernelEnd);
	puts(h);

	//__asm__ __volatile__ ("int $0x0+32");

	hlt();
	return;
}