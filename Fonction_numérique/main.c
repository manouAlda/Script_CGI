#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "function.h"

int main(){

	printf("Content-Type: text/html\n\n");
	float a = 1, b= 0;
	char* response = getenv("QUERY_STRING");
	char *interA = malloc(5);
	char *interB = malloc(5);
	float* dicho = malloc(sizeof(float)*20);
	float* newton = malloc(sizeof(float)*20);
	float* descarte = malloc(sizeof(float)*20);
	float* rect = malloc(sizeof(float)*50);
	float* trap = malloc(sizeof(float)*50);
	int i=0, count=0;

	if(response != NULL){
		sscanf(response, "%*[^=]=%[^&]&%*[^=]=%[^\n]\n", interA,interB);
		a = atof(interA);		b = atof(interB);
	}

	affiche_html();

	dicho = dichotomie(a,b);
	newton = newton_tangente(a,b);
	descarte = descarte_secante(a,b);

	if( strcmp(interA,"")!=0 && strcmp(interB,"")!=0){
		titre_tab1();
		
		while ( dicho[count] != 0 ){
			printf("            <tr>\n");
			printf("                <td>\n");
			printf("%d <hr>\n",i);
			printf("                </td>\n");
			printf("                <td>\n");
			printf("%f<hr>\n",dicho[count]);
			printf("                </td>\n");
			printf("                <td>\n");
			printf("%f <hr>\n",newton[i]);
			printf("                </td>\n");
			printf("                <td>\n");
			printf("%f<hr>\n",descarte[i]);
			printf("                </td>\n");
			printf("            </tr>\n");
			i++;
			count++;
		}
		printf("        </table>\n");
		printf("</div>\n");
	}

	printf("<li>\n");
	printf("<ul>\n");
	printf("<h3><font color=\"coral\">->&nbsp;&nbsp;Int&eacute;grale</font></h3>\n");
	printf("</ul>\n");
	printf("</li>\n");

	rect = integral_rectangle(a,b);
	trap = integral_trapeze(a,b);

	if( strcmp(interA,"")!=0 && strcmp(interB,"")!=0){
		 titre_tab2();
		 
		i=0; count=0;
		while ( rect[count] != 0 ){
			printf("            <tr>\n");
			printf("                <td>\n");
			printf("%d <hr>\n",i);
			printf("                </td>\n");
			printf("                <td>\n");
			printf("%f<hr>\n",rect[count]);
			printf("                </td>\n");
			printf("                <td>\n");
			printf("%f <hr>\n",trap[i]);
			printf("                </td>\n");
			printf("            </tr>\n");
			i++;
			count++;
		}
		printf("        </table>\n");
		printf("</div>\n");
	}

	free(interA);	free(interB);
	free(dicho);	free(newton); free(descarte);
	free(rect); 	free(trap);
		
	return 0;
}
