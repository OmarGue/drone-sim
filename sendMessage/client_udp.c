#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

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

    while (1)
    {
        printf("Quel est votre message ?  ");
        //scanf("%s", msg); //pas de ENTREE à la fin, mais coupe si espace
        fgets(msg, 40, stdin); //ENTREE s'ajoute à la fin

        bd = sendto(s, msg, sizeof(msg), 0, (struct sockaddr *)&padin, sizeof(padin));
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
        printf("Serveur : %s\n", msg1);
    }
    close(s);
    return 0;
}
