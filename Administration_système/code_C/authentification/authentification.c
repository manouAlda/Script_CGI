#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "connect.h"

int main() {
    // Print des balises HTML
	printf("Content-type:text/html\n\n");

    char* reply = getenv("CONTENT_LENGTH");
    char* answer = NULL;
    char* variable = malloc(100);
    char* valeur = malloc(100);
	FILE* file ;
    int connect= -1, inscrit=0, finish=1, longueur=0, modify=0;
    
    longueur = atoi(reply);
    answer = malloc(longueur+1);
    
    fgets(answer, longueur+1, stdin);

    if(answer!=NULL){       
        sscanf(answer, "%[^=]=%[^\n]", variable,valeur);     
        
        if(strcmp(variable,"utilisateur")==0){
            inscrit = fichier_inscrit(valeur);
            if(inscrit==0) { 
				finish=0;
				inscrire("Registration failed. Invalid pseudo or email (already used)");
			}
        }else if(strcmp(variable,"username")==0){
            connect= fichier_connecte(valeur);
            if(connect!=2){  
				finish=0;
				formulaire("Login failed. Invalid username, email or password "); 
			}
        }else if(strcmp(variable,"name_modify")==0){
            modify = modification(answer);
            if(modify == 0){
				finish=0;
				information("Modification refused. Invalid username, pseudo or email (already used)");
			}
        }
    }
    
    if (finish == 1) {
        printf("<head><meta http-equiv=\"refresh\" content=\"0;url=http://www.manou.mg/programme/varLog.cgi\"></head>");
    }
       
    free(variable); free(valeur);

    return 0;
}
