#ifndef _SPMEMORY_H_
#define _SPMEMORY_H_

#include <spbios.h>
#include <sptypes.h>
#include <spio.h>
#include <spsnprintf.h>


typedef struct _MEMINFO{
	u32 base0;
	u32 base1;
	u32 length0;
	u32 length1;
	u32 type;
} memory_info_t;

struct _MEMBLOCK{
	char signature[4];
	u32	size;
	u32 state;
	struct _mem_block * next;
};

void dump_memory();
void * mallock(u32 size);
void freek(void * p);

#endif // _SPMEMORY_H_