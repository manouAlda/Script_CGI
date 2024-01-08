#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

int main(){
    printf("Cache-Control: no-cache, no-store, must-revalidiate\n");
    printf("Pragma: no cache\n");
    printf("Expires: 0\n");
    printf("Content-type: text/html\n\n");
    char* reply = getenv ("QUERY_STRING");

    FILE* html = NULL;
    char* balise = malloc(255);
    char* directory = malloc(100);
    char* username = malloc(30);
    char* address = malloc(30);

    if(strcmp(reply,"")==0 || strcmp(reply,"information=1&exit=1")==0 ){
        print_html();
        text_login();
        main_page();
    }
    else{
        traitement(withoutHex(reply));
    }
   
    free(balise);
    free(username);
    free(address);

    return 0;
}