#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>

static void psig_real(void);
static void psig_virtual(void);
static void psig_prof(void);

static void c1sig_real(void);
static void c1ig_virtual(void);
static void c1ig_prof(void);

static void c2sig_real(void);
static void c2sig_virtual(void);
static void c2sig_prof(void);

long unsigned int fib(unsigned int n);

static long p_real_secs = 0, c1_real_secs = 0, c2_real_secs = 0;
static long p_virtual_secs = 0, c1_virtual_secs = 0, c2_virtual_secs = 0;
static long p_prof_secs = 0, c1_prof_secs = 0, c2_prof_secs = 0;

static struct itimerval p_realt, c1_realt, c2_realt;
static struct itimerval p_virtt, c1_virtt, c2_virtt;
static struct itimerval p_proft, c1_proft, c2_proft;

int main(int argc, char**argv){
	long unsigned fib = 0;
	int pid1, pid2;
	unsigned int fibarg;
	int status;
	int i;
	if(argc < 3){
		printf("Usage: prob.C arg1 arg2 arg3\n");
	}
	
	//parent progress
	signal(SIGALRM, psig_real);
	signal(SIGVTALRM, psig_virtual);
	signal(SIGPROF, psig_prof);			
}

