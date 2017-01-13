void cstart(){
	char * p = (char *)0xb8000;
	char helloWolrd[] = "Hello world!";
	int len = sizeof(helloWolrd);
	int i = 0;
	for(; i < len; ++i){
		*p = helloWolrd[i];
		p += 2;
	}
	return;
}