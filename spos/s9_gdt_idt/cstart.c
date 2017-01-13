#include <spio.h>
#include <spstring.h>
#include <spsnprintf.h>
#include <spgdt.h>
#include <spidt.h>


void cstart(u32 kernelBase, u32 kernelEnd){
	init_gdt(0, kernelEnd - kernelBase);
	init_idt(0);
	sti();
	//hlt();
	//HelloWorld();
	__asm__ __volatile__ ("int $0x0+32");
	__asm__ __volatile__ ("int $0x80");
	__asm__ __volatile__ ("int $3");
	
	cli();
	char helloWolrd[] = "Hello world!\nHello lib!\n";
	char h[50];
	strrvs(helloWolrd);
	strcpy(helloWolrd, h);
	strrvs(h);
	puts(helloWolrd);
	puts(h);
	snprintf(h,50,"kernelBase: 0x%x\nkernelEnd: 0x%x\n", kernelBase, kernelEnd);
	puts(h);
	return;
}