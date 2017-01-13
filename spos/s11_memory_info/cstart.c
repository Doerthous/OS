#include <spio.h>
#include <spstring.h>
#include <spsnprintf.h>
#include <spgdt.h>
#include <spidt.h>
#include <spi8259.h>
#include <spmemory.h>


void cstart(u32 kernelBase, u32 kernelEnd, u32 biosInfo, u32 mInfoNR){
	init_gdt(0, kernelEnd - kernelBase);
	init_idt(0);
	char h[100];
	snprintf(h,50,"kernelBase: 0x%x\nkernelEnd: 0x%x\n", kernelBase, kernelEnd);
	puts(h);
	snprintf(h,100,"memoryInfo: 0x%x memoryInfoCnt: %1235161651651651561f0x%08d\n", ((memory_info_t *)biosInfo)->base0, -mInfoNR);
	puts(h);
	dump_memory();
	hlt();
	return;
}