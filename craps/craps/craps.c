#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int lancerDes(void) {
    return rand() % 6 + 1; // Génère un nombre entre 1 et 6 (inclus)
}

int placerMise(int solde) {
    int mise;
    printf("\nVotre solde actuel est de %d$. Placez votre mise : ", solde);
    scanf("%d", &mise);

    if (mise > solde || mise <= 0) {
        printf("Mise invalide. Veuillez saisir une mise valide.\n");
        return placerMise(solde); // Appel récursif pour obtenir une mise valide
    }

    return mise;
}

void demarrerPartie(int* solde) {
    int point = 0;
    char choix;

    int mise = placerMise(*solde);

    printf("\nAppuyez sur 'L' pour lancer les dés : ");
    scanf(" %c", &choix);

    if (choix == 'L' || choix == 'l') {
        int de1 = lancerDes();
        int de2 = lancerDes();
        int sommeDes = de1 + de2;

        printf("\nVous avez lancé : %d + %d = %d\n", de1, de2, sommeDes);

        if (point == 0) {
            if (sommeDes == 7 || sommeDes == 11) {
                printf("Vous avez gagné!\n");
                *solde = *solde + mise;
            } else if (sommeDes == 2 || sommeDes == 3 || sommeDes == 12) {
                printf("Vous avez perdu.\n");
                *solde = *solde - mise;
            } else {
                point = sommeDes;
                printf("Point établi à %d.\n", point);
            }
        } else {
            if (sommeDes == point) {
                printf("Vous avez gagné!\n");
                *solde = *solde + mise;
                point = 0;
            } else if (sommeDes == 7) {
                printf("Vous avez perdu.\n");
                *solde = *solde - mise;
                point = 0;
            }
        }

        printf("Votre solde actuel est de %d$.\n", *solde);

        if (*solde <= 0) {
            printf("\nVous n'avez plus d'argent. Le jeu est terminé.\n");
        }
    }
}

void menu() {
    int solde = 1000; // Solde initial du joueur

    printf("Bienvenue au jeu de Craps!\n");

    int continuer = 1; // Variable pour contrôler si le jeu continue

    while (continuer) {
        if (solde <= 0) {
            printf("\nVous n'avez plus d'argent. Le jeu est terminé.\n");
            break;
        }

        printf("\nMenu :\n");
        printf("1. Démarrer une partie\n");
        printf("2. Quitter\n");
        printf("Votre choix : ");
        int menuChoice;
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1: // Démarrer une partie
                demarrerPartie(&solde);
                break;
            case 2: // Quitter
                printf("Au revoir !\n");
                continuer = 0; // Sortir de la boucle
                break;
            default:
                printf("Option invalide. Veuillez choisir à nouveau.\n");
                break;
        }
    }
}

int main(void) {
    menu();
    return 0;
}
