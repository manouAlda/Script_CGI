#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "configuration.h"

int main(){
    printf("Content-Type: text/html\n\n");
    char* conf = getenv("QUERY_STRING");
    char* content = malloc(255);
    char* tmp = malloc(50);
    char* nom = malloc(20);
    char* create = malloc (20);
    FILE* file = NULL;

    if (conf == NULL){
        printf("<p>Faute d'information</p>\n");
        return 0;
    }

    sscanf (conf, "%[^=]=%*[^.].%[^.].%*[^\n]\n", tmp, nom);
    printf("<p>NOM: %s</p>\n",nom);
    
    if (strcmp(tmp,"server")==0){
        create = create_conf(withoutHex(conf));
        file = fopen ("serverName.txt", "w");
        fprintf(file, "%s\n", create);
        fclose(file);
    }
    else if (strcmp(tmp,"activer")==0){ 
        file = fopen("serverName.txt","r");
        fgets(nom, 20, file);
        fclose(file);
        sprintf(tmp, "sudo a2ensite %s ", nom);
        popen (tmp, "w");
        sprintf(tmp, "sudo systemctl reload apache2");
        popen (tmp, "w");
    }
    else if (strcmp(tmp,"desactiver")==0){
        file = fopen("serverName.txt","r");
        fgets(nom, 20, file);
        fclose(file);
        sprintf(tmp, "sudo a2dissite %s ", nom);
        popen (tmp, "w");
        sprintf(tmp, "sudo systemctl reload apache2");
        popen (tmp, "w");
    }

    if (create != NULL){
        printf("<html>\n");
        printf("<head>  <title> Successfully finished </title>\n");
        printf("<style>\n");
        classe("h1", "text-transform: uppercase; letter-spacing: 2px; color:crimson; font-family:fantasy; padding: 5vw; ");
        classe("h2", "padding-top:5vw;");
        classe(".body", "marging-top:5vw;   marging-left:15vw;  border-radius:5vw;  background: lightblue;  width:70%%;  height: max-content;   padding-bottom:7vw;");
        classe(".element", "align-items: center; display:flex; justify-content: space-around;");
        classe(".boutton", "border-radius:3vw; background: honeydew; padding:2vw;");
        printf("</style>\n");
        printf("</head>\n");

        printf("<body>\n");
        content = balise_html ("center", "", "Your configuration has been successfully completed", "center");
        print_balise_html("h1","", content,"h1");

        printf("<div class='body'>\n");
        content = balise_html ("center", "", "Site status : ", "center");
        print_balise_html("h2", "", content, "h2");
        printf("    <div class='element'>\n");

        print_balise_html("div", "class='boutton'", "<a href='http://www.manou.mg/programme/site.cgi?activer=1' >Activer</a>" , "div");

        print_balise_html("div", "class='boutton'", "<a href='http://www.manou.mg/programme/site.cgi?desactiver=1' >Desactiver</a>", "div");

        printf("    </div>\n");
        printf("</div>\n");
        printf("<body>\n");

        printf("</html>\n");
        
    }

    free(content);      free(tmp);          free(nom);      free(create);

    return 0;
}
