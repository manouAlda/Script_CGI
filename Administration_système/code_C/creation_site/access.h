#ifndef ACCESS_H
#define ACCESS_H

#include <stdio.h>

typedef struct {
    char ip[15];
    char date[20];
    char time[20];
    char get[50];
    char url[255];  
}Acces;

int count_line_access (char* name);
void pagination_access(int page, char* user,int first, int end);
void traitement_access(char* reply);
void print_access(char* username, char* reply);

#endif

