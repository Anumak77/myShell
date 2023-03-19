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
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"     
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
extern char **environ;

void clr();
void dir(char *args[]);
void envi();
void cd(char *path);
void echo(char *args[]);
void pausee();
void help(char *path);

void syserr(char * msg);

extern char **environ;

// all libraries and function callers that are used are called in here in this file 