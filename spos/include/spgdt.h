#ifndef _SPGDT_H_
#define _SPGDT_H_

#include <sptypes.h>


#define	GDTE_NR 8191
// segment attribute
#define K32_CODE 		0xc09a
#define K32_DATA 		0xc092
#define U32_CODE 		0xc0fa
#define U32_DATA 		0xc0f2



struct seg_descriptor{
	unsigned 	limit0: 16;
	unsigned 	base0: 16;
	unsigned	base1: 8;
	unsigned	attrib0: 8;
	unsigned	limit1: 4;
	unsigned 	attrib1: 4;
	unsigned	base2: 8;
};
#define SEGDESCSIZE 	sizeof(struct seg_descriptor)

void load_gdt(u16 limit, u32 base);
void switch_to_seg(u32 offset, u32 segIndex);


#endif // _SPGDT_H_