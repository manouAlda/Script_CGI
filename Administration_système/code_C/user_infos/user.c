#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../site.h"

void ptabeau(int i,char* user, char* rep) {
    printf("<tr><td>%d.</td> <td>%s</td> <td>%s</td></tr>",i,user,rep);
}

int EstPoints(char* tab){
	int v=0;	
	for(int j=0;j<strlen(tab); j++)
			if(tab[j]==':' && tab[j+1]!=':')	v++;               							
	return v;
}

int ptraitement (){
    FILE* file = NULL;
	file= fopen ("/etc/passwd","r");
	char* contenu= malloc(255);	
	char* user = malloc(20);
    char* rep = malloc(20);
    char* mot = malloc(20);    
	int uid=13, i, j=0;
	int k=0, count=0;
	
	if (file == NULL){
		printf("Erreur d'ouverture du fichier /etc/passwd\n");
	}
	while(feof(file)!=1){
		fgets(contenu,255,file);
		k=EstPoints(contenu);
			
		mot = strtok(contenu,":");
		/// 1er champs
		if (mot == NULL)	continue;
		strcpy(user , mot);
		/// 2em champs
		mot = strtok(NULL,":");
		if (mot == NULL)	continue;
		/// 3em champs
		mot = strtok(NULL,":");
		if (mot == NULL)	continue;
		uid = atoi(mot);
		/// 4em,5em et 6em champs en boucle 
		int fin ;
		if(k==5)	fin=2;
		else if(k==6)	fin=3;
		for (j=0; j<fin;j++){
			mot = strtok(NULL,":");
			if (mot == NULL)	continue;
		}	
		strcpy(rep ,mot);

        if(uid>=1000){
		    ptabeau(count+1,user,rep);
            count++;
        }	
		i++;
	}
	fclose(file);
	free(contenu);  free(user);     free(rep);      free(mot);
    return count;
}

void pagination_passwd (int page){
    if (page<=10 && page!=1){
        for(int i=0; i<page; i++)
            printf("<li class='page-item'><a class='page-link' href='#'>%d</a></li>",i+1);
    }
    else if(page>10){
        printf("<li class='page-item'><a class='page-link' href='#'>&laquo;</a></li>");  
            for(int i=0; i<page; i++)      
                printf("<li class='page-item'><a class='page-link' href='#'>%d</a></li>",i+1);
        printf("<li class='page-item'><a class='page-link' href='#'>&raquo;</a></li>");       
    }
}

void print_passwd (char* username){
    int total = 0;
    int page = 0;
	FILE* file = NULL;
    char contenu[255];

    file = fopen("../HTML/user.html","r");
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

        total = ptraitement();
		printf("</tbody></table></div>");
		printf("<div class='card-footer clearfix'><ul class='pagination pagination-sm m-0 float-right'>");

		page = (total+9) / 10;

		pagination_passwd(page);
		printf("</ul></div>");
    
    	printf("</div></div></div></div></section>");

        for(int i=243; feof(file)!=1 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
    
	fclose(file);
}
