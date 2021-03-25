#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include <shadow.h>
#include <pwd.h>

//Donner les droit root a l'utilisateur
void tester_setreuid()
{ 
// mettre variable pour mettre id
  uid_t uid_reel;
  uid_t uid_eff;
//recup id donc user et root
  uid_reel = getuid();
  uid_eff = geteuid();
//interchanger les 2
  uid_eff, setreuid(uid_eff, -1); 
}

//Vérifier le password 
int password ()
{ 
//on récupere le password depuis les variables d'environnement getenv
  char *motDePasse = getspnam(getenv("USER"))->sp_pwdp; 
  //creer varibale mot et recupere le contenue
  char *mot = "";
  mot = getpass("Password: ");
  
//on vérifie si le mdp rentré et le mdp du user sont identique avec strcmp si c'est le meme return 1
  if (strcmp(crypt(mot, motDePasse), motDePasse) == 0) { 
    return (1);
  } else {
    printf("Sorry, try again\n");
    return (0);
  }
  return (0);
}

//Vérifier si la command est éxecutable
int checkcommand(char *command)
{ 
//return different 0 si la commande existe pas -> command not found
  if (system(command) != 0 && system(command) != 512) {
    system("clear");
    printf("sudo: ");
    printf (command);
    printf(": command not found\n");
    return (1);
//return 512 si la commande lui manque des parametre 
  } else if (system(command) == 512) {
    system("clear");
    printf (command);
    printf(": No such file or directory\n");
    return (2);
//return 0, commande bonne 
  } else {
    system("clear");
    return (3);
  }
}

//récuperer la commande dans une string
char *getcommand(char **command)
{
  //creer var size pour la mettre en string
  int size = 0;
  char *retstr;
  
//trouver la taille de la string finale  
  for (int i = 0; command[i] != 0; i++) {
      //lit mot par mot et lettre par lettre
    for (int j = 0; command[i][j] != 0; j++) {
      size++;
    }
    size++;
  }

//Calloc fait comme Malloc il aloue la mémoir sauf qu'il initialise la mémoir a 0
  retstr = calloc(size - 1, sizeof(char));
  for (int i = 1; command[i] != 0; i++) {
      //Chaque arg passe a la ligne 1 par 1
    strcat(retstr, command[i]);
//return un espace entre chaque param
    strcat(retstr, " ");
  }
//return la string
  return retstr;
}

//récuperer la commande dans une string si l'option --user est appeller
char *getcommand_user(char **command)
{ 
  int size = 0; 
  char *retstr = "";
  
  for (int i = 0; command[i] != 0; i++) {
    for (int j = 0; command[i][j] != 0; j++) {
      size++;
    }
    size++;
  }
//malloc alloue de la memoire
  retstr = malloc(sizeof(char) * size - 1);
  size = 0;
  
  for (int i = 3; command[i] != 0; i++) {
    for (int j = 0; command[i][j] != 0; j++) {
      retstr[size] = command[i][j];
      size++;
    }
//change de mot on mets un espace
    retstr[size] = ' ';
    size++;
  }
//Pour le \0
  retstr[size - 1] = 0;
  return (retstr);
}

//donner les droit du user demander pour l'option --user
int user_option(int ac, char **av)
{ 
//--user Babyshark et le user apres dcp 3 argument on peu rentrer dans le if
  if (ac >= 3){
//regarde si ya bien --user si il appel on rentre dans le if
    if (strcmp(av[1], "--user") == 0) {
// on crée une variable qui va contenir le nouveau user, utilisateur dans user
      char *user = av[2]; 
      char cmd[1000];
//getent passwd user > /dev/null 2>&1 (pour savoir si l'utilisateur existe)
//creer une string pour avoir la commande
      strcpy(cmd, "getent passwd ");
      strcat(cmd, user);
      strcat(cmd, " > /dev/null 2>&1");
//si il existe tu rentre 
      if (!system(cmd)) {
	struct passwd *pwd;
	pwd = getpwnam(user); 
// on récupere l'uid du nouveau user 
	int uid = pwd->pw_uid; 
	uid_t uid_reel;
	uid_t uid_eff;
	uid_reel = getuid();
	uid_eff = geteuid();
// on modifie l'uid du user courant avec le nouveau user                
	uid_eff, setreuid(uid, uid_reel); 
	return (1);
      } else {
//pas de user 
	system("clear");
	printf("sudo: unknown user: %s \n", user);
	return (2);
      }
    } else {
      return (3);
    }
  }
  return (3);
}


int main(int argc, char *argv[])
{
  char *command = "";
//on met la command dans une variable
  command = getcommand(argv);
//verification pswd/entrer psw
  if (password() == 1){
//verifie si on appelle l'option --user
    if (user_option(argc, argv) == 1) {
      command = getcommand_user(argv);
//on vérifie si la command est éxecutable 
      if (checkcommand(command) == 3) {
// si la commande est éxecutable on l'éxecute
	system(command);
	return (0); 
      }
//sverification appelle pas option --user genre cat ou ls
    } else if (user_option(argc, argv) == 3) {
      tester_setreuid();
      command = getcommand(argv);
//verification commande est bonne 
      if (checkcommand(command) == 3) {
	system(command);
      }
    }
  }
  return (0);
}
