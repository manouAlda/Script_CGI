#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../site.h"

void traitement_state(char* acte){
    FILE* file =    NULL;
    char* apache= malloc(20);
    char* nameServer= malloc(20);
    char** liste = allouer(15,30);
    char** enable = allouer(15,30);
    char** status = allouer(15,30);
    char* number = malloc(255);
    char* tmp = malloc(255);
    char* n = malloc(255);
    char* user = malloc(20);
    int i=0, k=0;
    int count =0;
    char** domainName = NULL;

    if(acte==NULL)  printf("Faute d'information\n");

    sscanf(acte, "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%[^=]=%[^.].%*[^\n]\n", apache,nameServer);

    if(strcmp(apache,"activate")==0){
        sprintf(tmp, "sudo a2ensite %s ", nameServer);
        popen (tmp, "w");
        printf("<head><meta http-equiv=\"refresh\" content=\"0;url=http://www.manou.mg/programme/system.cgi?information=1&status=1\"></head>");
        sprintf(tmp, "sudo systemctl reload apache2");
        popen (tmp, "w");
    }
    else if (strcmp(apache,"desactivate")==0){
        sprintf(tmp, "sudo a2dissite %s ", nameServer);
        popen (tmp, "w");
        printf("<head><meta http-equiv=\"refresh\" content=\"0;url=http://www.manou.mg/programme/system.cgi?information=1&status=1\"></head>");
        sprintf(tmp, "sudo systemctl reload apache2");
        popen (tmp, "w");
    } 
    
    site_file();
    count = count_site();
    domainName = allouer (count, 255);
    domainName = site_list(count);

    file = fopen("site.csv","r");
    for( i=0; feof(file)!=1; i++){
        fgets(liste[i], 30, file);      
    }
    fclose(file); 

    file = fopen("activer.csv","r");
    for(k=0; k<i ; k++){
        fgets(enable[k], 30, file);
        strcat(number,enable[k]);        strcat(number," ");
    }
    fclose(file); 

    for(int j=0; j<i-1; j++){
        if(strstr(number,liste[j])!=NULL){
            strcpy(status[j],"activate");
        }
        else{
            strcpy(status[j],"desactivate");
        }
        if(strcmp(status[j],"activate")==0)     strcpy(tmp,"desactivate");
        else if (strcmp(status[j],"desactivate")==0)     strcpy(tmp,"activate");

        if (strstr(liste[j],"manou.conf")==NULL){
            printf("<tr><td>%d.</td>"
                        "<td>%s</td>"
                        "<td>%s</td>"
                        "<td><a href='http://www.manou.mg/programme/system.cgi?information=1&status=1&%s=%s'>%s</a></td>"
                    "</tr>", j, domainName[j], status[j],tmp,liste[j],tmp);
        }
        else if (strstr(liste[j],"manou.conf")!=NULL){
             printf("<tr><td>%d.</td>"
                        "<td>%s</td>"
                        "<td>%s</td>"
                        "<td>-</td>"
                    "</tr>", j, domainName[j], status[j]);
        }
            
    }
    
    printf("</tbody></table></div>");

    free(apache);       free(nameServer);
    free(liste);    free(enable);   free(status);   free(number);      free(tmp);
    free(user);

}

void print_state(char* username, char* reply){
    FILE* file = NULL;
    char contenu[255];

    file = fopen("../HTML/status.html","r");
        for(int i=0; i<105; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
        printf("<a href='http://www.manou.mg/programme/system.cgi?user_information=1' class='d-block'>%s</a>",username);
        for(int i=106; i<192 ; i++){
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

        traitement_state(reply);

        for(int i=243; feof(file)!=1 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
    
	fclose(file);
}
