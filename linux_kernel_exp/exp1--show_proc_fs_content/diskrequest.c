#include"func.h"

#define NAME_INDEX 13

void diskRequest(){
	procFile = fopen("/proc/diskstats","r");
	if(!procFile){
		perror("Error open file\n");
		exit(1);		
	}
	printf("================================================\n");
	while(fgets(lineBuffer,LINE_BUFFER_SIZE,procFile) != NULL){
		if(startWith(lineBuffer+NAME_INDEX,"sda ")){
			int read,write,t;
			sscanf(lineBuffer+NAME_INDEX+4,"%d%d%d%d%d%d%d%d%d%d%d",&read,&t,&t,&t,&write,&t,&t,&t,&t,&t,&t);
			printf("all disk request time : %d\n",read+write);
		}
	}
	printf("================================================\n");
	fclose(procFile);
}
