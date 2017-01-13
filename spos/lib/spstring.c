#include <spstring.h>

/*
	不包括结尾字符'\0'
*/
u32 strlen(const char * str)
{
	u32 len = 0;
	for(; str[len]; ++len);
	return len;
}
/*
	没考虑to的大小
*/
u32 strcpy(const char * from, char *to)
{ // to 大小问题
	u32 len = strlen(from);
	u32 i = 0;
	for(; i < len; ++i)
		to[i] = from[i];
	return len;
}

void strrvs(char * str)
{
	u32 i, j = strlen(str)-1;
	char t;
	for(i = 0; i < j; ++i, --j){
		t = str[i];
		str[i] = str[j];
		str[j] = t;
	}
}