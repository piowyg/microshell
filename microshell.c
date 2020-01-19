#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include<sys/stat.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdbool.h>

void cyan () {
  printf("\033[0;36m");
}
void magenta () {
  printf("\033[0;35m");
}
void green () {
  printf("\033[0;32m");
}

void red () {
  printf("\033[1;31m");
}

void yellow() {
  printf("\033[1;33m");
}

void reset () {
  printf("\033[0m");
}
int licznik=0;

int copy(char* arg,char* arg2,int klucz)
{
            FILE * opened_file;
			opened_file = fopen(arg,"r");
	 		if(opened_file == NULL)
    		{
      			perror("Error");
      			licznik++;
      			return 0;
    		}   char pomoc[1000];
                char* pomoc1;
                pomoc1=getcwd(pomoc,1000);
                char wow[1000];
                memset(wow,0,sizeof(wow));
                if(strcspn(arg2,"/")==strlen(arg2))
                {
                     strcpy(wow,pomoc);
                    strcat(wow,"/");
                    strcat(wow,arg2);

               }
            else if(klucz=1)
                {
                    strcpy(wow,arg2);
                }
                else{

                strcpy(wow,"/home/students/s452686/");
                strcat(wow,arg2);
                }
		    int zapisana;
		    FILE * saved_file;

			saved_file = fopen(wow,"w");
			 if(saved_file == NULL)
   			 {
       			 perror("Error");

   			 }


    		while((zapisana=getc(opened_file))!=EOF)
            {
                putc(zapisana,saved_file);
            }

    		fclose(saved_file);
    		fclose(opened_file);
}

bool sprawdzenie(char* arg)
{
    if(chdir(arg)!=-1)
        return 1;
    else return 0;
}

int zliczanie(char* tab)
{
    char* schowek;
    schowek=strtok(tab,"/");
    int i=0;
    while(schowek !=NULL)
		{
			schowek=strtok(NULL,"/");
			i++;
		}
		return i;
}
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()

 {system("@cls||clear");
	char input[1000];
	char* schowek;
	char* arg[1000];
	char zapis[100][1000];
	char do_pliku[1000];
	//int licznik=0;
    char pomoc[1000];
    char* pomoc1;
    int licznik_chdir=0;
    char historia_chdir[1000][100];
    memset(historia_chdir,0,sizeof(historia_chdir));
    strcpy(historia_chdir[0],pomoc);
	cyan();
	printf("MicroShell SOP\nAutor Piotr Wygocki\n\n\n\n\n");
	printf("Type 'help' to get list of commands\n\n");

	while(1)
	{
    memset(pomoc,0,sizeof(pomoc));
    pomoc1=getcwd(pomoc,1000);
    memset(input,0,sizeof(input));
	yellow();
	printf("[");
	red();
	printf("%s:",getlogin());
	yellow();
	printf("%s",pomoc);
	printf("]\n");
	printf("$");
	cyan();
	fgets(input,1000,stdin);
	int dlugosc= strlen(input);
	if(dlugosc<2) continue;
	else
	{
	input[strlen(input)-1]=0;
	schowek=strtok(input," ");
	int i=0;
    int licznik_spacji=0;
    memset(arg,0,sizeof(arg));
    while(schowek !=NULL)
		{
            arg[i]=schowek;
			i++	;
			schowek=strtok(NULL," ");
			licznik_spacji++;

		}
	strcpy(zapis[licznik],arg[0]);
	if(strcmp(arg[0],"exit")==0)
		{
			break;
		}
	else if(strcmp(arg[0],"help")==0)
		{
				printf("\n***MicroShell SOP***\nAutor: Piotr Wygocki\n\n\n");
				printf("Available commands:\n");
				printf("-echo\n-cd\n-cp\n-help\n-exit\n-pwd\n-history\n-clear\n-touch\n-cat\n-rm\n");
	}
	else if(strcmp(arg[0],"pwd")==0)
		{
			printf("%s",pomoc);
			printf("\n");
	}

	else if(strcmp(arg[0],"clear")==0)
		{
			system("@cls||clear");
	}
	else if(strcmp(arg[0],"cd")==0)
		{
			if((arg[1]==0))
			{

        		char* home = getenv("HOME");
    			chdir(home);
            }else
			{   if(arg[2]!=0)
                {
                    printf("Error: Too many arguments.\n");
                    continue;
                }
                if(strcmp(arg[1],"~")==0)
                {
                    char* home = getenv("HOME");
                    chdir(home);
                }else if (strcmp(arg[1],"..")==0)
                {
                    chdir("..");
                }
                else if(strcmp(arg[1],"-")==0)
                {
                        chdir(historia_chdir[licznik_chdir]);

                }
                else
			    {
			        if(chdir(arg[1])==-1)
                    {
                        perror("Error");
                    }else chdir(arg[1]);
			    }

            }
            licznik_chdir++;
            strcpy(historia_chdir[licznik_chdir],pomoc);
        }
	else if(strcmp(arg[0],"echo")==0)
        {
         for(int i=1;i<licznik_spacji;i++)
         {
             printf("%s ",arg[i]);
         }printf("\n");
        }
    else if(strcmp(arg[0],"history")==0)
    {
        for(int i=0;i<=licznik;i++)
        {
            printf("%s\n",zapis[i]);
        }
    }
    else if(strcmp(arg[0],"touch")==0)
		{

			FILE * saved_file;
			saved_file = fopen(arg[1],"w");
			 if(saved_file == NULL)
   			 {
       			 perror("Error");
   			 }
    		fgets(do_pliku, 1000, stdin);
   			fputs(do_pliku,saved_file);
   			fclose(saved_file);
   			printf("Saved\n");
		}
		else if(strcmp(arg[0],"cp")==0)
		{
                if(strcmp(arg[1],"-r")==0)
                    {
                    if(sprawdzenie(arg[2]))
                    {
                        if(strcspn(arg[3],"/")!=strlen(arg[3]))//kopiowanie do innego katalogu xd
                            {
                                char xd[1000];
                                strcpy(xd,arg[3]);
                            int ile_sleszy=zliczanie(arg[3]);
                            char* home = getenv("HOME");
                            chdir(home);
                            char* schowek1;
                           schowek1=strtok(xd,"/");
                            int j=0;
                            while(j!=ile_sleszy-1)
                                {
                                    j++;
                                    chdir(schowek1);
                                    schowek1=strtok(NULL,"/");
                                }
                               mkdir(schowek1,0777);
                               chdir(schowek1);
                               char lokalizacja[1000];
                               char* lok;
                               lok=getcwd(lokalizacja,1000);
                               strcat(lokalizacja,"/");
                               chdir(pomoc);
                               chdir(arg[2]);
                                struct dirent *dir;
                                int moze=0;
                                char mamy_to[1000];
                                DIR* d = opendir(".");
                      if (d) {
                        while ((dir = readdir(d)) != NULL)
                           {
                                if(moze<2)
                                {
                                    moze++;
                                    continue;
                                }else{

                                strcpy(mamy_to,lokalizacja);
                                strcat(mamy_to,dir->d_name);
                                copy(dir->d_name,mamy_to,1);
                                memset(mamy_to,0,sizeof(mamy_to));
                                }
                            }
                                closedir(d);
                           }
                           chdir("..");
                            }
                        else{       //kopiowanie do tego samego katalogu
                        chdir("..");
                        mkdir(arg[3],0777);
                        char help_me[1000];
                        strcpy(help_me,pomoc);
                        strcat(help_me,"/");
                        strcat(help_me,arg[3]);
                        strcat(help_me,"/");
                       char mamy_to[1000];
                        chdir(arg[2]);
                        struct dirent *dir;
                        int moze=0;
                        DIR* d = opendir(".");
                      if (d) {
                        while ((dir = readdir(d)) != NULL)
                           {
                                if(moze<2)
                                {
                                    moze++;
                                    continue;
                                }else{

                                strcpy(mamy_to,help_me);
                                strcat(mamy_to,dir->d_name);
                                copy(dir->d_name,mamy_to,1);
                                memset(mamy_to,0,sizeof(mamy_to));
                                }
                            }
                     closedir(d);
                     chdir("..");

                      }
                        }
                    }
                    else
                    {
                    perror("Error");
                    }
                }
        else
            {
                if(sprawdzenie(arg[1])==1)
                {   chdir("..");
                    printf("Error: No such file\n");
                    continue;
                }
                  if(strcspn(arg[2],"/")==strlen(arg[2]))
                {
                    if(strcspn(arg[2],".")==strlen(arg[2]))
                    {
                            char wow[1000];
                             strcpy(wow,pomoc);
                            strcat(wow,"/");
                            strcat(wow,arg[2]);
                            strcat(wow,"/");
                            strcat(wow,arg[1]);
                            copy(arg[1],wow,0);
                    }
                     else
                     {
                        char wow[1000];
                         strcpy(wow,pomoc);
                        strcat(wow,"/");
                        strcat(wow,arg[2]);
                        copy(arg[1],wow,0);
                    }
                }
                    else
                        {
                            char wow[1000];
                            strcpy(wow,"/home/students/s452686/");
                             strcat(wow,arg[2]);
                            copy(arg[1],wow,0);
                        }
                }
		}
		else if(strcmp(arg[0],"cat")==0)
		{for(int i=1;i<licznik_spacji;i++)
		{

			char wyswietlana;
			FILE * opened_file;
			opened_file = fopen(arg[i],"r");
	 		if(opened_file == NULL)
    		{
      			perror("Error");
      			licznik++;
      			continue;

    		}
    		wyswietlana = fgetc(opened_file);
    		while (wyswietlana != EOF)
    		{
        		printf("%c", wyswietlana);
        		wyswietlana = fgetc(opened_file);

    		}
    		fclose(opened_file);
		}
		}
		else if(strcmp(arg[0],"rm")==0)
		{
        if( remove(arg[1])!=0 && strcmp(arg[1],"-r")>0)
    		{
      			perror("Error");
    		}
    		else

            {
                if(strcmp(arg[1],"-r")==0)
                {
                    struct dirent *dir;
                if(chdir(arg[2])!=-1)
                {
                    chdir(arg[2]);
                      DIR* d = opendir(".");
                      if (d) {
                        while ((dir = readdir(d)) != NULL)
                            {
                                remove(dir->d_name);
                            }
                     closedir(d);
                     chdir("..");
                     remove(arg[2]);
                        }
                }
                else
                {
                     perror("Error");
                }
                }else
                {
                {
                    remove(arg[1]);
                }
                }
            }

		}

        else
		{pid_t pid=fork();
		    if (pid == -1) {
                        perror("Error");
                        exit(1);
                } else if (pid == 0) {
                        execvp(arg[0], arg);
                        perror("Error");
                        exit(1);
                } else {
                        waitpid(pid, NULL, 0);
                }
		}

	licznik++;
	}
	}
	return 0;
}
