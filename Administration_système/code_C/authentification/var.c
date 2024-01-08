#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "var.h"
#include "../site.h"

int count_line (){
    FILE* f = NULL;
	f = fopen ("/var/log/auth.log","r");
	int total=0;
	char contenu[300];
	while(fgets(contenu, sizeof(contenu), f) != NULL){
		if(strstr(contenu,"session opened")!=NULL || strstr(contenu,"session closed")!=NULL )
            total++;
	}

	fclose(f);
	return total;
}

char* month_gasy (char* month){
	char* monat= malloc(20);
	char mois[12][5]={ "Jan","Fev","Mar","Avr","Mey","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	char volana[12][20]={ "Janoary","Febroary","Martsa","Aprily","May","Jona","Jolay","Aogositra","Septambra","Oktobra","Novambra","Desambra" };
	
	for(int i=0;i<12;i++){
		if(strcmp(month,mois[i])==0){
			strcpy(monat,volana[i]);
		}
	}
	return monat;
}

char* andro_gasy (int jour,char* month,int annee){
	/// on commence a l'année 1901 qui a commencee le mardi 1 Janvier 1901
	char andro[7][15]={ "Alahady", "Alatsinainy", "Talata", "Alarobia", "Alakamisy", "Zoma", "Sabotsy"};
	char mois[12][5]={ "Jan","Fev","Mar","Avr","Mey","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	char isa[12][3]={"31", "28", "31","30","31","30","31","31","30","31","30","31"};
	char* tag  = malloc(15);
	int day=2;
	int annee_ecoulee = 0;
	int jour_bissextil=0;
	int jour_ecoule =0;
	
	annee_ecoulee = annee -1901 ;
	jour_bissextil = annee_ecoulee / 4;
	if(annee%400==0){	
		strcpy(isa[1],"29");
	}
	for(int i=0;i<12;i++){
		if(strcmp(month,mois[i])==0){
			break;
		}
		jour_ecoule += atoi(isa[i]);
	}
	
	day = jour + jour_ecoule + jour_bissextil + annee_ecoulee + 1 ;
	day = day % 7;
	strcpy(tag, andro[day]);
	
	return tag;
}

void pagination_auth(int page, int search, char* user, int first, int end){
    printf("<div class='card-footer clearfix'><ul class='pagination pagination-sm m-0 float-right'>");
   
    if (page<=10 && page>1){
        printf("<form action=\"http://www.manou.mg/programme/system.cgi\" method=\"get\" style ='display: flex;'>\n");
        if(search==0)
            for(int i=0; i<page; i++)
                printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&numero' value='%d'>%d</button></li>",((i+1)*10)-9,i+1);
        else if (search==1)
            for(int i=0; i<page; i++)
                printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&search=1%s&numero' value='%d'>%d</button></li>",user, ((i+1)*10)-9,i+1);
        printf("    </form>\n");
    }
    else if(page>10){

            printf("<form action=\"http://www.manou.mg/programme/system.cgi\" method=\"get\" style ='display: flex;'>\n");
            if(search==0)
                for(int i=first; i<end ; i++){
                    if(i==first)
                        printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&return' value='%d'>&laquo;</button></li>",first); 

                    printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&numero' value='%d'>%d</button></li>",((i+1)*10)-9,i+1);

                    if(i==end-1 )
                        printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&move' value='%d'>&raquo;</button></li>",end);
                }
            else if (search==1)
                for(int i=first ; i<end ; i++){
                    if(i==first)
                        printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&return=' value='%d'>&laquo;</button></li>",first); 

                    printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&search=1%s&numero' value='%d'>%d</button></li>",user, ((i+1)*10)-9,i+1);

                    if(i==end-1 )
                        printf("<li class='page-item'><button class='page-link' name='information=1&auth=1&move' value='%d'>&raquo;</button></li>",end);
                }
             printf("    </form>\n");
       
    }
    printf("</ul></div>");
}

void traitement_auth(Auth* lines, int k, int start, int final,int first, int end, int search, char* thing, char* username){
    char date[200];
    char action[100];
    char user[100];
    char tmp[255];
    int i=0;

    int page = (k+9)/10;
    FILE* file = NULL;
    char contenu[255];

    if(end>page)    end = page;

    file = fopen("../HTML/varLog.html","r");

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

        for(int i=193; i<256 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
/// Traitement du tableau
    for (int i=start; i<final ; i++){
        sprintf(date, "%s faha %s %s 2023", andro_gasy(atoi(lines[i].date), lines[i].month, 2023), lines[i].date, month_gasy(lines[i].month));

        if(strstr(lines[i].infos,"for user")!=NULL){
            strcpy(tmp, strstr(lines[i].infos,"for user"));
            sscanf(tmp, "%*[^ ] %*[^ ] %[^(](%*[^\n]\n", user);
        }

        if(strstr(lines[i].infos, "opened")!=NULL){
            strcpy(action, "Opened");
        }
        else if (strstr(lines[i].infos, "closed")!=NULL){
            strcpy(action, "Closed");
        }

        if(strcmp(action,"Opened")==0)
            printf("<tr>"
            "<td>%d.</td>"
            "<td>%s</td>"
            "<td><span class='tag tag-success'>%s</span></td>"
            "<td><a href='http://www.manou.mg/programme/system.cgi?information=1&auth=1&search=%s'>%s</a></td>"
            "</tr>",i,date,action,user, user);
        else if(strcmp(action,"Closed")==0)
            printf("<tr>"
            "<td>%d.</td>"
            "<td>%s</td>"
            "<td><span class='tag tag-warning'>%s</span></td>"
            "<td><a href='http://www.manou.mg/programme/system.cgi?information=1&auth=1&search=%s'>%s</a></td>"
            "</tr>",i,date,action,user, user);

    }
/// Fin traitement tableau
    printf("</tbody></table>");

    pagination_auth(page, search, thing, first, end);

        for(int i=257; feof(file)!=1 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }

    fclose(file);
}

void print_auth (char* user, char* url){
    FILE* file = NULL;
    int count = count_line();
    Auth* lines =  (Auth*)malloc(count * sizeof(Auth));
    char contenu[500];
    int i=0;
    int first = 0;
    int end = 10;

    char* infos ;
    char* act = malloc(100);
    char* thing = malloc(100);
    char tmp[100];

    int search = 0;
    int start = 0;
    int final = 10;

    sscanf(url , "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%[^=]=%[^\n]\n", act, thing);

    //printf("<p>Act : %s</p>",act);
    if(strcmp(act,"search")==0){
        if(strstr(url,"search=1")!=NULL){
            sscanf(url, "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%*[^1]1%[^&]&%*[^=]=%[^\n]\n",thing,tmp);
            start = atoi(tmp);
        }
        search = 1;
    }    
    else if(strcmp(act,"numero")==0){
        sscanf(url, "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%*[^=]=%[^\n]\n",tmp);
        start = atoi(tmp);
        final = start+10;
        if(final>i) final=i;

        first = (start/10);
        end = first + 9;
    }
    else if(strcmp(act,"return")==0){
        sscanf(url, "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%*[^=]=%[^\n]\n",tmp);
        
        end = atoi(tmp);        if(end==1)      end = 9;
        first = end -9 ;        if(first<0)     first = 1;
    }
    else if(strcmp(act,"move")==0){
        sscanf(url, "%*[^=]=%*[^&]&%*[^=]=%*[^&]&%*[^=]=%[^\n]\n",tmp);
        
        first = atoi(tmp);        end = first +9 ;
    }
    
    //printf("<p>URL : %s</p><p>Search %d: %s</p><p>Act : %s</p><p>Page : %d</p>",url, search, thing, act, start);


    file = fopen("/var/log/auth.log","r");

    if(file==NULL){
        printf("Erreur lors de l'ouverture du fichier /var/log/auth.log");
    }

    while (fgets(contenu, sizeof(contenu), file)) {
        
        if(strstr(contenu,"session opened")!=NULL || strstr(contenu,"session closed")!=NULL ){
            if(search==1){
                infos = strstr(contenu ,"user ");  

                if( strstr(infos,thing)!=NULL ){
                    sscanf(contenu, "%[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^\n]\n" ,lines[i].month, lines[i].date, lines[i].time, lines[i].host, lines[i].action,lines[i].infos);
                    i++;
                }
            } else if (search==0){
                sscanf(contenu, "%[^ ] %[^ ] %[^ ] %[^ ] %[^ ] %[^\n]\n" ,lines[i].month, lines[i].date, lines[i].time, lines[i].host, lines[i].action,lines[i].infos);
                i++;
            }
        }
    }
    
    // printf("<p>->%d</p><p>MONTH : %s</p><p>DAY : %s</p><p>TIME : %s</p><p>HOST : %s </p><p> ACTION : %s </p><p> INFOS :%s </p>",i,lines[i].month, lines[i].date, lines[i].time, lines[i].host, lines[i].action,lines[i].infos);
    //printf("<p>Enregistrement : %d</p>",i);

    final = start+10;
    if(final>i) final=i;

    if(first == (i+9)/10){
        end = first;        first = end -9;
    }

    traitement_auth(lines,i, start, final, first, end, search, thing, user);

    free(act);      free(thing);   free(lines); 

    fclose(file);
    
}