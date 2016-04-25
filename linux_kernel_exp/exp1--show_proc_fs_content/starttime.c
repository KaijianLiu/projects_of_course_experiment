#include"func.h"
void startTime(){
	procFile = fopen("/proc/uptime","r");
        if(!procFile){
                perror("Error open file\n");
                exit(1);
        }
	if(fgets(lineBuffer,LINE_BUFFER_SIZE,procFile) != NULL){
			int cur,idle;
			sscanf(lineBuffer,"%d%d",&cur,&idle);
			int day   =  cur / (60*60*24);
			int hour  = (cur % (60*60*24)) / (60*60);
			int minute=((cur % (60*60*24)) % (60*60)) / 60;
			int second=((cur % (60*60*24)) % (60*60)) % 60;			
			printf("=================================================================\n");
			printf("|time sum since boot up   | %02d:%02d:%02d:%02d \n", day, hour, minute, second);
	}	
	printf("=================================================================\n");	
	fclose(procFile);

}
