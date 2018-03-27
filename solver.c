#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
const int MAX_UINT64_T = 2^64;

int solverHelper(float args[],int try, int deg){
        int i;
        int d = deg;
        int sum = 0;
        for (i=0;i<=deg;i++){
                sum += (args[i]*(try^d));
                d -= 1;
        }
        return sum;
}

int solver(char **args){
        int deg = atoi(args[1]);
        float tol = atof(args[2]);
        float lB = atof(args[3]);
        float rB = atof(args[4]);
        float coef[MAX_UINT64_T];
        int i;
        for (i=0;i<=deg;i++){
                coef[i] = atof(args[5+i]);
        }
        coef[i] = 0;
        float c;
        int n = 0;
        while (n<10000){
                c = (lB+rB)/2;
                if (((rB-lB)/2 < tol) || solverHelper(coef, c, deg) == 0){
                        FILE *fp = fopen("part2_solver.dat", "w");
                        fprintf(fp,"%f",c);
                        fclose(fp);
                        break;
                }
                if (solverHelper(coef,c,deg)*solverHelper(coef,lB,deg) > 0){
                        lB = c;
                } else {
                        rB = c;
                }
                n += 1;
        }
        if (n >= 10000){
                printf("Root not found\n");
        }
        return 1;
}

int main(int argc, char** argv, char** envp){
	solver(argv);
	exit(EXIT_SUCCESS);
}
