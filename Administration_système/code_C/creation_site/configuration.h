#ifndef CONFIGURATION_H
#define CONFIGURATION_H

char* balise_html (char* balise, char* attribut, char* text, char* fin_balise);
void print_balise_html (char* balise, char* attribut, char* text, char* fin_balise);
void classe (char* balise, char* text);
char* create_conf (char* conf);
void create_hosts (char* serverName);

void traitement_conf(char* reply);
void print_conf(char* username, char* reply);

#endif