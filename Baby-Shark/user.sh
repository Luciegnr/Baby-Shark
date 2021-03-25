#!/bin/sh                                                                                                                                                                                                                                                                                                

ask_user_name()
{
  echo "\nBonjour,\n"
  read -p "Veuillez entrer votre nom d'utilisateur ici : ? " new_user
  if [ "$new_user" = "" ]
    then
      echo "\nVotre nom d'utilisateur est vide !\n"
      read -p "Voulez-vous réessayer : O/n (défaut Oui) ? " re_try
      if [ "$re_try" = "" ] ||  [ "$re_try" = "O" ] ||  [ "$re_try" = "O" ]
        then
          echo "\nOK, on recommence."
          ask_user_name
        else
          echo "\nTant pis, je ne peux pas tester votre nom d'utilisateur.\nAu revoir.\n"
          exit 0
      fi
  fi
}


check_user_name()
{
  if [ "$REFUSED_NAME" != 0 ]
    then
      if id -u "$new_user"> /dev/null 2>&1
        then
          VALID_USER=0
        else
          VALID_USER=1
      fi
  fi
}

show_user_name()
{
  case $VALID_USER in
    0)
      echo "\nLe nom d'utilisateur $new_user est valide.\nMerci et au revoir.\n";;
    *)
      echo "\nDésolé, ce script n'accepte pas le nom d'utilisateur $new_user !\nVeuillez recommencer avec un nom d'utilisateur valide.\nAu revoir.\n";;
  esac
}

clear
ask_user_name

check_user_name
show_user_name
exit 0