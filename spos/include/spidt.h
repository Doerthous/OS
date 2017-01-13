#ifndef _SPIDT_H_
#define _SPIDT_H_

#include <sptypes.h>
#include <spio.h>
#include <spsnprintf.h>

// gata
#define INT32_GATE 		0x8e00
#define TSK_GATE 		0x8500
#define TRAP32_GATE 	0x8f00
#define CALL_GATE
struct gate_descriptor{
	unsigned	offset0: 16;
	unsigned	selector: 16;
	unsigned	attrib: 16;
	unsigned	offset1: 16;
};
#define GATEDESCSIZE 	sizeof(struct gate_descriptor)

// 中断和异常, IDT
#define KBASE	0x0000
#define OFFSET(x) (x)-KBASE
#define IDTE_NR	256 
typedef void (*idt_handler_t)();


void load_idt(u16 limit, u32 base);
void sti();
void cli();
void int80syscall();

#endif // _SPIDT_H_