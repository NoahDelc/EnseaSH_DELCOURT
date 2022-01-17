#include <stdio.h> 
#include <stdlib.h> 
#include <fcntl.h>
#include <unistd.h>

const char msgWelcome[]= "Bienvenue dans le Shell ENSEA.\nPour quitter, tapez 'exit'.\n";
const char prompt[] = "enseash %" ;


int main(){	
	
	write(STDOUT_FILENO, msgWelcome, sizeof(msgWelcome)); 		//On affiche le message d'accueil une fois à l'ouverture du shell
	write(STDOUT_FILENO,prompt, sizeof(prompt));				//On affiche également l'en-tête une première fois
	
	exit(EXIT_SUCCESS);
}
	

