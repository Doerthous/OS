/*
	Doerthous

	�޸��� 2016/11/10 19:09
	�޸���ustr,xstr,istrʹ���ܹ���paddingChar
	��������СminSize. ʵ����%08x��ʽ
*/

#include <spsnprintf.h>

// buffer size is deficient
#define BADBUF -99

static inline u32 isdigit(char ch) 
{
	return (ch >= '0' && ch <= '9');
}

/*
	����������ת��Ϊ��0��β���ַ���
	num:	�������޷�������
	str: 	������
	size: 	��������С(size >= num���ָ���+1)
	return: ����ɹ�, �����ַ�������(��������β0). ���򷵻�0
*/
static u32 ustr(u32 num, char * str, u32 size, s32 minSize, char paddingChar)
{
	char tab[16] = {'0','1','2','3','4','5','6','7','8','9'};
	s32 idx = size - 1;
	str[idx--] = 0;
	for(--minSize; idx >= 0; --minSize){
		str[idx--] = tab[num%10];
		num /= 10;
		if(!num) {		
			for(; minSize > 0 && idx >= 0; --minSize) // ���
				str[idx--] = paddingChar;
			u32 distance = ++idx;
			if(distance > 1) // ǰ��
				for(; idx <= size; ++idx)
					str[idx-distance] = str[idx];
			return size-distance-1; 
		}
	}
	return 0; 
}

static u32 istr(int num, char * str, u32 size, s32 minSize, char paddingChar)
{
	if(num < 0){
		num = -num;
		str[0] = '-';
		num = ustr(num, str+1, size-1, minSize-1, paddingChar); 
		return num == 0 ? num : num+1;
	}else{
		return ustr(num, str, size, minSize, paddingChar);
	}
}

static u32 str2u(const char * str, u32 size)
{
	u32 i = 1, num = 0;
	for(; size; i *= 10, --size){
		num += (str[size-1] - '0')*i;
	}
	return num;
} 

static u32 xstr(u32 num, char * str, u32 size, s32 minSize, char paddingChar)
{
	char tab[16] = {'0','1','2','3','4','5','6','7',
					'8','9','A','B','C','D','E','F'};
	s32 idx = size - 1;
	str[idx--] = 0;
	for(--minSize; idx >= 0; --minSize){
		str[idx--] = tab[num%16];
		num >>= 4;
		if(!num) {		
			for(; minSize > 0 && idx >= 0; --minSize) // ���
				str[idx--] = paddingChar;
			u32 distance = ++idx;
			if(distance > 1) // ǰ��
				for(; idx <= size; ++idx)
					str[idx-distance] = str[idx];
			return size-distance-1; 
		}
	}
	return 0; 
}

int snprintf(char * mem, u32 size, const char * fmt, ...)
{
	char tbuf[1024];
	va_list argPt;
	va_start(argPt, fmt);
	int i, j, t;
	for(i = 0, j = 0; j < size-1 && fmt[i]; ++i){
		if(fmt[i] != '%'){ // �����ַ� 
			mem[j] = fmt[i];
			++j;
		}else{ // ��ʽ������ 
			char padding = ' ';
			int numB = i+1, numE = i+1;
			while(isdigit(fmt[++i]));
			numE = i;
			s32 minSize = str2u(fmt+numB, numE-numB);
			if(fmt[numB] == '0')
				padding = '0';
			switch(fmt[i]){ // �жϸ�ʽ
				case 'd':{
					t = istr(va_arg(argPt, int), &mem[j], size-j, minSize, padding);
				} break;
				case 'u':{
					t = ustr(va_arg(argPt, int), &mem[j], size-j, minSize, padding);
				} break;
				case 'x':{
					t = xstr(va_arg(argPt, int), &mem[j], size-j, minSize, padding);	
				} break;
				default :{
					for(--numB, t = numB; t <= numE; ++t){
						mem[j+t-numB] = fmt[t];
					}
					t -= numB;
				}
			}
			if(t<0)return -1; // buffer���� 
			j += t;
		} 
	}
	mem[j] = 0;
	va_end(argPt);
	return 0;
}