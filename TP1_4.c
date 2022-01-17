
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
	char cmd[CMD_SIZE];   //La commande tapée au clavier par l'utilisateur
	pid_t pid;
	int status;
	char CodeReturn[CMD_SIZE];
	char SigReturn[CMD_SIZE];
	
	
	write(STDOUT_FILENO, msgWelcome, sizeof(msgWelcome));				//On affiche le message d'accueil une fois à l'ouverture du shell
	write(STDOUT_FILENO,prompt, sizeof(prompt));						//On affiche également l'en-tête une première fois
	
	while(1){
		
		//Lecture de la commande utilisateur
		int cmdLenght = read(STDIN_FILENO, cmd, CMD_SIZE);
		cmd [cmdLenght-1]= '\0';    									//On ajoute '\0' à la fin de la commande
		
		
		//Gestion de la commande "exit" et"ctrl+D"
		if ((strncmp(cmd, ExitToken , strlen(ExitToken)) == 0) || cmdLenght==0)  { 
			write(STDOUT_FILENO, ExitMsg, strlen(ExitMsg));
			break;
		}
		
		//Processus Fils
		if((pid=fork())==0){
		execlp(cmd, cmd, ( char * )NULL);
		exit(EXIT_FAILURE);
		}
		//Processus Père
		else{
			wait(&status);
			}
		
		//Etude du statut renvoyé par le fils terminé	
		if (WIFEXITED(status)){
			sprintf(CodeReturn, "enseash [code exit : %d] %%", WEXITSTATUS(status));
			write(STDOUT_FILENO,CodeReturn, strlen(CodeReturn));
			}
		else if	(WIFSIGNALED(status)){
			sprintf(SigReturn, "enseash [signal exit : %d] %%", WTERMSIG(status));
			write(STDOUT_FILENO,SigReturn, strlen(CodeReturn));
			}	
	}

	exit(EXIT_SUCCESS);
}
