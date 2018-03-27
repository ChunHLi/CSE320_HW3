#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <inttypes.h>


int fib(char **args){
        int n = atoi(args[1]);
        if (n < 0) {
                printf("INVALID INPUT, MUST BE >= 0\n");
        }
	FILE *fp = fopen("part2_fib.dat", "w");
	if (n == 0){
                fprintf(fp,"0");
        } 
	if (n == 1){
                fprintf(fp,"1");
        } else {
                uint64_t stor[255];
		uint64_t current;
                stor[0] = 0;
                stor[1] = 1;
                int i;
                for (i=2;i<=n;i++){
			stor[i] = stor[i-1]+stor[i-2];
			current = stor[i];
                }
                fprintf(fp,"%"PRIu64"\n",current);
        }
	fclose(fp);
        return 1;
}

int main(int argc, char** argv, char** envp){
        fib(argv);
	exit(EXIT_SUCCESS);
} 
