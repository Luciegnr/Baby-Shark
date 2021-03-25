#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int ask_user_name()
{
  printf("\nBonjour,\n");
  printf("Veuillez entrer votre nom d'utilisateur ici : ? " );
  char new_user = "";

  if (new_user) {
    printf("\nVotre nom d'utilisateur est vide !\n");
    printf("Voulez-vous réessayer : O/n (défaut Oui) ? ");
    char re_try;
    return 0;
  }
      char re_try = "O";
      if (re_try) {
          printf("\nOK, on recommence.");
          ask_user_name();
          return 0;
      } else {
          printf("\nTant pis, je ne peux pas tester votre nom d'utilisateur.\nAu revoir.\n");
          return 0;
    }
    return 0;
}

int check_user_name() 
{
  char new_user;
  if ("REFUSED_NAME" != 0) {
    if (id -u new_user > /dev/null 2>&1) {
          return 0;
    } else {
          return 1;
    }
  }
      
}

int show_user_name()
{
  case $VALID_USER in
    0)
      printf("\nLe nom d'utilisateur $new_user est valide.\nMerci et au revoir.\n");
    *)
      printf("\nDésolé, ce script n'accepte pas le nom d'utilisateur $new_user !\nVeuillez recommencer avec un nom d'utilisateur valide.\nAu revoir.\n");
  return 0;
}

int main(int argc, char *argv[]) 
{
    check_user_name();
    show_user_name();
    ask_user_name();
}