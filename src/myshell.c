/* 
strtokeg - skeleton shell using strtok to parse command line
usage:
strtokeg
reads in a line of keyboard input at a time, parsing it into
tokens that are separated by white spaces (set by #define SEPARATORS).
can use redirected input if the first token is a recognised internal command, 
then that command is executed. otherwise the tokens are printed on the display.
internal commands:
clear - clears the screen
quit - exits from the program
********************************************************************
version: 1.0
date:    December 2003
author:  Ian G Graham
School of Information Technology
Griffith University, Gold Coast
ian.graham@griffith.edu.au
copyright (c) Ian G Graham, 2003. All rights reserved.
This code can be used for teaching purposes, but no warranty,
explicit or implicit, is provided.
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
    /* keep reading input until "quit" command or eof of redirected input */






    char *pwd = strdup(getenv("PWD"));
    // signal(SIGINT, sig_handler); 3

    char *path = malloc(strlen(pwd) + strlen("/ca216/bin"));
    if(path == NULL) {
        syserr("Error in memory allocation");
    }
    strcat(path, pwd);
    strcat(path, "/ca216/bin");

    char *manual = malloc(strlen(pwd) + strlen("/manual/readme.md"));
    if(manual == NULL) {
        syserr("Error in memory allocation");
    }
    strcat(manual, pwd);
    strcat(manual, "/manual/readme.md");

    setenv("ca216", path, 1);  

        
        
    if(argv[1]) { //batchmode
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
    


    while (!feof(stdin)) { 
        /* get command line from input */
        fputs (prompt, stdout); // write prompt

        if (fgets (buf, MAX_BUFFER, stdin )) { // read a line
            /* tokenize the input into args array */
            arg = args;
            *arg++ = strtok(buf,SEPARATORS);   // tokenise input
            while ((*arg++ = strtok(NULL,SEPARATORS)));

            // last entry will be NULL 
            value = args[0];
            if (value) {                     // if there's anything there
                /* check for internal/external command */

                if (!strcmp(value,"clear")) { // "clear" command
                    system("clear");
                    continue;
                }

                else if (!strcmp(value,"quit")) {
                    break;  
                }                       // "quit" command
                                       // break out of 'while' loop

                else if (!strcmp(value,"cd")) {
                    if(args[1]) {
                        cd(args[1]);
                    }
                    else {
                        printf("%s\n", getenv("PWD"));
                    }
                }  

                
                else if (!strcmp(value,"pause")) { 
                    pausee();
                } 


                else if (!strcmp(value,"dir")) { 
                    dir(args);
                } 

                else if (!strcmp(value,"environ")) { 
                    envi();
                } 

                else if (!strcmp(value,"echo")) {
                    echo(args);
                } 

                else if (!strcmp(value,"help")) {
                    help(manual);
                } 


                else{ 
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
    free(manual);
    manual = NULL;
    free(path);
    path = NULL;
    return 0; 
}