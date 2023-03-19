/* 
Anushree Umak, s21343003
********************************************************************
I declare that this material, which I now submit for assessment,
is entirely my own work and has not been taken from the work of others
save and to the extent that such work 
has been cited and acknowledged within the text of my work.
*******************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

extern char **environ;



void syserr(char * msg) { // sends an error message and then aborts 
    fprintf(stderr, "%s: %s\n", strerror(errno), msg);
    abort();
}

void clr() { // clears the screen
    char *argv[] = {NULL};
    execvp("clear", argv);
}

void dir(char *args[]) { // shows all contents of the directory
    char *argv[MAX_BUFFER]; 
    argv[1] = "ls";       
    argv[2] = "-al";
    execvp("ls", argv);
}

void envi() { // shows all enviroment settings
    for(int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}

void cd(char *path) { // shows the current path, and if specified changes to the one mentioned
    char cwd[250];

        printf("%s\n", getcwd(cwd, 100));  
        setenv("PWD", cwd, 1);            
}


void echo(char *args[MAX_ARGS]) { // repeats anything that is said after echo
    // char end[MAX_BUFFER]; 
    // strcat(end, args[1]);
    for(int i = 1; args[i] != NULL; i++) {

        printf("%s\n", args[i]);
    }
    //  printf("%s\n", end);
    
}

void pausee() { // the pause command to stop the shell and only continue if pressed enter 
    printf("Press Enter to continue...\n");
    system("stty -echo");      
    while(getchar() != '\n');   
    system("stty echo");      
}



void help() {
    char command[1024] = "more ../manual/README.md";
    system(command);
}


void IORedirection(char **args) { // input/output redirecton
    for(int i = 1; args[i - 1] !=NULL; i++){ // checks for <
        if(strcmp(args[i - 1], "<") == 0){   
            if(access(args[i - 1], F_OK) != 0){   // this checks if the file exist
                perror("File Not Found.");
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