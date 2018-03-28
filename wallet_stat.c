#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

struct wallets {
    uint32_t key;
    int money;
};

void print_help() {}

uint32_t key_gen() {
    uint32_t key = rand() & 0xff;
    key |= (rand() & 0xff) << 8;
    key |= (rand() & 0xff) << 16;
    key |= (rand() & 0xff) << 24;

    return key;
}

uint32_t money_gen() {
    uint32_t money = rand() % 100;

    return money;
}

void generate_wallets(int num_wallets, struct wallets* wallet) {
    int i = 0;
    for (i; i < num_wallets; ++i) {
        wallet[i].key = key_gen();
        wallet[i].money = money_gen();
    }
}

void print_wallets(FILE* fp, int num_wallets, struct wallets* wallet) {
    int i = 0;
    for (i; i < num_wallets; ++i)
        fprintf(fp, "wallet: %x; money: %d\n", wallet[i].key, wallet[i].money);
}

int main(void) {
    printf("Welcome to the BTC wallet tracker.\n");
    srand(time(NULL));

    char* filename = (char*)malloc(255);
    char* command = (char*)malloc(255);
    FILE* fp = NULL;
    int num_wallets;
    int is_generated = 0;
    int is_printed = 0;
    pid_t pid, wpid;
    int status;

    printf("Please enter the file name that contains number of wallets: ");
    scanf("%s", filename);
    fp = fopen(filename, "r");
    if (!fp) {
	printf("FILE DOES NOT EXIST");
	return 0;
    }
    fscanf(fp, "%d", &num_wallets);
    struct wallets* wallet = (struct wallets*)malloc(num_wallets * sizeof(struct wallets));

    printf("Type 'help' for list of available commands.\n");
prompt:
    printf("prompt> ");
    scanf("%s", command);
    if (strcmp(command, "help") == 0) {
        if ((pid = fork()) == 0) {
	    char *args[]={"./print_help",NULL};
            execvp(args[0], args);
		printf("exec failed: %s\n",strerror(errno));
            exit(0);
        } else {
		do {
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
        sleep(1);
        goto prompt;
    }
    else if (strcmp(command, "generate") == 0) {
        if (!is_generated) {
            is_generated = 1;
            generate_wallets(num_wallets,wallet);
        }
        else
            printf("Wallets are already generated.\n");
        goto prompt;
    }
    else if (strcmp(command, "print") == 0) {
        if (!is_printed && is_generated) {
            is_printed = 1;
            filename = "wallets_info.dat";
            fp = fopen(filename, "w");
            print_wallets(fp, num_wallets, wallet);
        }
        else if (!is_generated){
		printf("Wallet have yet to be generated.\n");
	} 
	else {
            printf("Wallets are already printed.\n");
        }
	goto prompt;
    }
    else if (strcmp(command, "quit") == 0){
	free(filename);
        free(command);
	return 0;
    }
    else {
        printf("Unknown command.\n");
        goto prompt;
    }

    return 0;
}
