#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS 64                            // max # args
#define SEPARATORS " \t\n"     
                    // token separators
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

