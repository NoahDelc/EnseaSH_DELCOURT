
#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define CMD_SIZE 100

const char msgWelcome[]= "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
const char prompt[] = "enseash %" ;
const char ExitMsg[] = "Bye bye... \n";
const char ExitToken[] = "exit";



int main(){	
	char cmd[CMD_SIZE];				//La commande tapée au clavier par l'utilisateur
	pid_t pid;
	
	write(STDOUT_FILENO, msgWelcome, sizeof(msgWelcome));  		//On affiche le message d'accueil une fois à l'ouverture du shell
	
	while(1){
		
		//Affichage de l'en-tête
		write(STDOUT_FILENO,prompt, sizeof(prompt));
		
		
		//Lecture de la commande utilisateur
		int cmdLenght = read(STDIN_FILENO, cmd, CMD_SIZE);
		cmd [cmdLenght-1]= '\0';          //On ajoute '\0' à la fin de la commande
		
		
		//Gestion de la commande "exit" et "ctrl+D"
		if ((strncmp(cmd, ExitToken , strlen(ExitToken)) == 0) || cmdLenght==0)  { 
			write(STDOUT_FILENO, ExitMsg, sizeof(ExitMsg));
			break;
		}
		
		//Processus Fils
		if((pid=fork())==0){
		execlp(cmd, cmd, ( char * )NULL);      //On execute la commande tapée par l'utilisateur
		exit(EXIT_FAILURE);
		}
		
		//Processus Père
		else{
			wait(NULL);
			}
	}

	exit(EXIT_SUCCESS);
}
