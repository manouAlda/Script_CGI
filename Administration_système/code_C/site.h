#ifndef SITE_H
#define SITE_H

char** allouer(int line,int cols);
void site_file();
int count_site();
char* domainName (char* conf);
char** site_list (int list);
void site_navbar ();

#endif