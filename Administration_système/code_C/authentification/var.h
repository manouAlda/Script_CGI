#ifndef LOG_H
#define LOG_H

#include <stdio.h>

typedef struct {
    char month[10];
    char date[20];
    char time[10];
    char host[255];
    char action[255];
    char infos[500];   
}Auth;

int count_line ();
char* month_gasy (char* month);
char* andro_gasy (int jour,char* month,int annee);
void pagination_auth(int page, int search, char* user, int first, int end);
void traitement_auth(Auth* lines, int k, int start, int final, int first, int end,int search, char* thing, char* user);
void print_auth(char* user, char* url);

#endif
