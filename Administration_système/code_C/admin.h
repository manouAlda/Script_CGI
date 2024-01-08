#ifndef ADMIN_H
#define ADMIN_H

int hex_to_char(char* tab);
char* withoutHex(char* tab) ;

void print_html ();
void print_page ();
void print_home ();
void text_login ();
void main_page();
void noConnect();
void home();
void icon_login(char* name);
void sign(char* infos);
void login(char* infos);

int fichier_inscrit (char* infos);
int fichier_connecte ( char* infos);
char* test_user ();
void traitement(char* reply);

void print_content (char* username,char* reply,int mark);

void deconnexion(char* user);

#endif 
