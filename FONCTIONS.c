#include<stdio.h>
#include <string.h>
#include <termios.h>
#include<ctype.h>
#include <unistd.h>
#include <time.h>

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
}while(choix<1 || choix>6);
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
typedef struct{
    char username[20];
     char mdp[20];
     char codeE;
}code;
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
        strcpy(user[x].username, username);  //copie de la chaine lue username dans le tableau user
        strcpy(user[x].mdp, mdp);
        user[x].statut = stat;
        x++;
}
*taille=x;
fclose(fp);
}


// fonction pour masquer la saisie de l'utilisateur
void desactiver(void) {
    struct termios old_attr, new_attr;
     
    tcgetattr(STDIN_FILENO, &old_attr);
    new_attr = old_attr;
    new_attr.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}

//fonction pour afficher la saisie d'un utilisateur
void reactiver(void) {
    struct termios old_attr, new_attr; 
    tcgetattr(STDIN_FILENO, &old_attr);
    new_attr = old_attr;
    new_attr.c_lflag |= (ECHO | ECHOE | ECHOK | ECHONL | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_attr);
}
//fonction pour récupérer le mot de passe
void getPassWord(char * password){
    int i = 0;
    char ch;
    
    printf("Entrez votre mot de passe : ");
    desactiver(); // Masquage de la saisie de l'utilisateur

    while (1) {
        ch = getchar(); // On recupere les caractères que l'utilisateur à saisie
 
        if (ch == '\n') {
            password[i] = '\0';
            break;
        } else {
            password[i++] = ch;
            printf("*"); // Affichage des étoiles 
            fflush(stdout); // Forcer l'affichage de l'étoile
        }
     }
    putchar('\n');
    reactiver(); // Réaffichage de la saisie de l'utilisateur
}

int login(identification user[],int taille,char *motPasse,char login[]) // fonction pour demander le login et le mot de passe de l'utilisateur
{
    char mdp[20],c;
     char username[50];
     printf("************Connexion************\n");
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

      //mdp= getpass("Entrez votre mot passe: ");
        getPassWord(mdp); //masquer le mot de passe
  
      for (int i = 0; i < taille; i++) {
        if (strcmp(user[i].username, username) == 0 && strcmp(user[i].mdp, mdp) == 0) {
            strcpy(motPasse,mdp);
            strcpy(login,username);
            return user[i].statut;
        }
    }
    printf("informations  éronnée.\n");
    return 3;

}
void maquerpresenceAdmin(char motPasse[])  //fonction pour marquer la présence de l'apprenant
{
   char ligne[100];
    char username[50], mdp[50];
    char cod[20],x=0;
    char rep;char mat[10],classe[10];
    do{
 
     printf("Entrez votre code[Q pour quitter]\n");
     fflush(stdin);
     getchar();
     scanf("%s",mat);
     if(strcmp(mat,"Q")==0)
     {
         fflush(stdin);
        getchar();
        getPassWord(mdp);
        /*printf("donner votre mot de passe pour confirmer\n");
        fflush(stdin);
        getchar();
        scanf("%s",mdp);*/
        if(strcmp(mdp,motPasse)==0) break;
        else{continue;}
     }
     FILE* fp = fopen("devData.txt", "r");
     if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
     }
    
    while(fgets(ligne, sizeof(ligne), fp) != NULL) 
    {
        sscanf(ligne,"%s %s %s %s", cod,username,mdp,classe); 
        if(strcmp(cod,mat)==0)
        { x=1; break;} 
    }
    if(x==1)
    {
    
    time_t t;
    struct tm *info;
    time(&t);
    info = localtime(&t); //récuparation du temps local

    char current_date[20];
    strftime(current_date, sizeof(current_date), "%d/%m/%Y", info);

    char line[100]; char cd[10],m=0; char date[50],nom[50],prenom[50];

    //ouverture de la liste de présence 
    FILE* fa = fopen("Presence.txt", "r");
     if (fa == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
     }
     //vérifier si l'étudiant est dèjà marqué présent
     while(fgets(line, sizeof(line), fa) != NULL) 
    {
        sscanf(line,"%s %s %s %s", cd,prenom,nom,date); 
        if(strcmp(cd,cod)==0 && strcmp(date,current_date)==0)

        { m=1; break;} 
    }
    if(m==1){printf("vous etes deja marqué");}
    else
    {
         FILE* fc = fopen("Presence.txt", "a");
        if (fc == NULL) {
            printf("Impossible d'ouvrir le fichier.\n");
        }
        printf("Marqué présent avec succés\n");
        fprintf(fc," %s %s %s %s %02d/%02d/%04d %02d:%02d:%02d\n",cod,username,
        mdp,classe,info->tm_mday, info->tm_mon + 1, info->tm_year + 1900,info->tm_hour, info->tm_min, info->tm_sec);

         fclose(fc);
    }
    } 
    else if (x==0)
    {printf(" XX code Invalide!!!\n");}

        printf("Appuyer sur une touch pour continuer....\n");
    fflush(stdin);
    getchar();
    scanf("%c",&rep);
 
    }while(rep=='a' || rep=='b');  
}

 void marquerPresenceApprenant(char login[],char motPasse[])
{
    FILE* fp = fopen("devData.txt", "r"); //ouverture du fichier contenant les matricules des apprenants
     if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
     }
    char ligne[100];
    char username[50], mdp[50];
    char cod[10];
    while(fgets(ligne, sizeof(ligne), fp) != NULL) //parcourir les lignes du fichier pour récupérer les informations de l'apprenants 
    {
        sscanf(ligne,"%s %s %s", cod,username,mdp); 
         if (strcmp(login, username) == 0 && strcmp(motPasse, mdp) == 0) {
              break;
        }
    }
        fclose(fp);
     time_t t;
    struct tm *info;
    time(&t);
    info = localtime(&t);

     char current_date[20];
    strftime(current_date, sizeof(current_date), "%d/%m/%Y", info);

    char line[100], cd[10],m=0; char date[50],nom[50],prenom[50];
    FILE* fa = fopen("Presence.txt", "r");
     if (fa == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
     }

     while(fgets(line, sizeof(line), fa) != NULL) 
    {
        sscanf(line,"%s %s %s %s", cd,prenom,nom,date); 
        if(strcmp(cd,cod)==0 && strcmp(date,current_date)==0) //recherche du matricule de l'étudiant dans la liste des présents
        { m=1; 
        break;
        } 
    }
    if(m==1){printf("vous êtes dèjà marqué!!\n");}
    
    else{ //si l'étudiant ne se trouve pas dans la liste des présents on le marque
            FILE* fc = fopen("Presence.txt", "a");
     if (fc == NULL) {
        printf("Impossible d'ouvrir le fichier.\n");
     }
     printf("Marqué présent avec succés!!!!\n");
     // ecriture des informations de l'appprenant dans le fichier ou on marque les présences
    fprintf(fc," %s %s %s %02d/%02d/%04d %02d:%02d:%02d\n",cod,username,mdp,
    info->tm_mday, info->tm_mon + 1, info->tm_year + 1900,info->tm_hour, info->tm_min, info->tm_sec);
    fclose(fc);
    
    }
    }

//Generer fichier
typedef struct {
    char cod[10];
    char username[50];
    char mdp[50];
    char classe[50];
    int day;
    int month;
    int year;
    int hour;
    int min;
    int sec;
} PresenceInfo;

void imprimerTableau(FILE* fichier, char formattedDate[]) {
    fprintf(fichier, "\nDate: %s\n", formattedDate);
   fprintf(fichier, "+------------+----------------------+----------------------+--------+\n");
    fprintf(fichier, "| Code       | Nom                  | Prénom               | Classe |\n");
    fprintf(fichier, "+------------+----------------------+----------------------+--------+\n");
}

void ajouterLigneTableau(FILE* fichier, PresenceInfo presenceData) {
    fprintf(fichier, "| %-10s | %-20s | %-20s | %-6s |\n",
            presenceData.cod, presenceData.username, presenceData.mdp, presenceData.classe);
}

void regrouperParDate() {
    FILE* fpPresence = fopen("Presence.txt", "r");
    if (fpPresence == NULL) {
        printf("Impossible d'ouvrir le fichier Presence.txt en mode lecture.\n");
        return;
    }

    PresenceInfo presenceData[100];
    int nbPresences = 0;

    while (fscanf(fpPresence, "%s %s %s %s %d/%d/%d %d:%d:%d", presenceData[nbPresences].cod,
                  presenceData[nbPresences].username, presenceData[nbPresences].mdp, presenceData[nbPresences].classe,
                  &presenceData[nbPresences].day, &presenceData[nbPresences].month, &presenceData[nbPresences].year,
                  &presenceData[nbPresences].hour, &presenceData[nbPresences].min, &presenceData[nbPresences].sec) == 10) {
        nbPresences++;
    }

    fclose(fpPresence);

    if (nbPresences == 0) {
        printf("Aucune donnée de présence trouvée dans le fichier Presence.txt.\n");
        return;
    }

    // Triez les données par date
    for (int i = 0; i < nbPresences - 1; i++) {
        for (int j = i + 1; j < nbPresences; j++) {
            // Comparez les dates en considérant les jours, mois et années
            if (presenceData[i].year > presenceData[j].year ||
                (presenceData[i].year == presenceData[j].year && presenceData[i].month > presenceData[j].month) ||
                (presenceData[i].year == presenceData[j].year && presenceData[i].month == presenceData[j].month && presenceData[i].day > presenceData[j].day)) {
                PresenceInfo temp = presenceData[i];
                presenceData[i] = presenceData[j];
                presenceData[j] = temp;
            }
        }
    }

    FILE* fpGroupedByDate = fopen("GroupedByDate.txt", "w");
    if (fpGroupedByDate == NULL) {
        printf("Impossible d'ouvrir le fichier GroupedByDate.txt en mode écriture.\n");
        return;
    }

    char currentDate[20] = "";
    imprimerTableau(fpGroupedByDate, "Date");
    
    for (int i = 0; i < nbPresences; i++) {
        char formattedDate[20];
        sprintf(formattedDate, "%02d/%02d/%04d", presenceData[i].day, presenceData[i].month, presenceData[i].year);

        if (strcmp(formattedDate, currentDate) != 0) {
            // Si la date change, imprimez la nouvelle date et les en-têtes des colonnes
            fprintf(fpGroupedByDate, "+------------+----------------------+----------------------+--------+\n");
            imprimerTableau(fpGroupedByDate, formattedDate);
            strcpy(currentDate, formattedDate);
        }

        // Écrivez les informations de présence dans le tableau
        ajouterLigneTableau(fpGroupedByDate, presenceData[i]);
    }

    fprintf(fpGroupedByDate, "+------------+----------------------+----------------------+--------+\n");

    fclose(fpGroupedByDate);

    printf("Les données ont été regroupées par date dans le fichier GroupedByDate.txt.\n");
}
//fonction pour valider la date entrée par l'administrateur
void VerifierDate(int J, int M, int A ,int *x)
{
   //x=0; permet de demander encore la date si elle est fausse
   
         if(M==4 || M==6 || M==9 || M==11)
      {
      if(J>30)
      {
        *x=0;
        printf("%d / %d / %d Invalide!!\n",J,M,A);
      }
      }
      else if(A>0 && ((A%4!=0 ||  A%100==0) && A%400!=0  ))
    {if(M==2){
      if(J>28)
        {
            *x=0;
          printf("%d / %d / %d Invalide!!\n",J,M,A);
        }
    }
    }
    else if((J<=0 || J>31) || (M<=0 || M>12) || (A<=0))

        { *x=0; printf("%d / %d / %d Invalide!!\n",J,M,A);}
      else if((J>0 && J<=31) && (M>0 && J<=12) && (A>0))
        { *x=1; printf("%d /%d /%d est une date valide\n",J,M,A);} 
 
       
 } 
 
    
void genererDateIsoler(){
 
     int j,m,a,x;
     do{
             printf("Entrez la date\n");
            scanf("%d%d%d",&j,&m,&a);
            VerifierDate(j,m,a,&x);

     }while(x==0); 
}


void genererDesFichiers()
{
    int x;
    printf("**********GENERATION DE FICHIERS*********\n");
    printf("Veuillez choisir une option\n1-liste compléte des présences\n2-Liste de présence par date\n");
    scanf("%d",&x);
  if(x==1)
  {
    regrouperParDate();
  }
}


