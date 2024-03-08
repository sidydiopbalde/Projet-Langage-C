#include<stdio.h>
#include "FONCTIONS.c"
#include <unistd.h>

int main()
{
int menuE,menuA, taille;
char motPasse[20],login1[20];

identification user[100];

int x;
do{
        readFichieruser( user,&taille); //lecture des info du fichier.txt dans le tableau user

        do{
            x=login(user,taille,motPasse, login1); 

        }while(x==3);

if(x==1)         
{
    do{
        menuA=menu_Admin(); //menu administrateur
        if(menuA==3)
        {
            maquerpresenceAdmin(motPasse);
        }  
    }while(menuA!=6);
}
    
else if(x==2)   
{
    do{
        menuE=menu_Apprenant(); //menu apprenant
        if(menuE==1)
        {marquerPresenceApprenant(login1, motPasse);}

    }while(menuE!=4);
    
}
}while(x!=3);
return 0;
}
