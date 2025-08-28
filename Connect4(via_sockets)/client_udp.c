#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#include "puissance4.h"

#define LEPORT 2020

    
int main()
{
    int s = 0, taille, bd, un_entier;
    struct sockaddr_in padin; //adresse internet locale
    struct sockaddr_in *p_exp; //pointeur vers adresse internet expediteur (recuperée de l'entete paquet UDP recu)
    socklen_t p_lgexp = sizeof(struct sockaddr_in);
    char *name = "localhost";
    char *adr_serv = "127.0.0.1";
    char msg[40] = "coucou c'est moi, ton client ENSEM";
    char msg1[40]; // pour recevoir ACK
    char nom[40];
    int p;
    int *p_lgexp1;

    struct hostent *host;

    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1)
    {
        perror("erreur creation socket");
        exit(EXIT_FAILURE);
    }
    printf("le socket est identifie par : %d \n", s);

    taille = sizeof(struct sockaddr_in);
    bzero((char *)&padin, taille);

    // Avec le DNS, on obtient l'adresse ip par gethostbyname()
    if ((host = gethostbyname(name)) == NULL)
    {
        perror("Nom de machine");
        exit(EXIT_FAILURE);
    }
    bcopy(host->h_addr_list[0], &padin.sin_addr, host->h_length);

    // si on connait l'adresse ip de destination en chiffre, on peut l'affecter directement:
    // un_entier=inet_aton(adr_serv, &padin.sin_addr);
    padin.sin_family = AF_INET;
    padin.sin_port = htons(LEPORT);

    printf("Quel est votre nom ?  ");
        //scanf("%s", msg); //pas de ENTREE à la fin, mais coupe si espace
        fgets(nom, 40, stdin); //ENTREE s'ajoute à la fin
        strcpy(joueurs[0].pseudo,nom);
        joueurs[0].couleur = CROIX;
        bd = sendto(s, nom, sizeof(msg), 0, (struct sockaddr *)&padin, sizeof(padin));
        if (bd == -1)
        {
            perror("Erreur send");
            exit(EXIT_FAILURE);
        }

        p_exp = (struct sockaddr_in *)(malloc(taille));
        p_lgexp1 = (int *)malloc(sizeof(int));
        *p_lgexp1 = sizeof(*p_exp);

        bd = recvfrom(s, msg1, sizeof(msg1), 0, (struct sockaddr *)p_exp, p_lgexp1);
        if (bd == -1)
        {
            perror("Erreur receive");
            exit(EXIT_FAILURE);
        }
        
        strcpy(joueurs[1].pseudo,msg1);
        joueurs[1].couleur = ROND;
        printf("Serveur : %s\n", joueurs[1].pseudo);

        afficher_plateau(tableau);
    while (1)
    {
////////////////////////////
        printf("le tour de %s \n ",joueurs[0].pseudo);
        //scanf("%s", msg); //pas de ENTREE à la fin, mais coupe si espace
        fgets(msg, 40, stdin); //ENTREE s'ajoute à la fin
        p = atoi(msg);
        while(p<1 || p>7 || combien_dans_colonne(tableau, p)==6){
                printf("Choisissez une colonne #(1-7) : \n");
                scanf("%i",&p);
            }
        sprintf(msg, "%d", p);
        bd = sendto(s, msg, sizeof(msg), 0, (struct sockaddr *)&padin, sizeof(padin));
        if (bd == -1)
        {
            perror("Erreur send");
            exit(EXIT_FAILURE);
        }
        empiler(tableau, p, joueurs[0].couleur);
        afficher_plateau(tableau);
        compteur++;
            if (test_tout(tableau, joueurs[0].couleur, p)!=-1){
                printf("Le gagnant de cette partie est le joueur %i %s\n", 
                joueurs[0].couleur, joueurs[0].pseudo);

                exit(EXIT_FAILURE);
            } else if (compteur == (7*6)){
                printf("La partie est finie ");
                
                exit(EXIT_FAILURE);
            }
        
//////////////////////////////

        p_exp = (struct sockaddr_in *)(malloc(taille));
        p_lgexp1 = (int *)malloc(sizeof(int));
        *p_lgexp1 = sizeof(*p_exp);

        bd = recvfrom(s, msg1, sizeof(msg1), 0, (struct sockaddr *)p_exp, p_lgexp1);
        if (bd == -1)
        {
            perror("Erreur receive");
            exit(EXIT_FAILURE);
        }
        printf("Serveur : %s\n", msg1);
        empiler(tableau, atoi(msg1), joueurs[1].couleur);
        afficher_plateau(tableau);
        compteur++;
            if (test_tout(tableau, joueurs[1].couleur, atoi(msg1))!=-1){
                printf("Le gagnant de cette partie est le joueur %i %s\n",
                 joueurs[1].couleur, joueurs[1].pseudo);

                exit(EXIT_FAILURE);
            } else if (compteur == (7*6)){
                printf("La partie est finie ");
                
                exit(EXIT_FAILURE);
            }
///////////////////////////////
    }
    close(s);
    return 0;
}
