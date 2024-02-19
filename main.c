#include<stdio.h>
#include<stdlib.h>

struct noeud{
    int* plateau;
    int score;
    int nb_liste;
    struct noeud** liste;
};

typedef struct noeud noeud;
typedef struct noeud * arbre;


int* remplir_plateau(int* table, int taille){
    int nb = 42;
    int i = 0;
    
    while (nb != 0){
        int n = rand() % 2;
        table[i % taille] += n;
        nb -= n;
        i++;
    }
    return table;
}

/*
  13 12 11 10 9  8      joueur 1
 0                 7
  1  2  3  4  5  6      joueur 0
*/


void affiche_plateau(int* table){
    printf("   ");
    for (int i = 13; i != 7; i--){
        printf("%d ", table[i]);
    }
    printf("\n %d             %d", table[0], table[7]);
    printf("\n   ");
    for (int i = 1; i != 7; i++){
        printf("%d ", table[i]);
    }
    printf("\n");
}

int find_indice(int nb){
    for (int i = 0; i != 14; i++){
        if (i + nb == 14){
            return i;
        }
    }
    return 0;
}

void tour(int* table, int joueur, int index){
    int* plateau_depart = table;
    int case_depart = index;
    int nb = table[index];
    table[index] = 0;
    while (nb != 0){
        index = (index + 1) % 14;
        if (((joueur == 0  && index != 0) || (joueur == 1 && index != 7)) && index != case_depart){
            table[index] += 1;
            nb--;
        }
    }
    index = (index + 1) % 14;

    if (joueur == 0 && (index <= 6 && index > 0)){
        table[7] += table[find_indice(index)];
    }
    if (joueur == 1 && (index <= 13 && index > 7)){
        table[0] += table[14 - index];
    }
    
    while (joueur == 1 && (index <= 6 && index > 0) && (table[index] == 2 || table[index] == 3)){
        table[0] += table[index];
        table[index] = 0;
        if (index != 0){
            index --;
        }
        else{
            index = 13;
        }
    }
    while (joueur == 0 && (index <= 13 && index > 7) && (table[index] == 2 || table[index] == 3)){
        table[7] += table[index];
        table[index] = 0;
        if (index != 0){
            index --;
        }
        else{
            index = 13;
        }
    }
    if ((table[1] == 0 && table[2] == 0 && table[3] == 0 && table[4] == 0 && table[5] == 0 && table[6] == 0) || (table[8] == 0 && table[9] == 0 && table[10] == 0 && table[11] == 0 && table[12] == 0 && table[13] == 0)){
        table = plateau_depart;
    }
    
    
    
}

int verif_fin(int* table){
    if (table[0] > 25 || table[7] > 25){
        return 1;
    }
    int* plateau_temp = table;
    int nb = 0;
    affiche_plateau(plateau_temp);
    while (plateau_temp[1] == 0 && plateau_temp[2] == 0 && plateau_temp[3] == 0 && plateau_temp[4] == 0 && plateau_temp[5] == 0 && plateau_temp[6] == 0){
        plateau_temp = table;
        if (nb == 7){
            for (int i = 8; i != 14; i++){
                table[0] += table[i];
                table[i] = 0;
            }
            return 1;
        }
        tour(plateau_temp, 1, nb);
        nb++;
    }

    nb = 0;
    while (plateau_temp[8] == 0 && plateau_temp[9] == 0 && plateau_temp[10] == 0 && plateau_temp[11] == 0 && plateau_temp[12] == 0 && plateau_temp[13] == 0){
        plateau_temp = table;
        if (nb == 14){
            for (int i = 1; i != 7; i++){
                table[7] += table[i];
                table[i] = 0;
            }
            return 1;
        }
        tour(plateau_temp, 0, nb);
        nb++;
    }
    return 0;
}


void main(){


    int table[14] =   {0, 0, 0, 0, 0, 0, 0,
                       0, 0, 0, 0, 0, 1, 0};

    noeud* plateau = (arbre) malloc (sizeof (noeud));
    
    //int table[14] = {0, 4, 4, 4, 4, 4, 4,
    //                 0, 4, 4, 4, 4, 4, 4};


    //remplir_plateau(table, taille);

    affiche_plateau(table);
    printf("\n");
    /*

    for (int j = 0; j != 20; j++){
        printf("tour N:%d\n", j);
        if (j%2){
            tour(table, 1, 2*(rand()%6 +1));
        }
        else{
            tour(table, 0, (rand()%6)+1);
        }
        affiche_plateau(table);
        printf("\n");
    }
    */
    tour(table, 1, 12);
    affiche_plateau(table);
    printf("%d", verif_fin(table));
    affiche_plateau(table);

    /*
    tour(table, 1, 12);
    affiche_plateau(table);

    tour(table, 0, 5);
    affiche_plateau(table);

    tour(table, 1, 11);
    affiche_plateau(table);

    tour(table, 0, 3);
    affiche_plateau(table);

    tour(table, 1, 10);
    affiche_plateau(table);

    tour(table, 0, 2);
    affiche_plateau(table);

    tour(table, 1, 12);
    affiche_plateau(table);
    
    tour(table, 0, 1);
    affiche_plateau(table);

    tour(table, 1, 13);
    affiche_plateau(table);

    tour(table, 0, 5);
    affiche_plateau(table);
    */

    return;

}