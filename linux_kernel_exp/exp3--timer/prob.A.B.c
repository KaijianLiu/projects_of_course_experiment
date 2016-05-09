#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>

static long int pass = 0;
static struct timeval theTime;
static struct timeval  now;
static struct itimerval rt;

static void sig_real(int);

static void init_gtd(){
	gettimeofday(&theTime,NULL);
	gettimeofday(&now,NULL);
	signal(SIGALRM, sig_real);
        	
        rt.it_interval.tv_sec  = 1;
        rt.it_interval.tv_usec = 0;
        rt.it_value.tv_sec = 1;
        rt.it_value.tv_usec = 0;
        
        setitimer(ITIMER_REAL,&rt,NULL);

}
static long get_time_of_day(){
	long pass  = now.tv_sec - theTime.tv_sec;
	return pass;
} 
static void get_time_of_day2(struct timeval* t){
	t->tv_sec  = now.tv_sec  - theTime.tv_sec; 
	t->tv_usec = now.tv_usec - theTime.tv_usec; 
}

int main(){	
	printf("====Problem A======\n");
	init_gtd();
	long begin = get_time_of_day();
	int i;
	for(i=0;i<1000*10000;i++){
		printf(" \b");
	}	
	long end = get_time_of_day();
	printf("time passed [%ld] seconds\n",end-begin);
	printf("===Problem B=======\n");
	for(i=0;i<1000*10000;i++){
                printf(" \b");
        }     	
	struct timeval t;
	get_time_of_day2(&t);
	printf("current time: sec[%ld],usec[%ld]\n", t.tv_sec, t.tv_usec);
}

static void sig_real(int a){
	pass++;
	gettimeofday(&now,NULL);
//	printf("tv_sec = %ld, tv_usec = %ld,a = %d\n", now.tv_sec, now.tv_usec,a);
}
