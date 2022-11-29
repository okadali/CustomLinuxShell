#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "sys/wait.h"
#include "string.h"
#include <readline/readline.h>
#include <dirent.h> 

int main(int argc, char *argv[]) {
    char *input;
    while (1) {
        input = readline("MYSHELL>>");
        if(strlen(input) == 0) {
            continue;
        }
        

        int ix = 0;
        char *inputs[80];
        char *token = strtok(input," ");
        while( token != NULL ) {
            inputs[ix++] = token;
            token = strtok(NULL," ");
        }
        
        if(strcmp(inputs[0],"exit") == 0) {
            return 0;
        }
        else if(strcmp(inputs[0],"clear") == 0) {
            system("clear");
        }
        else if(strcmp(inputs[0],"cat") == 0) {
            printf("cat:%s\n",inputs[1]);
        }
        else if(strcmp(inputs[0],"ls") == 0) {
            DIR *d;
            struct dirent *dir;
            d = opendir(".");
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    printf("%s\n", dir->d_name);
                }
                closedir(d);
            }
        }
        else if(strcmp(inputs[0],"execx") == 0 && strcmp(inputs[1],"-t") == 0) {
            char *pass[80];
            int passIx = 0;
            for(int x = 2 ; x < ix ; x++) {
                pass[passIx++] = inputs[x];
            }
            if(passIx < 2) {
                printf("not enough parameters\n");
            }
            else {
                pass[passIx] = (char*)0;
                int f = fork();
                int i;
                if(f==0) {
                    i = execv("execx",pass);
                    perror("execx failed\n");
                    return 0;
                }
                else {
                    wait(&i);
                }
            }
        }
        else if(strcmp(inputs[0],"writef") == 0) {
            if (ix == 1) {
                printf("not enough parameters\n");
            }
            else {
                if(strcmp(inputs[1],"-f") == 0) {

                }
                else {
                    
                }
            }
        }
    }
    
    return 0;
}
