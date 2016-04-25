#include "func.h"

#define MEM_INFO_NUM 3
#define INFO_MAX_CHAR 16

static char opts[MEM_INFO_NUM*2][INFO_MAX_CHAR]={
	"MemTotal",      
	"MemFree",       	
	"MemAvailable",      	
	
	"Total",
	"Free ",
	"Avila"
};                          	

static void copyContent(char* from, char* to, int max){
	while(*from++ != ':')
		;
	while(*from++ == ' ')
		;
	for(int i=0;i<max;i++){
		if(iscntrl(from[i]) ){
			to[i]='\0';
			break;
		}
		to[i]=from[i];
	}
}


void memInfo(){
	procFile = fopen("/proc/meminfo","r");
	if(!procFile){
		perror("Error open file\n");
		exit(1);
	}
	char tmp[50];
	while(fgets(lineBuffer,LINE_BUFFER_SIZE,procFile) != NULL){
		for(int i=0;i< MEM_INFO_NUM;i++){
			if(startWith(lineBuffer,opts[i])){
				copyContent(lineBuffer,tmp,50);
				printf("=============================================\n");
				printf("|  %s  |  %s\n",opts[i+MEM_INFO_NUM], tmp);
			}
		}
	}	
	printf("=============================================\n");
	fclose(procFile);

	procFile = fopen("/proc/loadavg","r");
	if(!procFile){
		perror("Error open file\n");
		exit(1);
	}
	fgets(lineBuffer,LINE_BUFFER_SIZE,procFile);
	float one_minute=0,five_minute=0,fifteen_minute=0;
	char s[20];
	int max_pid=0;

	sscanf(lineBuffer,"%f%f%f%s%d",&one_minute, &five_minute, &fifteen_minute, s, &max_pid);
	
	int index=0;
        while(*(s+index) !='/'){
                index++;
        }
        *(s+index)='\0';
        index++;

	printf("| lavg_1/1 minute    | %f \n",one_minute);
	printf("=============================================\n");
	printf("| lavg_2/5 minutes   | %f \n",five_minute);	
	printf("=============================================\n");
	printf("| lavg_3/15minutes   | %f \n",fifteen_minute);
	printf("=============================================\n");
	printf("| nr_running| %s\n",s);
	printf("=============================================\n");
	printf("| nr_thread | %s\n",s+index);
	printf("=============================================\n");
	printf("| max_pid   | %d\n",max_pid);
	printf("=============================================\n");
}	
