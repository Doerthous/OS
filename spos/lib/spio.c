#include <spio.h>


void putchar(char ch){
	static u16 curr_pos = 0; 
	char * p = (char *)(VGA_BASE + (curr_pos << 1));
	switch(ch){ // 特殊字符
		case '\n':{
			curr_pos = (1+curr_pos/80)*80;
		} break;
		case '\r':{
			curr_pos = (1+curr_pos/80)*80;
		} break;
		case '\t':{
			curr_pos += 8;
			curr_pos %= A_PAGE_CHAR_CNT;
		} break;
		default:{ // 一般显示字符
			*p = ch;
			++curr_pos;
			curr_pos %= A_PAGE_CHAR_CNT;
		} break;
	}
}

void puts(char * str){
	for(; *str; ++str){
		putchar(*str);
	}
}