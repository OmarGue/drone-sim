#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

#include "puissance4.h"

#define LEPORT 2020
#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];
void Lire_file(char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        printf("Le contenu est ; %s\n", buffer);
    }
    fclose(file);
    
}

int main() {
    int s = 0, taille, bd, error_number, lg = 40;
    char msg[40];
    char msg1[40] = "message bien recu ";
    char msg2[40] = "blabla";
    char nom[40];
    int p;
    struct sockaddr_in *padin; //pointeur adresse internet locale
    struct sockaddr_in *p_exp; //pointeur adresse internet expediteur (recuperée de l'entete paquet UDP recu)
    
    s = socket(AF_INET, SOCK_DGRAM, AF_UNSPEC);
    if (s == -1) {
        perror("erreur creation socket");
        exit(EXIT_FAILURE);
    }
    printf("le socket est identifie par : %d \n", s);

    taille = sizeof(struct sockaddr_in);
    padin = (struct sockaddr_in *)(malloc(taille));
    bzero((char *)padin, taille);

    padin->sin_family = AF_INET;
    padin->sin_port = htons(LEPORT);

    bd = bind(s, (struct sockaddr *)padin, taille);
    if (bd == -1) {
        perror("Erreur d'attachement");
        exit(EXIT_FAILURE);
    }

    p_exp = (struct sockaddr_in *)(malloc(sizeof(struct sockaddr_in)));
    socklen_t p_lgexp = sizeof(struct sockaddr_in);

    bd = recvfrom(s, msg, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if (bd == -1) {
            perror("Erreur receive");
            exit(EXIT_FAILURE);
        }
        strcpy(joueurs[0].pseudo,msg);
        joueurs[0].couleur = CROIX;
        printf("Client : %s\n", joueurs[0].pseudo);

        printf("Quel est votre nom ?  ");
        fgets(nom, 40, stdin);
        strcpy(joueurs[1].pseudo,nom);
        joueurs[1].couleur = ROND;
        bd = sendto(s, nom, lg, 0, (struct sockaddr *)p_exp, sizeof(*p_exp));
        if (bd == -1) {
            perror("Erreur send");
            exit(EXIT_FAILURE);
        }
    afficher_plateau(tableau);
    while (1) {
/////////////////////////////////////
        bd = recvfrom(s, msg, lg, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if (bd == -1) {
            perror("Erreur receive");
            exit(EXIT_FAILURE);
        }
        printf("Client : %s\n", msg);
        empiler(tableau, atoi(msg), joueurs[0].couleur);
        afficher_plateau(tableau);
        compteur++;
            if (test_tout(tableau, joueurs[0].couleur, atoi(msg))!=-1){
                printf("Le gagnant de cette partie est le joueur %i %s\n",
                 joueurs[0].couleur, joueurs[0].pseudo);

                exit(EXIT_FAILURE);
            } else if (compteur == (7*6)){
                printf("La partie est finie ");
                
                exit(EXIT_FAILURE);
            }
        

//////////////////////////////////////
        printf("le tour de %s \n ",joueurs[1].pseudo);
        fgets(msg2, 40, stdin);
        p = atoi(msg2);
        while(p<1 || p>7 || combien_dans_colonne(tableau, p)==6){
                printf("Choisissez une colonne #(1-7) : \n");
                scanf("%i",&p);
            }
        sprintf(msg2, "%d", p);
        bd = sendto(s, msg2, lg, 0, (struct sockaddr *)p_exp, sizeof(*p_exp));
        if (bd == -1) {
            perror("Erreur send");
            exit(EXIT_FAILURE);
        }
        empiler(tableau, p, joueurs[1].couleur);
        afficher_plateau(tableau);
        compteur++;
            if (test_tout(tableau, joueurs[1].couleur, p)!=-1){
                printf("Le gagnant de cette partie est le joueur %i %s\n", 
                joueurs[1].couleur, joueurs[1].pseudo);

                exit(EXIT_FAILURE);
            } else if (compteur == (7*6)){
                printf("La partie est finie ");
                
                exit(EXIT_FAILURE);
            }
        
/////////////////////////////////   
    }

    // Free allocated memory
    free(padin);
    free(p_exp);

    close(s);
    return 0;
}
