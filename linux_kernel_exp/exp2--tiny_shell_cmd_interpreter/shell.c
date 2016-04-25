/*
* filename ：shell.c
* author : XuChongyang
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>

//#define DEBUG

//command
#define MAX_CMD_LINE_LEN  256
char text[MAX_CMD_LINE_LEN];
//word pase
#define MAX_CMD_LEN 60
typedef struct token{
	char val[MAX_CMD_LEN];
	struct token* next;
} Token;
//syntax pase
enum Type {NONE, CMD, PIPE, R_RE, L_RE, SEMICOLON, BG};
#define MAX_PARA_NUM 10
//EOF,  ls, |, >, <, ; , &
typedef struct cmd{
	enum Type t;
	struct cmd* next;
	struct cmd* pre;
	char* name;
	char* argv[MAX_PARA_NUM];
} COMMAND;

#define INIT_TOKEN(p) {  \
	p->val[0] = '\0';\
	p->next=NULL;    \
}
#ifdef DEBUG
#define PRINT_TOKEN(p) {        	\
       printf("====Tokens====\n");	\
	Token* t= p;            	\
        while(t){               	\
                printf("[%s]\n",t->val);\
                t=t->next;      	\
        }                       	\
} 
#else
#define PRINT_TOKEN(p)
#endif

#define INIT_COMMAND(p){ \
	p->t = NONE;	 \
	p->next = NULL;	 \
	p->pre = NULL;	 \
	p->name = '\0';	 \
	p->argv[0]=NULL; \
}

#ifdef DEBUG
#define PRINT_COMMAND(cmd) {					\
	printf("====COMMANDs====\n");				\
	COMMAND* p = cmd;					\
	while(p){						\
		printf("{\n  type : [%d],\n",p->t);		\
		printf("  name : [%s],\n",p->name);		\
		int i;						\
		for(i=0 ; p->argv[i] !=0 ; i++){		\
			printf("  argv[%d] :[%s],\n",i,p->argv[i]);\
		}						\
		printf("}\n");					\
		p=p->next;					\
	}							\
}
#else
#define PRINT_COMMAND(p)
#endif

Token* t_head = NULL;
COMMAND* c_head = NULL;

int isOperator(char c){
	if(c == '|' || c == '<' || c == '>' || c == ';' || c == '&'){
		return 1;
	}else{
		return 0;
	}
}

void word_parse(){
	if(text[0]=='\n' || text[0]=='\0') return;
	t_head = (Token*)malloc(sizeof(Token));
	INIT_TOKEN(t_head);
	Token* cur = t_head;
	int tk_index = 0;
	int pos=0;
	while(pos < MAX_CMD_LINE_LEN){
		if(text[pos] == '\n'){
			cur->val[tk_index]='\0';
		 	break;	
		}
		if(isOperator(text[pos]) == 0){
			cur->val[tk_index]=text[pos];
			tk_index++;
			pos++;
		}else{
			cur->val[tk_index]='\0';
			tk_index = 0;
			cur->next =(Token * )malloc(sizeof(Token));
			INIT_TOKEN(cur->next);
			cur = cur->next;
			switch(text[pos]){
				case '|':
					cur->val[0]='|';
					cur->val[1]='\0';
					break;
				case '>':
					cur->val[0]='>';
					cur->val[1]='\0'; 
					break;
				case '<':
					cur->val[0]='<';
					cur->val[1]='\0';
					break;
				case ';':
					cur->val[0]=';';
					cur->val[1]='\0'; 
					break;
				case '&':
				    cur->val[0]='&';
				    cur->val[1]='\0';
				    break;
               			 default:
					break;
			}
			pos++;
			cur->next = (Token * )malloc(sizeof(Token));
			INIT_TOKEN(cur->next);
			cur = cur->next;
		}
		
	}

	PRINT_TOKEN(t_head);
}

void syntax_parse(){
	if(text[0]=='\n' || text[0]=='\0') return;
	Token* hd = t_head;
	c_head = (COMMAND *)malloc(sizeof(COMMAND));
	INIT_COMMAND(c_head);
	COMMAND* cur_cmd = c_head;
	while(hd != NULL){
		
		int index=0;
		int cmd_index=0;
		for(;hd->val[index]==' ';index++)
			;//pre space 
		
		switch(hd->val[index]){
			case '|':
				cur_cmd->t    = PIPE;
				break;
			case '>':
				cur_cmd->t    = R_RE;
				break;
			case '<':
				cur_cmd->t    = L_RE;
				break;
			case ';':
				cur_cmd->t    = SEMICOLON;
				break;
			case '&':
				cur_cmd->t     = BG;
				break;
            case '\0':
                cur_cmd->t = NONE;
                break;
            default:
				cur_cmd->t    = CMD;
		}
		
		cur_cmd->argv[cmd_index] = &hd->val[index];
		
		for(;hd->val[index] != '\0';index++){
			if(hd->val[index] == ' '){
				hd->val[index]='\0';
				if(hd->val[index+1] != ' ' && hd->val[index+1] != '\0'){
					cmd_index++;
					cur_cmd->argv[cmd_index] = &hd->val[index+1];
				}
			}
		}
		cur_cmd->argv[cmd_index+1] = 0;
		cur_cmd->name = cur_cmd->argv[0];

		hd = hd->next;
		if(hd != NULL){
			cur_cmd->next = (COMMAND*)malloc(sizeof(COMMAND));
			INIT_COMMAND(cur_cmd->next);
			COMMAND* cc = cur_cmd;
			cur_cmd = cur_cmd->next;
			cur_cmd->pre = cc;
		}
	}
	
	PRINT_COMMAND(c_head);
}

void expr(){
	//wc < 1.txt | grep [1-9] > 2.txt [&];...
	COMMAND* cur = c_head;
	int fd_in,fd_out;
	int fifo[2];
expr_start:
        if(cur != NULL){
            if(cur->t != CMD){
                        cur=cur->next;
                        goto expr_start;
            }
            if(cur->next && cur->next->t == R_RE){
	    		if(!cur->next->next){
		    		printf("syntax error\n");
			    	goto end;
			    }
			    pid_t pid = fork();
			    if(pid == 0){
                       		fd_out = open(cur->next->next->name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IRGRP | S_IROTH);
				            dup2(fd_out,1);
				          int res =  execvp(cur->name,cur->argv);
					  if(res < 0){
					  	printf("can't exec [%s]\n",cur->name);
						exit(1);
					  }
			    }else if(pid > 0){
				    if(cur->next->next->next && cur->next->next->next->t == BG){
				    	  cur = cur->next->next->next->next;
				    }else{
					wait(pid);
					cur = cur->next->next->next;
				    }
				    
				    cur = cur->next->next->next;
				    goto expr_start;
			    }else{
				    printf("fork error\n");
				    goto end;
			    }	
            }else if(cur->next && cur->next->t == L_RE){
                if(!cur->next->next){
                                printf("syntax error\n");
                                goto end;
                }
                pid_t pid = fork();
                if(pid == 0){
				COMMAND* cp = cur->next->next->next;
				if(cp && cp->t == R_RE){
					fd_in = open(cur->next->next->name,O_RDONLY);
	                	    	close(0);
        	            		dup(fd_in);
                	    		close(fd_in);
					fd_out = open(cp->next->name,O_CREAT | O_WRONLY | O_TRUNC,S_IRUSR | S_IRGRP | S_IROTH);
				        close(1);
				        dup(fd_out);
				        close(fd_out);
				       int res =  execvp(cur->name,cur->argv);
					if(res < 0){
					  	printf("can't exec [%s]\n",cur->name);
						exit(1);
					  }
				 }else if(cp && cp->t == BG){
				 	fd_in = open(cur->next->next->name,O_RDONLY);
	                	    	close(0);
        	            		dup(fd_in);
                	    		close(fd_in);
				        int res = execvp(cur->name,cur->argv);
					if(res < 0){
					  	printf("can't exec [%s]\n",cur->name);
						exit(1);
					  }
				}else if(cp && cp->t == PIPE){
					pipe(fifo);
					pid_t pid2 = fork();
				    	//wc < 1.txt
				    	if(pid2==0){
						    fd_in = open(cur->next->next->name,O_RDONLY);
					            close(0);
						    dup(fd_in);
				        	    close(fd_in);
						    close(1);
						    dup(fifo[1]);
						    close(fifo[1]);
						    close(fifo[0]);
						    int res = execvp(cur->name,cur->argv);
						   if(res < 0){
					  		printf("can't exec [%s]\n",cur->name);
							exit(1);
					  	   }
					}else if(pid2 > 0){
						    close(0);
						    dup(fifo[0]);
						    close(fifo[0]);
						    close(fifo[1]);
						   int res =  execvp(cp->next->name,cp->next->argv);
						   if(res < 0){
						  	printf("can't exec [%s]\n",cur->next->name);
							exit(1);
					 	 }
					}else{
						    printf("fork error\n");
						    goto end;
					}
				}else{
					   fd_in = open(cur->next->next->name,O_RDONLY);
				           close(0);
				           dup(fd_in);
				           close(fd_in);
				           int res = execvp(cur->name,cur->argv);
					   if(res < 0){
					  	printf("can't exec [%s]\n",cur->name);
						exit(1);
					  }
				}
                }else if(pid > 0){
                        COMMAND* cp = cur->next->next->next;
                        if( (cp && cp->t == R_RE) || (cp && cp->t == PIPE) ){
				 wait(pid);				
				cur = cp->next->next;
			}else if(cp && cp->t==BG){
				cur = cp;
			}else{
				 wait(pid);
				 cur=cp;			
			}
			goto expr_start;
                 }else{
                                printf("fork error\n");
                                goto end;
               	 }       
               	 goto expr_start;
        }else if(cur->next && cur->next->t == PIPE){
			if(!cur->next->next){
                                printf("syntax error\n");
                                goto end;
                        }
                        pid_t pid = fork();
                        if(pid == 0){
                                pipe(fifo);
                                pid_t pid2 = fork();
				if(pid2==0){	
					close(1);
                                        dup(fifo[1]);
                                        close(fifo[1]);
                                        close(fifo[0]);
                                        int res = execvp(cur->name,cur->argv);
					if(res < 0){
					  	printf("can't exec [%s]\n",cur->name);
						exit(1);
					  }
				}else if(pid2>0){
					wait(pid2); 
					close(0);
                                        dup(fifo[0]);
                                        close(fifo[0]);
                                        close(fifo[1]);
                                        int res = execvp(cur->next->next->name,cur->next->next->argv);
					if(res < 0){
					  	printf("can't exec [%s]\n",cur->name);
						exit(1);
					  }

				}
			}else if(pid > 0){	
				wait(pid);
				cur = cur->next->next->next;
				goto expr_start;
			}
	}else if(cur->next && (cur->next->t==SEMICOLON || cur->next->t==BG)){
			pid_t pid3=fork();
                        if(pid3 == 0){
                                int res = execvp(cur->name,cur->argv);
				if(res < 0){
					  	printf("can't exec [%s]\n",cur->name);
						exit(1);
					  }
                        }else if(pid3 > 0){
				if(cur->next->t != BG)
                                	wait(pid3);
				cur=cur->next;
                                goto expr_start;
                        }else{ 
                                printf("fork error\n");
                                goto end;
                        }

	}
        if(cur && !cur->next){
		pid_t pid3=fork();
		if(pid3 == 0){
			int res = execvp(cur->name,cur->argv);	
			if(res < 0){
			  	printf("can't exec [%s]\n",cur->name);
				exit(1);
			  }
		}else if(pid3 > 0){
			wait(pid3);	
			goto end;
		}else{	
			printf("fork error\n");
			goto end;
		}
	}	
    }
end:;
}
void resfree(){
	COMMAND* c = c_head;
	while(c!=NULL){
		COMMAND* n = c->next;
		free(c);
		c=n;
	}
	c_head=NULL;
	Token* t = t_head;
	while(t!=NULL){
		Token* n = t->next;
		free(t);
		t=n;
	}
	t_head=NULL;
}

void promote(){
	fputs("$ ",stdout);
}

int main(){
	char exit[5]={"exit"};
	promote();
	memset(text,0, sizeof(char) *  MAX_CMD_LINE_LEN);
	fgets(text, MAX_CMD_LINE_LEN, stdin);
	while( strncmp(text,exit,4) != 0 ){
		word_parse();
		syntax_parse();
		expr();
		resfree();
		promote();
		memset(text, 0, sizeof(char) *  MAX_CMD_LINE_LEN);
		fgets(text, MAX_CMD_LINE_LEN, stdin);
//		printf("pid: %d\n",getpid());
	}
}

