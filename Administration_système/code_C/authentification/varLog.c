#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "connect.h"

int main() {
    // Print des balises HTML
    printf("Cache-Control: no-cache, no-store, must-revalidiate\n");
    printf("Pragma: no cache\n");
    printf("Expires: 0\n");
	printf("Content-type:text/html\n\n");

    char* reply = getenv("QUERY_STRING");
    char* ip = getenv("REMOTE_ADDR");
    char* variable = malloc(100);
    char* valeur = malloc(100);
    char* username = malloc(30);
    char* address = malloc(30);
    char user[20] , contenu[100], tmp[20];

    FILE* var=NULL;		FILE* file ;
    int nbr = count_line(var);
    int count =0;
    int debut=1, fin=10, commence=1, final=10;
    int search=0, none=0;
    int verify=1, connect= -1, inscrit=0;
    count = (nbr+9) / 10;
    
    strcpy(username,"");

    file = fopen("connecte.csv", "r");
    if(file==NULL)  printf("Erreur d'ouverture du fichier de connexion");
    for(int i=0; feof(file)!=1; i++){
         fgets(contenu, 100, file);
        sscanf(contenu, "%[^,],%*[^,],%[^\n]\n",tmp,address);
        if(strcmp(address,ip)==0)
            strcpy(username,tmp);
    }

    if(reply!=NULL){       
        sscanf(reply, "%[^=]=%[^\n]", variable,valeur);  

        if (strcmp(variable,"login")==0) {
            verify=0;	none=1;
            formulaire("");
        }else if(strcmp(variable,"inscrire")==0){
            verify=0;	none=1;
            inscrire("");
        }else if(strcmp(variable,"information")==0){
            verify=0;	none=1;
            information("");
        }else if(strcmp(variable,"suivant")==0){
            debut=atoi(valeur)+1;       fin = debut +9;
            if(atoi(valeur)==0)    commence=1;
            else    commence=atoi(valeur)/10;       
            final=commence+9;
        }else if(strcmp(variable,"avant")==0){
            fin = atoi(valeur)-10;      debut = fin -9;
            commence=(atoi(valeur)-10)/10;          final=commence+9;
        }else if(strcmp(variable, "hundred")==0){
            debut = nbr-100;            fin = debut + 9 ;
        }else if(strcmp(variable, "user")==0 || strstr(variable,"user")!=NULL){
            search=1;
            if(strcmp(variable, "user")==0 ){
				sscanf(reply, "%*[^=]=%[^&]&%[^=]=%[^\n]\n", valeur, user,variable);		 }
			else if(strstr(variable,"user")!=NULL){
				sscanf(reply, "%*[^+]+%[^+]+%[^=]=%[^\n]\n", valeur, user, variable);	     }
            
            if( strcmp(user, "suivant_user")==0){
                debut=atoi(variable)+1;       fin = debut +9;     
            }else if (strcmp(user, "avant_user")==0){
                fin = atoi(variable)-10;      debut = fin -9;
            }else if (strcmp(user, "page")==0){
                debut = ( (atoi(variable)-1) * 10 ) +1;            fin = debut +9;
				commence=atoi(variable);      final=atoi(variable)+9;
            }else if (strcmp(user, "plage_avant")==0){
                final = atoi(variable);       
				if(final<10)    commence = final - (final - 1);
				else            commence= final-9;
            }else if(strcmp(user, "plage_apres")==0){
				commence = atoi(variable)+1;      final = commence+9;
			}
        }else if(strcmp(variable, "page")==0){
            if(atoi(valeur)>count){
                search=1;   strcpy(valeur,"Nothing");
            }
            debut = ( (atoi(valeur)-1) * 10 ) +1;            fin = debut +9;
            commence=atoi(valeur);      final=atoi(valeur)+9;
        }else if(strcmp(variable, "plage_avant")==0){
            final = atoi(valeur);       
            if(final<10)    commence = final - (final - 1);
            else            commence= final-9;
        }else if(strcmp(variable, "plage_apres")==0){
            commence = atoi(valeur)+1;      final = commence+9;
        }else if(strcmp(variable,"deconnexion")==0){
            deconnexion(username);      strcpy(username,"");
        }
    }

	if( strcmp(username,"")==0 && none!=1 ){
        oupps();
        verify=0;
    }
    if(verify==1){
        aheader(username);

        traitement_search(var,valeur , search ,debut,fin,commence,final);

        pfoot(nbr,commence, final);
    }
       
    free(variable); free(valeur);   free(username);
    fclose(file);

    return 0;
}
