#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../site.h"

char* balise_html (char* balise, char* attribut, char* text, char* fin_balise){
    char* instruction = malloc (1000);

    if (strcmp(fin_balise,"")==0) {
        sprintf( instruction , "\n<%s %s>\n\t %s ",balise,attribut, text );
    }
    else if (strcmp(fin_balise,"")!=0){
        sprintf( instruction , "\n<%s %s>\n\t %s \t\n</%s>\n",balise,attribut, text, fin_balise );
    }
    return instruction;
}

void print_balise_html (char* balise, char* attribut, char* text, char* fin_balise){
    if (strcmp(fin_balise,"")==0){ 
        printf("\n<%s %s>\n\t %s ",balise,attribut, text );
    }
    else if (strcmp(fin_balise,"")!=0){
        printf("\n<%s %s>\n\t %s \t\n</%s>\n",balise,attribut, text, fin_balise );
    }
}

void classe (char* balise, char* text){
    printf("\n%s { \n %s }\n", balise, text);
}

void create_hosts (char* serverName){
    FILE* file = NULL;
    char* content = malloc(100);
    char* contenu = malloc(255);
    int test = 0;

    sprintf ( content,"127.0.0.1     %s", serverName);

    file = fopen ("/etc/hosts", "r");

    for (int i=0; feof(file)!=1; i++){
        fgets(contenu, 255, file);
        if (strstr(contenu, content)!=NULL)     test = 1;
    }
    fclose(file);
    file = fopen ("/etc/hosts", "a");
    if (test == 0)
        fprintf(file, "\n127.0.0.1     %s\n", serverName);

    fclose(file);
    free(content);      free(contenu);
}

char* create_conf (char* conf){
    FILE* file = NULL;
    char* instruction = malloc (500);
    char* directive = malloc (255);
    char* content = malloc(500);

    char* server = malloc(150);
    char* admin = malloc(150);
    char* root = malloc(150);
    char* site = malloc(100);
    char* command = malloc(255);
    char* error = malloc(20);
    char* directory = malloc (255);

    char* allow = malloc(100);
    char* opt = malloc(255);
    char* add = malloc(100);
    char* req = malloc(255);

    strcpy(allow,"");   strcpy(opt,"");   strcpy(add,"");     strcpy(req,"");

    char* contenu = malloc(500);
    char* name = malloc(20);

    sscanf(conf, "server=%[^&]&admin=%[^&]&error=%[^&]&document=%[^&]&%*[^=]=%[^\n]\n", server, admin, error, root, directory);
    sscanf(server, "%*[^.].%[^.].%*[^\n]", site);
    strcat(site,".conf");

    sprintf(command, "sudo mkdir %s", root);
    //popen(command,"w");
    system(command);
    sprintf(command, "chmod o+rwx %s", root);
    popen(command,"w");

    if (strstr(directory,"Options")!=NULL){
        strcpy(opt,"Options");      strcat(opt," ");
        if(strstr(directory,"All")!=NULL && strstr(directory,"granted")==NULL) {
            strcat(opt,"All");       strcat(opt," ");
        }
        if(strstr(directory,"Indexes")!=NULL){
            strcat(opt,"+Indexes");       strcat(opt," ");
        }
        if(strstr(directory,"FollowSymLinks")!=NULL){
            strcat(opt,"+FollowSymLinks");       strcat(opt," ");
        }
        if(strstr(directory,"ExecCGI")!=NULL)    {
            strcat(opt,"+ExecCGI");       strcat(opt," ");
        }
        
    }   

    if (strstr(directory, "AllowOverride")!=NULL){
        strcpy(allow, "AllowOverride");  strcat(allow," ");
        if(strstr(directory, "allow=All")!=NULL){
            strcat(allow,"All");
        }
        if(strstr(directory, "allow=None")!=NULL){
            strcat(allow,"None");
        }
    } 

    if(strstr(directory, "AddHandler")!=NULL){
        strcat(add,"AddHandler cgi-script .cgi");
    }

    if(strstr(directory, "Require")!=NULL){
        strcpy(req,"Require all granted\n");
    }

    sprintf(contenu, "%s\n\t%s\n\t%s\n\t%s", opt, allow, add, req);

    directive = balise_html ("Directory", root, contenu, "Directory");

    sprintf(content, "ServerName %s\n\tServerAdmin %s\n\tDocumentRoot %s\n\t%s\n\tErrorLog ${APACHE_LOG_DIR}/%s\n\tCustomLog ${APACHE_LOG_DIR}/access.log combined\n", server, admin, root, directive,error);

    instruction = balise_html ("VirtualHost", "*:80", content, "VirtualHost");

    file = fopen (site,"w");

   fprintf(file, "%s", instruction);

    fclose(file);

    sprintf(command, "mv %s /etc/apache2/sites-available/", site);
    
    system(command);

    create_hosts (server);

    strcpy(name, site) ; 

    free(contenu);
    free(directive);       free(instruction);             free(content);  
    free(server);  free(admin);  free(root);   free(site);  free(error);      free(directory);    free(command);     
    free(allow);    free(req);      free(opt);    free(add);

    return name;
}

void traitement_conf(char* reply){
    char* tmp = malloc(50);
    char* create = malloc (20);
    char conf[255];
    FILE* file = NULL;

    sscanf(reply, "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%[^=]=%*[^\n]\n", tmp);
    sscanf(reply, "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%[^\n]\n", conf);

    if(strcmp(tmp,"server")==0){
        create = create_conf(conf);
        file = fopen ("serverName.txt", "w");
        fprintf(file, "%s\n", create);
        fclose(file);
        if(create!=NULL){
            sprintf(tmp, "sudo a2ensite %s", create);
            popen(tmp,"r");
            printf("<head><meta http-equiv=\"refresh\" content=\"0;url=http://www.manou.mg/programme/system.cgi?information=1&site=1\"></head>");
            popen("sudo systemctl reload apache2","r");
        }
    }
}

void print_conf(char* username, char* reply){
    FILE* file = NULL;
    char contenu[255];

    file = fopen("../HTML/site.html","r");
        for(int i=0; i<103; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
        printf("<a href='http://www.manou.mg/programme/system.cgi?user_information=1' class='d-block'>%s</a>",username);
        for(int i=104; i<190 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }

        printf("<ul class='nav nav-treeview'>");
        site_navbar();        
        printf("</ul></li>");

        for(int i=193; i<242 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }

        for(int i=243; feof(file)!=1 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
    
	fclose(file);

    traitement_conf(reply);
}


