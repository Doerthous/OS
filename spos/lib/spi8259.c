/*
    参考《30天制作操作系统》
*/

#include <spi8259.h>

void init_i8259()
{
    io_out8(PIC0_IMR,  0xff  ); /* 禁止主PIC所有中断 */
    io_out8(PIC1_IMR,  0xff  ); /* 禁止从PIC所有中断 */

    io_out8(PIC0_ICW1, 0x11  ); /* 边沿触发模式 */
    io_out8(PIC0_ICW2, 0x20  ); /* IRQ0-7由INT 0x20-0x27接收 */
    io_out8(PIC0_ICW3, 1 << 2); /* PIC1(从PIC)由IRQ2连接 */
    io_out8(PIC0_ICW4, 0x01  ); /* 无缓冲区模式 */

    io_out8(PIC1_ICW1, 0x11  ); /* 边沿触发模式 */
    io_out8(PIC1_ICW2, 0x28  ); /* IRQ8-15由INT 0x28-0x2f接收 */
    io_out8(PIC1_ICW3, 2     ); /* PIC1(从PIC)由IRQ2连接 */
    io_out8(PIC1_ICW4, 0x01  ); /* 无缓冲区模式 */

    io_out8(PIC0_IMR,  0xfb  ); /* 11111011 禁止除INT 0x22以外的所有中断 */
    io_out8(PIC1_IMR,  0xff  ); /* 11111111 禁止所有中断 */

    return;
}

void i8259_enable_isr(u8 irq){
	u8 data = 0;
	u8 which = 0;
	which = irq < 8 ? PIC0_IMR : PIC1_IMR;
	data = io_in8(which);
	io_out8(which,  data & ~(0x1 << irq)); 
}
void i8259_disable_isr(u8 irq){
	u8 data = 0;
	u8 which = 0;
	which = irq < 8 ? PIC0_IMR : PIC1_IMR;
	data = io_in8(which);
	io_out8(which,  data | (0x1 << irq)); 
}


/**
 * 参考洪明坚老师的EPOS
 */
void init_i8253(u32 freq)
{
    unsigned short latch = 1193182/freq;
    io_out8(0x43, 0x36);
    io_out8(0x40, latch&0xff);
    io_out8(0x40, (latch&0xff00)>>8);
}

// 有关键盘的信息，原作者网站 
// http://community.osdev.info/?(AT)keyboard
// 此处为加快中断处理速度，将数据保存在buf，
// 由主程序去不定时读取 
// 结构体定义在kn.h 
void inthandler21(int *esp)
{
    unsigned char data;
    io_out8(PIC0_OCW2, 0x61);   /* 通知主pic "irq-01"已处理 */
    //data = io_in8(PORT_KEYDAT); /* 注irq-xx的端口为(0x60 + xx)*/
    return;
}

void inthandler2c(int *esp)
{
    /*
        这里说明一下
        主PIC处理IRQ 0 ~ 7，其中2是从PIC
        从PIC处理IRQ 8 ~ 15，也就是说，IRQ 12对应在从PIC的4号 
    */
    unsigned char data;
    io_out8(PIC1_OCW2, 0x64);   /* 通知从pic "irq-04"已处理 */
    io_out8(PIC0_OCW2, 0x62);   /* 通知主pic "irq-02"已处理 */
    //data = io_in8(PORT_KEYDAT); // 显然，鼠标键盘共用数据端口 
    return;
}

