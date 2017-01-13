#ifndef _SPIO_H_
#define _SPIO_H_

#include <sptypes.h>

#define A_PAGE_CHAR_CNT	2000 // 80*25
#define VGA_BASE 0xb8000

void putchar(char ch);
void puts(char * str);

#endif // _SPIO_H_