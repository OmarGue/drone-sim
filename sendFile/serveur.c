#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>
#define LEPORT 2020
#define BUFFER_SIZE 1000024

int main() {
    int s = 0, taille, bd, error_number, lg = 40;
    char msg[BUFFER_SIZE];
    char msg1[40] = "message bien recu ";
    char msg2[40] = "blabla";
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

    while (1) {
        bd = recvfrom(s, msg, BUFFER_SIZE, 0, (struct sockaddr *)p_exp, &p_lgexp);
        if (bd == -1) {
            perror("Erreur receive");
            exit(EXIT_FAILURE);
        }
        msg[bd] = '\0';
        printf("Client : '%s'\n", msg);
        FILE *file = fopen("commandDrone.txt", "wb");
        if (file == NULL) {
            perror("Erreur lors de l'ouverture du fichier");
            continue;  // Continue to the next iteration of the loop
        }
        fwrite(msg, 1, strlen(msg), file);
        fclose(file);

        printf("Quel est votre message ?  ");
        fgets(msg2, 40, stdin);

        bd = sendto(s, msg2, lg, 0, (struct sockaddr *)p_exp, sizeof(*p_exp));
        if (bd == -1) {
            perror("Erreur send");
            exit(EXIT_FAILURE);
        }
        
    }

    // Free allocated memory
    free(padin);
    free(p_exp);
    
    close(s);
    return 0;
}