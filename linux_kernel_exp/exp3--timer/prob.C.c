#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/time.h>

static void psig_real(void);
static void psig_virtual(void);
static void psig_prof(void);

static void c1sig_real(void);
static void c1sig_virtual(void);
static void c1sig_prof(void);

static void c2sig_real(void);
static void c2sig_virtual(void);
static void c2sig_prof(void);

long unsigned int fibonacci(unsigned int n);

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
	if(argc < 4){
		printf("Usage: prob.C arg1 arg2 arg3\n");
		return;
	}
	
	//parent progress
	signal(SIGALRM, psig_real);
	signal(SIGVTALRM, psig_virtual);
	signal(SIGPROF, psig_prof);	
	
	//初始化父进程 3种时间定器
	p_realt.it_interval.tv_sec = 9;
	p_realt.it_interval.tv_usec = 999999;
	p_realt.it_value.tv_sec = 9;
	p_realt.it_value.tv_usec = 999999;
	setitimer(ITIMER_REAL,&p_realt,NULL); 
	
	p_virtt.it_interval.tv_sec = 9;
	p_virtt.it_interval.tv_usec = 999999;
	p_virtt.it_value.tv_sec = 9;
	p_virtt.it_value.tv_usec = 999999;
	setitimer(ITIMER_VIRTUAL,&p_virtt,NULL); 
	
	p_proft.it_interval.tv_sec = 9;
	p_proft.it_interval.tv_usec = 999999;
	p_proft.it_value.tv_sec = 9;
	p_proft.it_value.tv_usec = 999999;
	setitimer(ITIMER_VIRTUAL,&p_proft,NULL); 
	
	pid1 = fork();
	if(pid1==0){
		//子进程1
		signal(SIGALRM, c1sig_real);
		signal(SIGVTALRM, c1sig_virtual);
		signal(SIGPROF, c1sig_prof);	
		
		//初始化父进程 3种时间定器
		c1_realt.it_interval.tv_sec = 9;
		c1_realt.it_interval.tv_usec = 999999;
		c1_realt.it_value.tv_sec = 9;
		c1_realt.it_value.tv_usec = 999999;
		setitimer(ITIMER_REAL,&c1_realt,NULL); 
		
		c1_virtt.it_interval.tv_sec = 9;
		c1_virtt.it_interval.tv_usec = 999999;
		c1_virtt.it_value.tv_sec = 9;
		c1_virtt.it_value.tv_usec = 999999;
		setitimer(ITIMER_VIRTUAL,&c1_virtt,NULL); 
		
		c1_proft.it_interval.tv_sec = 9;
		c1_proft.it_interval.tv_usec = 999999;
		c1_proft.it_value.tv_sec = 9;
		c1_proft.it_value.tv_usec = 999999;
		setitimer(ITIMER_PROF,&c1_proft,NULL); 
		
		fib = fibonacci(atoi(argv[1]));
		
		// 打印子进程 1所花费的 3种时间值
		getitimer(ITIMER_REAL,&c1_realt);
		printf("Child1 fib = %d \nChild1 RealTime=%ld sec : %ld msec\n",fib,c1_real_secs + 9 -c1_realt.it_value.tv_sec,999999-c1_realt.it_value.tv_usec/1000);
		getitimer(ITIMER_VIRTUAL,&c1_virtt);
		printf("Child1 VirtualTime=%ld sec : %ld msec\n",fib,c1_virtual_secs + 9 -c1_virtt.it_value.tv_sec,999999-c1_virtt.it_value.tv_usec/1000);
		getitimer(ITIMER_PROF,&c1_virtt);
		printf("Child1 ProfTime=%ld sec : %ld msec\n",fib,c1_prof_secs + 9 -c1_proft.it_value.tv_sec,999999-c1_proft.it_value.tv_usec/1000);
		
	}
	else {
		pid2 =fork();
		if(pid2==0){
			//子进程2
			signal(SIGALRM, c2sig_real);
			signal(SIGVTALRM, c2sig_virtual);
			signal(SIGPROF, c2sig_prof);	
			
			//初始化父进程 3种时间定器
			c2_realt.it_interval.tv_sec = 9;
			c2_realt.it_interval.tv_usec = 999999;
			c2_realt.it_value.tv_sec = 9;
			c2_realt.it_value.tv_usec = 999999;
			setitimer(ITIMER_REAL,&c2_realt,NULL); 
			
			c2_virtt.it_interval.tv_sec = 9;
			c2_virtt.it_interval.tv_usec = 999999;
			c2_virtt.it_value.tv_sec = 9;
			c2_virtt.it_value.tv_usec = 999999;
			setitimer(ITIMER_VIRTUAL,&c2_virtt,NULL); 
			
			c2_proft.it_interval.tv_sec = 9;
			c2_proft.it_interval.tv_usec = 999999;
			c2_proft.it_value.tv_sec = 9;
			c2_proft.it_value.tv_usec = 999999;
			setitimer(ITIMER_VIRTUAL,&c2_proft,NULL); 
			
			fib = fibonacci(atoi(argv[2]));
			
			// 打印子进程 2所花费的 3种时间值
			getitimer(ITIMER_REAL,&c2_realt);
			printf("Child2 fib = %d \nChild2 RealTime=%ld sec : %ld msec\n",fib,c2_real_secs + 9 -c2_realt.it_value.tv_sec,999999-c2_realt.it_value.tv_usec/1000);
			getitimer(ITIMER_VIRTUAL,&c2_virtt);
			printf("Child2 VirtualTime=%ld sec : %ld msec\n",fib,c2_virtual_secs + 9 -c2_virtt.it_value.tv_sec,999999-c2_virtt.it_value.tv_usec/1000);
			getitimer(ITIMER_PROF,&c2_virtt);
			printf("Child2 ProfTime=%ld sec : %ld msec\n",fib,c2_prof_secs + 9 -c2_proft.it_value.tv_sec,999999-c2_proft.it_value.tv_usec/1000);
			
			
		}else{
			fib = fibonacci(atoi(argv[3]));
			// 打印子进程 1所花费的 3种时间值
			getitimer(ITIMER_REAL,&c1_realt);
			getitimer(ITIMER_VIRTUAL,&c1_virtt);
			getitimer(ITIMER_PROF,&c1_virtt);
			printf("Parent fib = %d \nParent RealTime=%ld sec : %ld msec\n",fib,p_real_secs + 9 -p_realt.it_value.tv_sec,999999-p_realt.it_value.tv_usec/1000);
			printf("Parent VirtualTime=%ld sec : %ld msec\n",fib,p_virtual_secs + 9 -p_virtt.it_value.tv_sec,999999-p_virtt.it_value.tv_usec/1000);		
			printf("Parent ProfTime=%ld sec : %ld msec\n",fib,p_prof_secs + 9 -p_proft.it_value.tv_sec,999999-p_proft.it_value.tv_usec/1000);
			waitpid(0, &status, 0);
			waitpid(0, &status, 0);
		}
	}
	
}

long unsigned int fibonacci(unsigned int n){
	if(n >= 3) return fibonacci(n-1) + fibonacci(n-2);
	if(n==1) return 1;
	if(n==2) return 1;
	return -1;
}

static void psig_real(void){
	p_real_secs += 10;
}
static void psig_virtual(void){
	p_virtual_secs += 10;
}
static void psig_prof(void){
	p_prof_secs += 10;
}

static void c1sig_real(void){
	c1_real_secs+=10;
}
static void c1sig_virtual(void){
	c1_virtual_secs+=10;
}
static void c1sig_prof(void){
	c1_prof_secs+=10;
}

static void c2sig_real(void){
	c2_real_secs += 10;
}
static void c2sig_virtual(void){
	c2_virtual_secs += 10;
}
static void c2sig_prof(void){
	c2_prof_secs += 10;
}
