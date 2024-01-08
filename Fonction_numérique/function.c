#include "function.h"
#include <math.h>
#include <stdlib.h>

void affiche_html (){
	printf("<html>\n");
	printf("<head>\n");
	printf("<title>Fonction num&eacute;rique</title>\n");
	printf("<style>\n");
	printf(".entete{	display: flex;		justify-content: center;	}\n");
	printf(".fonction{	border-radius: 5px;		background-color: pink;		width: 70%%;	margin-left: 15%%;	}\n");
	printf(".intervalle{	border:thick ;	display: flex;	justify-content: space-around;	}\n");
	printf(".tableau{	background-color: rgb(245, 3, 75);	width: 80%%;	height: max-content;	border-radius: 10px;	margin-left: 10%%;	}\n");
	printf("</style>\n");
	printf("</head>\n");

	printf("<body>\n");
	printf("<div class=\"entete\">\n");
	printf("<h1><i><b><font color=\"red\">Fonction Num&eacute;rique</font></b></i></h1>\n");
	printf("</div>\n");
	printf("<hr><br>\n");

	printf("<div class=\"fonction\">\n");
	printf("<br><center><b><font color=\"white\" size=\"5\">log(x)-1</font></b></center><br>\n");
	printf("</div>\n");

	printf("<br><br><center>Entrer l'intervalle : </center><br>");
	printf("<div class=\"intervalle\">\n");
	printf("<form action=\"http://www.proud.com/cgi-bin/solution.cgi\" method=\"get\">\n");
	printf("<input type=\"number\" name=\"a\" placeholder=\"1\">	 <input type=\"number\" name=\"b\" placeholder=\"13\">\n");
	printf("<br><input type=\"submit\" value=\"submit\">\n");
	printf("</form>\n");
	printf("</div>\n");

	printf("<li>\n");
	printf("<ul>\n");
	printf("<h3><font color=\"coral\">->&nbsp;&nbsp;R&eacute;solution</font></h3>\n");
	printf("</ul>\n");
	printf("</li>\n");
}

void titre_tab1(){
		printf("<div class=\"tableau\">\n");
		printf("<table cellpading=\"15px\" width=\"100%%\" cellspacing=\"10px\">\n");
		printf("            <tr>\n");
		printf("                <td>\n");
		printf("<font color=\"yellow\">It&eacute;rations</font> <hr>\n");
		printf("                </td>\n");
		printf("                <td>\n");
		printf("<font color=\"yellow\">Methode de Dichotomie</font> <hr>\n");
		printf("                </td>\n");
		printf("                <td>\n");
		printf("<font color=\"yellow\">Methode de Newton </font><hr>\n");
		printf("                </td>\n");
		printf("                <td>\n");
		printf("<font color=\"yellow\">Methode de Descarte </font><hr>\n");
		printf("                </td>\n");
		printf("            </tr>\n");
}

void titre_tab2(){
printf("<div class=\"tableau\">\n");
		printf("<table cellpading=\"15px\" width=\"100%%\" cellspacing=\"10px\">\n");
		printf("            <tr>\n");
		printf("                <td>\n");
		printf("<font color=\"yellow\">It&eacute;rations</font> <hr>\n");
		printf("                </td>\n");
		printf("                <td>\n");
		printf("<font color=\"yellow\">Methode de Rectangle</font> <hr>\n");
		printf("                </td>\n");
		printf("                <td>\n");
		printf("<font color=\"yellow\">Methode de Trap&egrave;ze </font><hr>\n");
		printf("                </td>\n");
		printf("            </tr>\n");
}

float function(float x){
	return (log(x)-1);
}

float* dichotomie (float a, float b){
	float func = 0;
	float e=13;
	int index = 20;
	float* sol = malloc(sizeof(float)*index);
	int i=0;
	
	while ( fabs(function(b)-function(a)) > eps ){
		e = (a+b)/ 2 ;
		sol[i]=e;
		func = function(b) * function(e) ;
			if( func > 0 ){
				b = e;
			}else if( func <= 0){
				a=e;
			}
		i++;	
	}

	return sol;
}

float derivee(float x){
	return (1/x);
}

float* newton_tangente (float a, float b){
	float* newton = malloc(sizeof(float)*20);
	float sol=13;
	int i=0;
	
/// Methode de Newton ( tangente ) 
	sol = a - (function(a)/derivee(a) ) ;

	while ( fabs(function(b) ) > eps){
		sol = sol - (function(sol)/derivee(sol) ) ;
		b= sol;
		newton[i] = sol ;
		i++;
	}

	return newton;
}

float equation__droite ( float a, float b ) {
	return ( (b-a) / (function(b)-function(a) ) );
}

float* descarte_secante (float a, float b){
	float* decar = malloc(sizeof(float)*20);
	float sol=13;
	int i=0;

	sol =  b - ( function(b) * equation__droite(a,b) ) ;

		while ( fabs(function(b)) > eps){
			sol =  b - ( function(b) * equation__droite(a,b) ) ;
			b= sol;
			decar[i] = sol;
			i++;
		}

	return decar;
}

float* integral_rectangle (float a, float b){
	float* rect = malloc(sizeof(float)*50);
	float inter=0, x=0;
	float aire = 0;
	inter = (b-a)/20;
/// Methode des retangles 
	for (int i = 0; i <=20 ; i++){
		x= (a + (i* inter) ) ;
		aire += (function(x) ) * inter; 
		rect[i]=aire;
	}
	return rect;
}

float* integral_trapeze(float a, float b){
	float* trap = malloc(sizeof(float)*50);
	float inter=0, aire=0;
	float x=0, y=0;
	inter = (b-a)/20;
/// Methode des trapèzes
	for (int i=0 ; i<= 20 ; i++){
		x= (a + (i* inter) ) ;
		y= (a + ((i+1)* inter) ) ;
		aire += ( ( ( log(x)-1) + (log( y) -1 ) ) * inter ) / 2 ;
		trap[i]=aire;
	}
	return trap;
}
