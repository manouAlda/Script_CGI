#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** allouer(int line,int cols){
	char **tab=NULL;
	tab=(char**)malloc(sizeof(char*)*line);
	for(int i=0;i<line;i++){
		*(tab+i)=(void*)calloc(cols,sizeof(char)*cols);
	}
	return tab;
}

void site_file(){
    FILE* file =    NULL;
    file = popen("ls /etc/apache2/sites-available > site.csv ", "r");
    pclose(file);
    file = popen("ls /etc/apache2/sites-enabled > activer.csv", "r");
    pclose(file);
}

int count_site(){
    int count=0;
    FILE* file = NULL;
    char tmp[100];
    file = fopen("site.csv", "r");
    while(fgets(tmp,100,file)!=NULL){
        count++;
    }
    fclose(file);
    return count;
}

char* domainName (char* conf){
    char* serverName = malloc(100);
    char name[255];
    char*  tmp = malloc(255);
    FILE* file =NULL;

    if(strstr(conf,"000-default.conf")!=NULL){
        strcpy(serverName,"localhost");
    }
    else if (strstr(conf,"default-ssl.conf")!=NULL){
        strcpy(serverName,"default-ssl");   
    }
    else {
        sprintf(name, "cat /etc/apache2/sites-available/%s", conf);
        file = popen(name, "r");
        for(int i=8; feof(file)!=1; i++){
            fgets(tmp,255, file);
            if(strstr(tmp,"ServerName")!=NULL){
                sscanf(tmp, "%*[^ ] %[^\n]\n", serverName);
                if(strstr(serverName,"ServerName")!=NULL){
                    sscanf(serverName, "%*[^ ] %[^\n]\n", tmp);
                    strcpy(serverName,tmp);
                }
            }
        }
        pclose(file);
    }

    free(tmp);
    return serverName;
}

char** site_list (int list){
    FILE* file =    NULL;
    char** list_conf = allouer(list,255);
    char* tmp = malloc(255);
    char* andrana = malloc(255);

    file = fopen ("site.csv", "r");
    for(int i=0; feof(file)!=1; i++){
        fgets(tmp, 255, file);
        list_conf[i] =  domainName(tmp);
    }

    free(tmp);
    fclose(file);
    return list_conf;
}

void site_navbar (){
    int count = 0;
    char** domainName = NULL;

    site_file();
    count = count_site();
    domainName = allouer (count, 255);
    domainName = site_list(count);

    for(int i=0; i<count ; i++){
        printf("<li class='nav-item'>"
                 "<a href='http://www.manou.mg/programme/system.cgi?information=1&access=%s' class='nav-link'>"
                    "<i class='far fa-circle nav-icon'></i>"
                    "<p>%s</p>"
                  "</a>"
                "</li>",domainName[i],domainName[i]);
    }

}

