#include <spmemory.h>

/*
	在loader.S中获取了内存信息
	并保存在相应的地址出
*/
static memory_info_t * 	g_mem_info = (memory_info_t *)MEMINFOBASE;
static u32 *			g_mem_info_cnt = (u32 *)MEMINFOCNTBASE;

void dump_memory(){
	char buf[80];
	snprintf(buf, 80, "\n0x%x %d\n", g_mem_info, *g_mem_info_cnt);
	puts(buf);
	int i = 0;
	for(; i < *g_mem_info_cnt; ++i){
		snprintf(buf, 80, "0x%032x  0x%032x  %d\n", g_mem_info[i].base0, 
						g_mem_info[i].length0, g_mem_info[i].type);
		puts(buf);
	}
}
void * mallock(u32 size){}
void freek(void * p){}