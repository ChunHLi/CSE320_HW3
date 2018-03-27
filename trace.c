#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int trace(char **args){
	int argcount = 3;
        int rowA = atoi(args[1]);
        int colA = atoi(args[2]);
	printf("%d\n",rowA);
	printf("%d\n",colA);
        int mA[rowA][colA];
        //matrixMaker(args,mA,rowA,colA,argcount);
        int i;
        for (i=0;i<rowA;i++){
                int j;
                for (j=0;j<colA;j++){
                        mA[i][j]=atoi(args[argcount]);
                        argcount += 1;
                }
        }
        int rowB = atoi(args[argcount]);
        int colB = atoi(args[argcount + 1]);
	printf("%d\n",rowB);
	printf("%d\n",colB);
	argcount += 2;
        int mB[rowB][colB];
        //matrixMaker(args,mB,rowB,colB,argcount); 
        int k;
        for (k=0;k<rowB;k++){
                int l;
                for (l=0;l<colB;l++){
                        mB[k][l]=atoi(args[argcount]);
                        argcount += 1;
                }
        }
        if (colA != rowB){
                printf("INVALID INPUT, column of A and row of B must match\n");
        } else {
                int sum = 0;
                int mC[rowA][colB];
                int a;
                int b;
                int c;
                for (a=0;a<rowA;a++){
                        for (b=0;b<colB;b++){
				mC[a][b]=0;
                                for (c=0;c<colA;c++){
                                        mC[a][b] += mA[a][c]* mB[c][b];                
                                }
                        }       
                }
                FILE *fp = fopen("part2_trace.dat", "w");
                for (a=0;a<rowA;a++){
                        for (b=0;b<colB;b++){
                                fprintf(fp,"%d",mC[a][b]);
                                if (b == colB - 1){
                                        fprintf(fp,"\n");
                                } else {
                                        fprintf(fp," ");
                                }
                        }
                }
                fclose(fp);
        }
        return 1;
}
int main(int argc, char** argv, char** envp){
        trace(argv);
	exit(EXIT_SUCCESS);
}
