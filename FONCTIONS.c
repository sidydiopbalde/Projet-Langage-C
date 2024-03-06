#include<stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include<ctype.h>
#include <unistd.h>

int  menu_Admin()
{
     int choix;
     printf("***********MENU-ADMIN***********\n");
     printf("1........GESTION DES ETUDIANTS\n");
     printf("2........GENERATION DE FICHIERS\n");
     printf("3........MARQUER LES PRÉSENCES\n");
     printf("4........ENVOYER UN MESSAGE\n");
     printf("5........#Paramètre#\n");
     printf("6........Deconnexion\n");
do{
      puts("Entrez votre choix\n");
      scanf("%d",&choix);
     if(choix<1 || choix>6)
    {
     printf("Choix invalide!!\n");
    }
}while(choix<1 || choix>5);
   return choix;
}
int  menu_Apprenant()
{
     int choix;
     printf("***********MENU-APPRENANT***********\n");
     printf("1........MARQUER MA PRÉSENCE\n");
     printf("2........NOMBRE DE MINUTES D'ABSENCE\n");
     printf("3........MES MESSAGESÀ( ) \n");
     printf("4........DECONNEXION\n");
     puts("**************************************\n");
do{
      puts("Entrez votre choix\n");
      scanf("%d",&choix);
     if(choix<1 || choix>4)
    {
     printf("Choix invalide!!\n");
    }
}while(choix<1 || choix>4);
   return choix;
}

typedef struct 
{
     int id;
     char matricule[10];
     char prenom[20];
     char nom[20];
     char motdepasse[10];
     int nbrRetard;
     int presence;
}Etudiant;
typedef struct
{
     char username[20];
     char mdp[20];
     int statut;

}identification;
typedef struct{}termios;
void readFichieruser( identification user[],int *taille)
{
     
    int  x=0;
     FILE* fp = fopen("fichier.txt", "r"); //ouverture du fichier en mode lecture
    if (fp== NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    char ligne[100];

    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        char username[50], mdp[50];
        int stat;
        sscanf(ligne, "%[^,],%[^,],%d", username, mdp, &stat);  //lecture des lignes du fichier dans le tableau user
        strcpy(user[x].username, username);  //copie de la chaine lusername dans le tableau user
        strcpy(user[x].mdp, mdp);
        user[x].statut = stat;
        x++;
}
*taille=x;
fclose(fp);
}

int login(identification user[],int taille)
{
    char *mdp,c;
     char username[50];
do{
     printf("Entrez ton username: ");
      scanf("%s",username);
      username[strcspn(username,"\n")]='\0';
if(strlen(username)==0)
{
    printf("invalide!\n");
}
else if(isspace((unsigned char)username[0])){
    printf("invalide\n");

}
else{break;}
}while(strlen(username) == 0 || strspn(username, " ") == strlen(username) || isspace((unsigned char)username[0]));
     
            
        fflush(stdin);
        getchar();

       mdp= getpass("Entrez votre mot passe: "); //pour cacher le mot de passe
      for (int i = 0; i < taille; i++) {
        if (strcmp(user[i].username, username) == 0 && strcmp(user[i].mdp, mdp) == 0) {
            return user[i].statut;
        }
    }
     printf("informations  éronnée.\n");
    return 3;

}

void maquerpresenceAdmin()
{
     printf("voici la liste des classes\n");
     FILE *fp;
    char ligne[100]; 
    fp = fopen("listeClasse.txt", "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
    }
    while (fgets(ligne, sizeof(ligne), fp) != NULL) {
        
        printf("%s", ligne);
    }
    int classe;

    printf("Veuillez choisir la classe de l'étudiant(1-devWeb,2-refDig-3-devData\n");
    scanf("%d",&classe);
    if(classe==1)
    {
        FILE *fc;
        FILE *fs;
        fc = fopen("devWeb.txt", "r");
        printf("liste des étudiants devWeb\n");
        while (fgets(ligne, sizeof(ligne), fc) != NULL)
         {
            printf("%s", ligne);
            printf("\n");
         }
         char nom[50];
         printf("Select Etudiant:\n");
         scanf("%s",nom);
        fs=fopen("Presence.txt","a");
        fprintf(fs,"%s\n",nom);
    }
    

    
}

