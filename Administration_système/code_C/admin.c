#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "user_infos/user.h"
#include "site.h"
#include "authentification/var.h"
#include "creation_site/configuration.h"
#include "creation_site/status.h"
#include "creation_site/access.h"

int hex_to_char(char* tab){
	int val=0, decimal=0;
	int len = strlen(tab)-1;
	
	for (int i=0; tab[i]!='\0'; i++){
		if(tab[i]>= '0' && tab[i]<='9'){
			val = tab[i]-48;
		}else if(tab[i]>='a' && tab[i]<='f'){
			val = tab[i]-97+10;
		}else if(tab[i]>= 'A' && tab[i]<='F'){
			val = tab[i]-65+10;
		}else{
			return -1;
		}
		
		decimal += val* pow(16, len);
		len--;
	}
	
	return decimal;
}

char* withoutHex(char* tab) {
    char* new = malloc(strlen(tab) + 1);
    int i = 0, j = 0;
    char hex[3];
    char car;

    while (tab[i] != '\0') {
        if (tab[i] == '%' && tab[i + 1] != '\0' && tab[i + 2] != '\0') {
            hex[0] = tab[i + 1];
            hex[1] = tab[i + 2];
            hex[2] = '\0';

            car = hex_to_char(hex);

            if (car != -1) {
                new[j] = car;
                i += 3;
            } else {
                new[j] = tab[i];
                i++;
            }
        } else if (tab[i] == '+') {
            new[j] = ' ';
            i++;
        } else {
            new[j] = tab[i];
            i++;
        }
        j++;
    }
    new[j] = '\0';

    return new;
}

void print_html (){
    FILE* file = NULL;
    char contenu[255];
    file = fopen("../HTML/andrana.html","r");
        for(int i=0; feof(file)!=1; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
    fclose(file);
}

void print_home(){
    FILE* file = NULL;
    char contenu[255];
    file = fopen("../HTML/home.html","r");
        for(int i=0; feof(file)!=1; i++){
            fgets(contenu, 255, file);
            printf("%s",contenu);
        }
    fclose(file);
}

void main_page(){
    printf("<div id='text'> \n <center> \n User information, authentification, and website hosting <br><br> \n ");
    printf("<a href='http://www.manou.mg/programme/system.cgi?information=1&home=1'><button id='more'>More information</button></a></center>\n");
    printf("       </div></body></html>");
}

void text_login(){
    printf("<div><a href='http://www.manou.mg/programme/system.cgi?information=1&login=1'><button class='button'>Login</button></a></div></div></nav></header>");
}

void icon_login(char* name){
    printf("<div class='signIn'><a href='http://www.manou.mg/programme/system.cgi?information=1&infos_login=1' style='color: white;'><img src='../img/login.png' alt='Icon' class='logo' id='logIn'> %s&nbsp;&nbsp;&nbsp;&nbsp;</a><a href='http://www.manou.mg/programme/system.cgi?information=1&exit=1'><button class='button'>Deconnexion</button></a></div></div></nav></header>",name);
}

void noConnect(){
    printf("<div id='noConnect'><center class='text'><img src='../img/oupps.png' alt='Oupps!!!' id='oupps'><br><br><h3>You have to connect to view more information</h3>\n");
    printf("<br><br><a href='http://www.manou.mg/programme/system.cgi?login=1'><button id='more'> Sign in</button></a>\n");
    printf("</center></div></body></html>");
}

void sign(char* infos){
    printf("<div id='signUP'><h2>Create Account</h2><form action='http://www.manou.mg/programme/auth.cgi' method='post'>");
    printf("           <div class='input-box'><input type='text' name='utilisateur' placeholder='Enter your name' required></div>");
    printf("            <div class='input-box'><input type='text' name='pseudo' placeholder='Enter your id' required></div>");
    printf("            <div class='input-box'><input type='email' name='email' placeholder='Enter your email' required></div>");
    printf("            <div class='input-box'><input type='password' name='mdp' placeholder='Create password' required></div>");
    printf("            <div class='input-box'><input type='password' name='passer' placeholder='Confirm password' required></div>");
    printf("           <div class='submit'><input type='submit' value='Submit'></div><br>");
    printf("           <div class='text'><h3>Already have an account?<a href='http://www.manou.mg/programme/system.cgi?login=1'>Login now</a></h3></div>");
    printf("            <p style='color='red';'><center><font color='red'>%s</font></center></p>",infos);
    printf("        </form></div></body></html>");
}

void login(char* infos){
    printf("<br><br><div id='signUP'><h2>Login</h2><form action='http://www.manou.mg/programme/auth.cgi' method='post'>");
    printf("           <div class='input-box'><input type='text' name='username' placeholder='Enter your name or email' required></div>");
    printf("            <div class='input-box'><input type='password' name='password' placeholder='Password' required></div>");
    printf("           <div class='submit'><input type='submit' value='Submit'></div><br>");
    printf("           <div class='text'><h3>Not a member?<a href='http://www.manou.mg/programme/system.cgi?sign=1'>Sign up now</a></h3></div>");
    printf("            <br><p><center><font color='red'>%s</font></center></p>",infos);
    printf("        </form></div></body></html>");
}

void home(){
    printf("<div id='home'><a name='discover'><h3 class='title'>Discover</h3></a><br><br><br>");
    printf("        <div><a href='http://www.manou.mg/programme/system.cgi?information=1&passwd=1'><button class='element'>User Infomation</button></a></div>");
    printf("        <div><a href='http://www.manou.mg/programme/system.cgi?information=1&auth=1'><button class='element'>Auth.log</button></a></div>");
    printf("        <div><a href='http://www.manou.mg/programme/system.cgi?information=1&site=1'><button class='element'>Website hosting</button></a></div>");
    printf("        <div><a href='http://www.manou.mg/programme/system.cgi?information=1&status=1'><button class='element'>Site Status</button></a></div>");
    printf("        <div><a href='http://www.manou.mg/programme/system.cgi?information=1&access=1'><button class='element'>Access.log</button></a></div>");
    printf("    </div></body>     </html>");
}

char* test_user (){
    char contenu[100], tmp[20], address[30];
    char* username = malloc(30);
    char* ip = getenv("REMOTE_ADDR");
    FILE* file = NULL;

    file = fopen("connecte.csv","r");
    if(file==NULL){
        printf("Erreur d'ouverture du fichier de connexion");
        exit(1);
    } 

    strcpy(username,"");

    for(int i=0; feof(file)!=1; i++){
        fgets(contenu, 100, file);
        sscanf(contenu, "%[^,],%*[^,],%[^\n]\n",tmp,address);
        if(strcmp(address,ip)==0)
            strcpy(username,tmp);
    }

    fclose(file);
    
    return username;
}

int fichier_inscrit (char* infos){
  char* ip = getenv("REMOTE_ADDR");
  FILE* file = fopen("inscrit.csv","a+");
  FILE* f = fopen("connecte.csv","w");
  char nom[255], email[100], mdp[50], clone[50],pseudo[20],content[255];
  char user[100], id[50], mail[100];
  int confirmation=1;

  if(file==NULL)    printf("Erreur d'ouverture du fichier d'inscription\n");

  sscanf(infos,"%[^&]&%*[^=]=%[^&]&%*[^=]=%[^&]&%*[^=]=%[^&]&%*[^=]=%[^\n]\n", nom,pseudo, email, mdp, clone);

  for(int i=0; feof(file)!=1; i++){
    fgets(content, 255, file);
    sscanf(content, "%[^,],%[^,],%[^,],%*[^\n]\n",user, id, mail);
    if(strcmp(user,nom)==0 || strcmp(id,pseudo)==0 || strcmp(mail,email)==0 )
      confirmation=0;
  }

  if(strcmp(mdp,clone)!=0)  confirmation=0;
  else if (confirmation == 1) {
    fprintf(file, "%s,%s,%s,%s\n", nom, pseudo, email, mdp);
    fprintf(f, "%s,%s,%s\n", pseudo, mdp,ip);
  } 
    
  fclose(file);     fclose(f);

  return confirmation;
}

int fichier_connecte ( char* infos){
  FILE* file = fopen("connecte.csv","w");
  FILE* fichier = fopen("inscrit.csv","r+");
  char nom[255], mdp[50], name[100], email[100], passwd[50],pseudo[20];
  int connecte=0, verifier=0;
  char contenu[255];
  char* ip = getenv("REMOTE_ADDR");

  if(file==NULL)    printf("Erreur d'ouverture du fichier de connexion\n");
  if(fichier==NULL)    printf("Erreur d'ouverture du fichier d'inscription\n");

  sscanf(infos, "%[^&]&%*[^=]=%[^\n]\n", nom, mdp);

  for(int i=0; feof(fichier)!=1; i++){
    fgets(contenu, 255, fichier);
    sscanf(contenu, "%[^,],%[^,],%[^,],%[^\n]\n", name,pseudo, email, passwd);
    if( (strcmp(name,nom)==0 || strcmp(email,nom)==0 || strcmp(pseudo,nom)==0) &&  strcmp(passwd,mdp)==0){
      connecte=1;
        if(strcmp(email,nom)==0 || strcmp(name,nom)==0)			 
			strcpy(nom,pseudo);
      verifier=1;
    }
  }

  if(connecte==1 && verifier==1){
    fprintf(file, "%s,%s,%s\n", nom, mdp,ip);
    connecte=2;
  }
  
  fclose(file);   fclose(fichier);
  return connecte;
}

void deconnexion(char* user){
  char tmp[255];
  char doc[50][255];
  char nom[20];
  int i=0;
  FILE* file = fopen("connecte.csv","r");
  if(file==NULL)  printf("Erreur d'ouverture du fichier de connexion\n");

  for(i=0; feof(file)!=1; i++){
    fgets(tmp, 255, file);
    sscanf(tmp, "%[^,],%*[^\n]\n" , nom);

    if(strcmp(nom,user)!=0){
      strcpy(doc[i],tmp);
    }
  }
  fclose(file);

  file = fopen("connecte.csv","w");

  for(int j=0; j<i; j++){
    fprintf(file, "%s", doc[j]);
  }

  fclose(file);
}

void print_content (char* username, char* reply, int mark){
    if(mark == 1)       print_passwd(username); 
    else if (mark == 2)     print_auth(username,reply); 
    else if (mark == 3)     print_conf(username, reply); 
    else if (mark == 4)     print_state(username, reply); 
    else if (mark == 5)     print_access(username, reply);  
}

void traitement(char* reply){
    FILE* html = NULL;
    char* balise = malloc(255);
    char* directory = malloc(100);
    char* username = malloc(30);
    char* address = malloc(30);

    sscanf(reply, "%[^=]=%*[^\n]\n", directory);
        if(strcmp(directory,"information")==0){
            username = test_user();
        }
        else if(strcmp(directory,"sign")==0){
            print_html();
            text_login();
            sign("");
        }
        else if (strcmp(directory,"login")==0){
            print_html();
            text_login();
            login("");
        }

        if(strcmp(username,"")==0 && strcmp(directory,"sign")!=0 && strcmp(directory,"login")!=0){
            print_html();
            text_login();
            noConnect();
        }
        if(strcmp(username,"")!=0){
            sscanf(reply, "%*[^=]=%*[^&]&%[^=]=%*[\n]\n", directory);
            if(strcmp(directory,"home")==0){
                print_home();
            }
            else if (strcmp(directory,"exit")==0){
                deconnexion(username);
            }
            else if(strcmp(directory,"menu")==0){
                printf("<head><meta http-equiv=\"refresh\" content=\"0;url=http://www.manou.mg/programme/system.cgi?information=1&home=1#discover\"></head>");
            }
            else if (strcmp(directory,"passwd")==0){
                print_content(username, reply, 1);
            }
            else if (strcmp(directory,"auth")==0){
                print_content(username, reply, 2);
            }
            else if (strcmp(directory,"site")==0){
                print_content(username, reply, 3);
            }
            else if (strcmp(directory,"status")==0){
                print_content(username, reply, 4);
            }
            else if (strcmp(directory,"access")==0){
                print_content(username, reply, 5);
            }
        }

        printf("    </body>\n</html>");

    free(balise);
    free(username);
    free(address);
}
