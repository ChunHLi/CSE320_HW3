#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

const int MAX_UINT64_T = 2^64;

int quit(){
	return 0;
}

int loop(int argc, char *argv[], char **envp){
	int app = 0;
	int status;
	char *args[255];
	do {
		if (argc != 2){
                	perror("INVALID NUMBER OF ARGUMENTS\n");
                	return (-1);
        	} else {
			FILE *fr = fopen(argv[1],"r");
                	if (fr == NULL){
                        	perror("ERROR OPENING FILE");
                        	return (-1);
                	}
                	memset(args,0, 255*sizeof args[0] );
                	char line[255];
                	int i = 1;
			while (fgets(line,255,fr)!=NULL){
                        	char* p = strchr(line,'\n');
                        	if (p != NULL){
                                	line[p-line]='\0';
                        	}
                        	char* token;
                        	for (token=strtok(line," "); token!=NULL; token=strtok(NULL," ")){
                                	args[i] = strdup(token);
                                	i += 1;
                        	}
                	}
			fclose(fr);
			printf("> Available applications:\n> 1) solver\n> 2) trace\n> 3) fib\n> 4) change input file name\n> 5) quit\n> Enter application number: ");
                	scanf("%d",&app);
			if (app<1||app>5){
				printf("\n Invalid input, try again");
				status = 1;
			}	
				
			if (app == 4){
				printf("Enter new input file name: ");
				scanf("%s",argv[1]);
				status = 1;
			} else if (app == 5){
				status = quit();
			} else {
				pid_t pid, wpid;
				int pidstatus;
				pid = fork();
				if (pid == 0){
					if (app==1){
						args[0] = "./solver";
					}
					if (app==2){
						args[0] = "./trace";
					}
					if (app==3){
						args[0] = "./fib";
					} 
					if (execve(args[0],args,envp)==-1){
						perror("Unsuccessful application");
					}
					exit(EXIT_FAILURE);
				} else if (pid < 0){
					perror("Error forking");
				} else {
					do{
						wpid = waitpid(pid, &pidstatus, WUNTRACED);
					} while (!WIFEXITED(pidstatus) && !WIFSIGNALED(pidstatus));
				}
				status = 1;
			}
                        
        	}
	} while (status);
        return 1;
}
int main(int argc, char *argv[], char** envp){
        loop(argc,argv,envp);
	return EXIT_SUCCESS;
}
