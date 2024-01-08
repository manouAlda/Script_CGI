#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "../admin.h"

int main(){	
	FILE* file ;
	char* user = malloc(20);
	strcpy(user,"");

	//Print des balises HTML
	printf("Content-Type: text/html\n\n");
	
	user = test_user();

	if(strcmp(user,"")!=0){
		print_content(user);
	}

	free(user);

	return 0;
}
