#include "puissance4.h"



void afficher_plateau(int tableau[LIGNES][COLONNES]) {
    for (int i = 0; i < LIGNES; i++) {
        for (int j = 0; j < COLONNES; j++) {
            printf("| ");
            if (tableau[i][j] == CROIX) {
                printf("X ");
            } else if (tableau[i][j] == ROND) {
                printf("O ");
            } else {
                printf("  "); 
            }
        }
        printf("|\n");
    }
    
    for (int j = 0; j < 4*COLONNES+1; j++) {
        printf("-");
    }
    printf("\n");
}


int combien_dans_colonne(int tableau[LIGNES][COLONNES],int colonne)
{
  colonne--;
  int c=0;
  int i=LIGNES - 1;
  while (tableau[i][colonne]!=0){
      c++;
      i--;
  }
  return c;
}

void empiler(int tableau[LIGNES][COLONNES],int colonne, int couleur)
{
  
  int k=combien_dans_colonne(tableau, colonne);
  colonne--;
  if (k!=LIGNES){
    tableau[LIGNES-(k+1)][colonne]=couleur;
  }else {
    printf("%s\n","YOU CAN'T!!");
  }
}

int combien_dans_direction(int tableau[LIGNES][COLONNES], int couleur,
 int colonne, int delta_i,int delta_j)
{
  
  if (colonne<=0 || colonne>COLONNES){
    return 0;
  }
  colonne--;
  //trouver l'indice du dernier pion empilé
  int i=LIGNES-1;
  while (i>=0 && i<LIGNES && tableau[i][colonne] != 0){
    
    
    i--;
  }
  i++;

  int compteur=0;
  if (tableau[i][colonne] == couleur){
    compteur = 1;
    while ((i+delta_i>=0 && i+delta_i<LIGNES) && 
    (colonne+delta_j>=0 && colonne+delta_j<COLONNES) && 
    tableau[i+delta_i][colonne+delta_j] == couleur){
    
      compteur++;
      i+=delta_i;
      colonne+=delta_j;

  }
  }
  
  return compteur;
}

int test_lignes(int tableau[LIGNES][COLONNES], int couleur,int colonne)
{
for (int i =0; i<LIGNES; i++)
{
  for (int j =0; j<COLONNES; j++)
{
  if (tableau[i][j] != 0){
    if (combien_dans_direction(tableau, couleur, colonne, 0, 1)>=4){
      return couleur;
    }else if (combien_dans_direction(tableau, couleur, colonne, 0, -1)>=4){
      return couleur;
    }else{
      return 0;
    }
  }
}
}
}

int test_colonnes(int tableau[LIGNES][COLONNES], int couleur,int colonne)
{
  for (int i =0; i<LIGNES; i++)
{
  for (int j =0; j<COLONNES; j++)
{
  if (tableau[i][j] != 0){
    if (combien_dans_direction(tableau, couleur, colonne, 1, 0)>=4){
      return couleur;
    }else if (combien_dans_direction(tableau, couleur, colonne, -1, 0)>=4){
      return couleur;
    }else{
      return 0;
    }
  }
}
}
}

int test_diagonales(int tableau[LIGNES][COLONNES], int couleur,int colonne)
{
    for (int i =0; i<LIGNES; i++)
{
  for (int j =0; j<COLONNES; j++)
{
  if (tableau[i][j] != 0){
    if (combien_dans_direction(tableau, couleur, colonne, 1, 1)>=4){
      return couleur;
    }else if (combien_dans_direction(tableau, couleur, colonne, -1, 1)>=4){
      return couleur;
    }else if (combien_dans_direction(tableau, couleur, colonne, -1, -1)>=4){
      return couleur;
    }else if (combien_dans_direction(tableau, couleur, colonne, 1, -1)>=4){
      return couleur;
    }else{
      return 0;
    }
  }
}
}
}

int test_tout(int tableau[LIGNES][COLONNES], int couleur,int colonne)
{
  if (test_lignes(tableau, couleur, colonne)!=0 ||
   test_colonnes(tableau, couleur, colonne)!=0 || 
   test_diagonales(tableau, couleur, colonne)!=0 ){
    return couleur;
  }else{
    return -1;
  }
  

}