#ifndef INFO_HEADER
#define INFO_HEADER

#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define LINE_BUFFER_SIZE 100

extern FILE* procFile;
//struct timeval now;
//enum TYPE reportType;
//char repTypeName[16];

extern char* lineBuffer;
//int interval;
//int duration;
//int iteration;


extern void cpuInfo();
extern void kernelInfo();
extern void memInfo();
extern void cpuTime();
extern void startTime();
extern void diskRequest();
extern int startWith(char*, char*);

#endif	
