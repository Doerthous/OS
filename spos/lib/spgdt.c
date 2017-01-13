#include <spgdt.h>

// limit only use lower 20 bit
// atrri only use lower 8 bit and higher 4 bit
void set_segDesc(struct seg_descriptor * pDesc, u32 base,
					u32 limit, u16 attrib)
{
	pDesc->base0 = 0xffff & base;
	pDesc->base1 = (0x00ff0000&base)>>16;
	pDesc->base2 = (0xff000000&base)>>24;
	pDesc->limit0 = 0xffff & limit;
	pDesc->limit1 = (0xf0000&limit)>>16;
	pDesc->attrib0 = 0x00ff & attrib;
	pDesc->attrib1 = (0xf000&attrib)>>12;
}

struct seg_descriptor __gdt[GDTE_NR];
void init_gdt(u32 base, u32 kernelSize)
{
	base = (u32)__gdt;
	struct seg_descriptor * pDGTR = (struct seg_descriptor *)base;

	set_segDesc(pDGTR, 		0, 			0, 			0);
	set_segDesc(pDGTR+1, 	0, 			0x000fffff, K32_DATA);
	set_segDesc(pDGTR+2, 	0x00000000, kernelSize, K32_CODE);
	set_segDesc(pDGTR+4, 	0, 			0x000fffff, U32_DATA);
	set_segDesc(pDGTR+3, 	0, 			0, 			U32_CODE);


	load_gdt(SEGDESCSIZE*5-1, base);
}