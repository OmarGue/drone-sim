#include "puissance4.h"


int main()
{
    
    
    char a[20]; char b[20];

    printf("Le nom du premier joueur : \n");
    scanf(" %s",a);
    printf("Le nom du deuxième joueur : \n");
    scanf(" %s",b);

    strcpy(joueurs[0].pseudo,a);
    joueurs[0].couleur = CROIX;
    strcpy(joueurs[1].pseudo,b);
    joueurs[1].couleur = ROND;
    
    
    
    do {
        for (int i=1;i<=2;i++){
            couleur = i;
            afficher_plateau(tableau);

            int p;
            printf("Le tour de %s \n",joueurs[i-1].pseudo);
            scanf("%i",&p);

            while(p<1 || p>7 || combien_dans_colonne(tableau, p)==6){
                printf("Choisissez une colonne #(1-7) : \n");
                scanf("%i",&p);
            }
            
            empiler(tableau, p, joueurs[i-1].couleur);
            compteur++;
            if (test_tout(tableau, couleur, p)!=-1){
                printf("Le gagnant de cette partie est le joueur %i %s\n", couleur, joueurs[couleur-1].pseudo);
                stop=1;
                break;
            } else if (compteur == (7*6)){
                printf("La partie est finie ");
                stop=1;
                break;
            }
            

        }
        
    }while(stop == 0);
  
    afficher_plateau(tableau);
    return 0;
}
