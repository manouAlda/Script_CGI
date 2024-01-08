#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "access.h"
#include "../site.h"

int count_line_access (char* name){
    FILE* f = NULL;
    int total=0;
	char contenu[500];
    char url[255];
	f = popen("sudo cat /var/log/apache2/access.log","r");
	
	while(fgets(contenu, 500, f)!=NULL){
        sscanf(contenu, "%*[^-]-%*[^[][%*[^:]:%*[^ ] %*[^T]T%*[^\"]\"%*[^\"]\"%[^\"]\"%*[^\n]\n", url);
        if(strstr(url,name)!=NULL) total++;
    }
	pclose(f);
	return total;
}

void pagination_access(int page, char* user, int first, int end){
    printf("<div class='card-footer clearfix'><ul class='pagination pagination-sm m-0 float-right'>");
   
    if (page<=10 ){
        printf("<form action=\"http://www.manou.mg/programme/system.cgi\" method=\"get\" style ='display: flex;'>\n");
        
            for(int i=0; i<page; i++)
                printf("<li class='page-item'><button class='page-link' name='information=1&access=1&search=1%s&numero' value='%d'>%d</button></li>",user, ((i+1)*10)-9,i+1);
       
        printf("    </form>\n");
    }
    else if(page>10){

            printf("<form action=\"http://www.manou.mg/programme/system.cgi\" method=\"get\" style ='display: flex;'>\n");
            
                for(int i=first ; i<end ; i++){
                    if(i==first)
                        printf("<li class='page-item'><button class='page-link' name='information=1&access=1&search=1%s&return' value='%d'>&laquo;</button></li>",user, first); 

                    printf("<li class='page-item'><button class='page-link' name='information=1&access=1&search=1%s&numero' value='%d'>%d</button></li>",user, ((i+1)*10)-9,i+1);

                    if(i==end-1 )
                        printf("<li class='page-item'><button class='page-link' name='information=1&access=1&search=1%s&move' value='%d'>&raquo;</button></li>",user, end);
                }
               
            printf("    </form>\n");
       
    }
    printf("</ul></div>");
}

void traitement_access(char* reply){
    char* contenu = malloc(500);
    int count = 0;
    Acces* lines ;
    char tmp[30];
    char tmp1[10];
    char name[100];
    char url[255];
    FILE* file = NULL;

    int k=0;
    int nbr = 0;
    int first =0,  end=10, page=0, start=0, final =10 ;

    sscanf(reply, "%*[^=]=%*[^&]&%*[^=]=%[^\n]\n", name);
    printf("<p>***************************************** reply -> %s</p>", reply);
    printf("<p>***************************************** name -> %s</p>", name);

    if(strstr(name,"&")!=NULL){
        sscanf(reply, "%*[^&]&%*[^&]&%*[^1]1%[^&]&%[^=]=%[^\n]\n",name, tmp, tmp1);
    
        if(strcmp(tmp, "numero")==0){
            start = atoi(tmp1)-1;
            final = start+10;

            first = (start/10);
            end = first + 9;
        }
        else if(strcmp(tmp,"move")==0){
            first = atoi(tmp1);        end = first +9 ;
        }
        else if(strcmp(tmp,"return")==0){
            end = atoi(tmp1);        if(end<=0 || end==1)      end = 9;
            first = end -9 ;        if(first<=0)     first = 0;
            //printf("<p>***************************************** ITO name -> %s  AND %s     ---     %d || first = %d & end = %d</p>", name, tmp1, atoi(tmp1) , first, end);
        }
    }

    count = count_line_access(name);
    lines = (Acces*)malloc((count) * sizeof(Acces));
    
    //printf("AO RAHA -> %s = %s  ; first&end = %d, %d\n",tmp,tmp1,first, end);

    file = popen("sudo cat /var/log/apache2/access.log","r");

    if (file ==  NULL)  printf("Faute");

    while(fgets(contenu, 500, file)!=NULL){
        sscanf(contenu, "%*[^ ] %*[^[][%*[^:]:%*[^ ] %*[^T]T%*[^\"]\"%*[^\"]\"%*[^/]/%[^?]?%*[^\n]\n", url);

        if(strstr(url,name)!=NULL){
            sscanf(contenu, "%[^ ] %*[^[][%[^:]:%[^ ] %*[^T]T%[^\"]\"%*[^\"]\"%[^\"]\"%*[^\n]\n", lines[nbr].ip, lines[nbr].date, lines[nbr].time, lines[nbr].get, lines[nbr].url);
            nbr++;
        }
    }
    
    page = (nbr+9)/10;
    if (final > nbr) final =nbr-1;
    //printf("<p>***************************************** nbr -> %d and final = %d</p>", nbr, final);

    for (int i=start; i<final; i++){
        printf("<tr><td>%d.</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td></tr>",i ,lines[i].ip, lines[i].date, lines[i].get, lines[i].url);
    }
    printf("</tbody></table></div>");

    pclose(file);

    //if(end==page)   end = page;

    pagination_access(page, name,first, end);

    free(lines);
    free(contenu);
    //free(ip);   free(date);     free(time);     free(get);      free(url);
    //free(tmp);  free(tmp1);

}

void print_access(char* username, char* reply){
    FILE* file = NULL;
    char contenu[255];

    file = fopen("../HTML/access.html","r");
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

        for(int i=193; i<243 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }

        traitement_access(reply);

        for(int i=244; feof(file)!=1 ; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
    
	fclose(file);
}