/* 
Anushree Umak, s21343003
********************************************************************
I declare that this material, which I now submit for assessment,
is entirely my own work and has not been taken from the work of others
save and to the extent that such work 
has been cited and acknowledged within the text of my work.
*******************************************************************/


// #include <dirent.h>
// #include <unistd.h>
// #include <string.h>
// #include <stdio.h>
// #include <stdlib.h>
// #define MAX_BUFFER 1024                        // max line buffer
// #define MAX_ARGS 64                            // max # args
// #define SEPARATORS " \t\n"                     // token separators
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <signal.h>
#include "myshell.h"
#include "utility.c"






int main (int argc, char ** argv)
{
    char buf[MAX_BUFFER];                      // line buffer
    char * args[MAX_ARGS];                     // pointers to arg strings
    char ** arg;
    char *value;                               // working pointer thru args
    char * prompt = "==>" ;                    // shell prompt
    // keep reading input until "quit" command or eof of redirected input 






    char *pwd = strdup(getenv("PWD"));

    char *path = malloc(strlen(pwd) + strlen("/ca216/bin"));
    if(path == NULL) {
        syserr("There is a problem allocating memory");
    }

        
        
    if(argv[1]) { // batchmode
    const char* batchfile = argv[1];
    
    if(access(batchfile, F_OK) == 0)
    {                            
        freopen(batchfile, "r", stdin);
    }
    else
    {
        printf("File %s not found.\n", batchfile);
        exit(0);
        
    }
    }
    


    while (!feof(stdin)) {  //get command line from input
        fputs (prompt, stdout); // write prompt

        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
       
            arg = args; //  tokenize the input into args array
            *arg++ = strtok(buf,SEPARATORS);   // tokenise input
            while ((*arg++ = strtok(NULL,SEPARATORS)));

            // last entry will be NULL 
            value = args[0];
            if (value) {                     // if there's anything there
                // check for internal/external command 

                if (!strcmp(value,"clear")) { // "clear" command
                    system("clear");
                    continue;
                }

                else if (!strcmp(value,"quit")) {
                    break;  
                }                       // "quit" command
                                       // break out of 'while' loop

                else if (!strcmp(value,"cd")) { // "cd" command
                    if(args[1]) {
                        cd(args[1]);
                    }
                    else {
                        printf("%s\n", getenv("PWD"));
                    }
                }  

                
                else if (!strcmp(value,"pause")) {  // "pause" command
                    pausee();
                } 


                else if (!strcmp(value,"dir")) {  // "dir" command
                    dir(args);
                } 

                else if (!strcmp(value,"environ")) {  // "environ" command
                    envi();
                } 

                else if (!strcmp(value,"echo")) { // "echo" command
                    echo(args);
                } 

                else if (!strcmp(value,"help")) { // "help" command
                    help();
                } 


                else{ // forking
                    int pid = fork();
                    if (pid < 0){
                        fprintf(stderr, "Could not Fork\n");
                        return 0;
                    }
                    else if (pid == 0){
                        execvp(args[0], args);
                        printf("\n");
                    }
                        }

                /* else pass command onto OS (or in this instance, print them out) */
                arg = args;
                // while (*arg) {
                //     fprintf(stdout,"%s ",*arg++);
                //     fputs ("\n", stdout);
                
                
            }
        }
    }

    free(path);// frees all the variables
    path = NULL;
    return 0; 
}