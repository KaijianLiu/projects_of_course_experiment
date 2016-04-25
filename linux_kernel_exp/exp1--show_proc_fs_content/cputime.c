#include"func.h"

/*
#define CPU_INFO_NUM 9
#define INFO_MAX_CHAR 16


static char opts[CPU_INFO_NUM*2][INFO_MAX_CHAR]={
	"cpu ",      
	"ctxt",       	
	"btime",      	
	"processes",         	
		
	"cpu time(jiffies) u/s/i  ",
	"contex switch times      ",
	"time sum since boot up   ",
	"number of created process",

};                          	
*/

void cpuTime(){
	procFile = fopen("/proc/stat","r");
        if(!procFile){
                perror("Error open file\n");
                exit(1);
        }

	//char tmp[50];
	while(fgets(lineBuffer,LINE_BUFFER_SIZE,procFile) != NULL){
		if(startWith(lineBuffer,"cpu ")){
			int user,d2,system,idle,d5,d6,d7;
			sscanf(lineBuffer+3,"%d%d%d%d%d%d%d",&user, &d2, &system, &idle, &d5, &d6, &d7);
			printf("=================================================================\n");
			printf("|cpu time(jiffies) u/s/i  | %d %d %d\n", user, system, idle);
		}else if(startWith(lineBuffer,"ctxt")){
			int t;
			sscanf(lineBuffer+4,"%d",&t);
			printf("=================================================================\n");
			printf("|contex switch times      | %d \n", t);
		}else if(startWith(lineBuffer,"processes")){
			int t;
			sscanf(lineBuffer+9,"%d",&t);
			printf("=================================================================\n");
			printf("|number of created process| %d \n", t);
		}
	}	
	
	printf("=================================================================\n");	
	fclose(procFile);

}
