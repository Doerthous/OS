#ifndef _SPI8259_H_
#define _SPI8259_H_

#include <sptypes.h>

#define PIC0_ICW1       0x0020
#define PIC0_OCW2       0x0020
#define PIC0_IMR        0x0021
#define PIC0_ICW2       0x0021
#define PIC0_ICW3       0x0021
#define PIC0_ICW4       0x0021
#define PIC1_ICW1       0x00a0
#define PIC1_OCW2       0x00a0
#define PIC1_IMR        0x00a1
#define PIC1_ICW2       0x00a1
#define PIC1_ICW3       0x00a1
#define PIC1_ICW4       0x00a1


void init_i8259(void);
void i8259_enable_isr(u8 irq);
void i8259_disable_isr(u8 irq);
void init_i8253(u32 freq);

#endif // _SPI8259_H_