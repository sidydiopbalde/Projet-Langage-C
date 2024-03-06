 #include<stdio.h>
#include "FONCTIONS.c"
#include <unistd.h>

int main()
{
int menuE,menuA, taille;;



identification user[100];

readFichieruser( user,&taille); //lecture des info du fichier.txt dans le tableau user

int x;
do{
     x=login(user,taille); //

}while(x==3);

if(x==1)         // 1 correspond à l'admin
{
    menuA=menu_Admin();
    if(menuA==3)
    {
       maquerpresenceAdmin(); 
}
    }
    
else if(x==2)   // 2 correspond à l'apprenant

{
    menuE=menu_Apprenant();
}


    return 0;
}