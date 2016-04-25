#include"func.h"


//enum TYPE{STANDARD, SHORT, LONG};

FILE* procFile;
//struct timeval now;
//enum TYPE reportType;
//char repTypeName[16];

char* lineBuffer;
//int interval;
//int duration;
//int iteration;
char c1,c2;


void printHelp(){
	printf("Usage : watch [-c] [-C] [-k] [-t] [-m] [-d]\n");
	printf("	-c : cpu type\n");
	printf("	-C : cpu status\n");
	printf("	-k : kernel version\n");
	printf("	-t : time from start up,in format \"dd:hh:mm:ss\"\n");
	printf("	-m : memory infomation\n");
	printf("	-d : disk request\n");
}

int main(int argc, char* argv[]){
	lineBuffer = (char *)malloc(LINE_BUFFER_SIZE +1);
	//reportType = STANDARD;
	//strcpy(repTypeName,"Standard");
	if(argc < 2){
		printHelp();
		exit(1);	
	}
	sscanf(argv[1],"%c%c",&c1,&c2);
	if(c1 !='-'){
		printHelp();
		exit(1);
	}
	if(c2=='k'){
		printf("******* Kernel Version ***********\n");
		kernelInfo();
	}
	if(c2=='c'){
		printf("******* CPU Info ***********\n");
		cpuInfo();
	}
	if(c2=='C'){
		printf("******* C ***********\n");
		cpuTime();
	}
	if(c2=='t'){
		printf("******* time ***********\n");
		startTime();
	}
	if(c2=='m'){
		printf("******* Mem Info ***********\n");
		memInfo();
	}	
	if(c2=='d'){
		printf("******* disk request time ***********\n");
		diskRequest();
	}
	free(lineBuffer);
}
