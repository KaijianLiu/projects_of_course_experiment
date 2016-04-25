#include"func.h"

void kernelInfo(){
	procFile = fopen("/proc/version","r");
	if(!procFile){
		perror("Error open file\n");
		exit(1);
	}
	//char tmp[50];
	fgets(lineBuffer,LINE_BUFFER_SIZE,procFile);
	int offset=0;
	while(*(lineBuffer+offset) !='('){
		offset++;
	}
	*(lineBuffer+offset)='\0';
	printf("%s\n",lineBuffer);
	
	fclose(procFile);

}
