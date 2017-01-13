#include <spio.h>
#include <spstring.h>
#include <spsnprintf.h>


void cstart(){
	char helloWolrd[] = "Hello world!\nHello lib!\n";
	char h[50];
	strrvs(helloWolrd);
	strcpy(helloWolrd, h);
	strrvs(h);
	puts(helloWolrd);
	puts(h);
	snprintf(h,50,"0x%%x\n0x%x", (u32)snprintf, (u32)cstart);
	puts(h);
	return;
}