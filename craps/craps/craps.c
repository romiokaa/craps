#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure pour le joueur
struct Joueur {
    int solde;
};

// Structure pour la partie
struct Partie {
    int point;
};

int lancerDes(void) {
    return rand() % 6 + 1; // Génère un nombre entre 1 et 6 (inclus)
}

int placerMise(struct Joueur* joueur) {
    int mise;
    printf("\nVotre solde actuel est de %d$. Placez votre mise : ", joueur->solde);
    scanf("%d", &mise);

    if (mise > joueur->solde || mise <= 0) {
        printf("Mise invalide. Veuillez saisir une mise valide.\n");
        return placerMise(joueur);
    }

    return mise;
}

void demarrerPartie(struct Joueur* joueur, struct Partie* partie) {
    char choix;

    int mise = placerMise(joueur);

    printf("\nAppuyez sur 'L' pour lancer les dés : ");
    scanf(" %c", &choix);

    if (choix == 'L' || choix == 'l') {
        int de1 = lancerDes();
        int de2 = lancerDes();
        int sommeDes = de1 + de2;

        printf("\nVous avez lancé : %d + %d = %d\n", de1, de2, sommeDes);

        if (partie->point == 0) {
            if (sommeDes == 7 || sommeDes == 11) {
                printf("Vous avez gagné!\n");
                joueur->solde += mise;
            } else if (sommeDes == 2 || sommeDes == 3 || sommeDes == 12) {
                printf("Vous avez perdu.\n");
                joueur->solde -= mise;
            } else {
                partie->point = sommeDes;
                printf("Point établi à %d.\n", partie->point);
            }
        } else {
            if (sommeDes == partie->point) {
                printf("Vous avez gagné!\n");
                joueur->solde += mise;
                partie->point = 0;
            } else if (sommeDes == 7) {
                printf("Vous avez perdu.\n");
                joueur->solde -= mise;
                partie->point = 0;
            }
        }

        printf("Votre solde actuel est de %d$.\n", joueur->solde);

        if (joueur->solde <= 0) {
            printf("\nVous n'avez plus d'argent. Le jeu est terminé.\n");
        }
    }
}

void menu(struct Joueur* joueur) {
    struct Partie partie = {0}; // Initialisation de la partie avec un point de 0

    printf("Bienvenue au jeu de Craps!\n");

    int continuer = 1;

    while (continuer) {
        if (joueur->solde <= 0) {
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
            case 1:
                demarrerPartie(joueur, &partie);
                break;
            case 2:
                printf("Au revoir !\n");
                continuer = 0;
                break;
            default:
                printf("Option invalide. Veuillez choisir à nouveau.\n");
                break;
        }
    }
}

int main(void) {
    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires
    struct Joueur joueur = {1000}; // Initialiser le joueur avec 1000$
    menu(&joueur);
    return 0;
}
