#include "func.h"

#define CPU_INFO_NUM 9
#define INFO_MAX_CHAR 16


static char opts[CPU_INFO_NUM*2][INFO_MAX_CHAR]={
	"processor",      
	"vendor_id",       	
	"model name",      	
	"cpu MHz",         	
	"cache size",      	
	"core id",         	
	"cpu cores",       	
	"cache_alignment", 	
	"address sizes",
	
	"#processor    ",
	"#vendor       ",
	"model         ",
	"MHz           ",
	"cache size(KB)",
	"#core         ",
	"core num      ",
	"cache align   ",
	"address size  "
};                          	

static void copyContent(char* from, char* to, int max){
	while(*from++ != ':')
		;
	for(int i=0;i<max;i++){
		if(iscntrl(from[i]) ){
			to[i]='\0';
			break;
		}
		to[i]=from[i];
	}
}

int startWith(char* s, char*patt){
        int res = 1;
        do{
                if(*s != *patt){
                        res=0;
                        break;
                }
                s++;
                patt++;
        }while(*s !='\0' && *patt !='\0');
        return res;
}



void cpuInfo(){
	procFile = fopen("/proc/cpuinfo","r");
	if(!procFile){
		perror("Error open file\n");
		exit(1);
	}
	char tmp[50];
	while(fgets(lineBuffer,LINE_BUFFER_SIZE,procFile) != NULL){
		for(int i=0;i< CPU_INFO_NUM;i++){
			if(startWith(lineBuffer,opts[i])){
				copyContent(lineBuffer,tmp,50);
				printf("=================================================================\n");
				printf("|  %s  |  %s\n",opts[i+CPU_INFO_NUM], tmp);
			}
		}
	}	
	printf("=================================================================\n");
	fclose(procFile);
}
