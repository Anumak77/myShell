#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

extern char **environ;



void syserr(char * msg) {
    fprintf(stderr, "%s: %s\n", strerror(errno), msg);
    abort();
}

void clr() {
    char *argv[] = {NULL};
    execvp("clear", argv);
}

void dir(char *args[]) {
    char *argv[64]; 
    argv[0] = "ls";       
    argv[1] = "-al";
    execvp("ls", argv);
}

void envi() {
    for(int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

void cd(char *path) {
    char cwd[250];

        printf("%s\n", getcwd(cwd, 100));  
        setenv("PWD", cwd, 1);            
}


void echo(char *args[]) {
    char end[64]; 
    strcat(end, args[1]);
    for(int i = 2; args[i] != NULL; i++) {
        strcat(end, " ");
        strcat(end, args[i]);
        printf("%s\n", args[i]);
    }
    printf("%s\n", end);
    
}

void pausee() { // the pause command to stop the shell and only continue if pressed enter 
    printf("Press Enter to continue...\n");
    system("stty -echo");      
    while(getchar() != '\n');   
    system("stty echo");      
}

/* help: print out the readme file */
void help(char *path) {
    char *input = malloc(0);
    input = realloc(input, sizeof(char) * (strlen("cat ") + strlen(path) + strlen(" | more")));
    strcat(input, "cat ");
    strcat(input, path);
    strcat(input, " | more");

    system(input);   

    free(input);     
    input = NULL;
}


void IORedirection(char **args) {
    for(int i = 1; args[i - 1] !=NULL; i++){ // check for <
        if(strcmp(args[i - 1], "<") == 0){   
            if(access(args[i - 1], F_OK) != 0){   // this checks if the file exist
                perror("Error: File Not Found.");
            }
            else{
                
                freopen(args[i], "r", stdin);
                args[i - 1] = NULL;
                i++;
            }
            
        }

        if(strcmp(args[i - 1], ">") == 0){ // looks for >
            freopen(args[i], "w", stdout);
            args[i - 1] = NULL;
            i++;
        }

     
        if(strcmp(args[i - 1], ">>") == 0){ // looks for >> 
            freopen(args[i], "a", stdout);
            args[i - 1] = NULL;
            i++;
        }
    }
}