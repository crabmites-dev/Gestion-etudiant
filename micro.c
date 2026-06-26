#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ETUDIANTS 100
#define MAX_MATIERES 50
#define MAX_NOTES 500
#define FICHIER_ETUDIANTS "etudiants.txt"
#define FICHIER_MATIERES "matieres.txt"
#define FICHIER_NOTES "notes.txt"

typedef struct {
    char matricule[20];
    char nom[50], prenom[50], classe[20];
} Etudiant;

typedef struct {
    char code[10], libelle[50];
    int coefficient;
} Matiere;

typedef struct {
    char matricule[20];
    char codeMatiere[10];
    float valeur;
    char dateEval[11];
} Note;

Etudiant baseEtudiants[MAX_ETUDIANTS]; int nbEtudiants = 0;
Matiere baseMatieres[MAX_MATIERES]; int nbMatieres = 0;
Note baseNotes[MAX_NOTES]; int nbNotes = 0;


int saisirEntier() {
    char buffer[100];
    int valeur, i, valide;
    do {
        valide = 1;
        scanf("%s", buffer);
        // fgets();
        for (i = 0; i < strlen(buffer); i++) {
            if (!isdigit(buffer[i])) {
                valide = 0;
                break;
            }
        }
        if (!valide) printf("Erreur : Veuillez saisir un nombre entier : ");
    } while (!valide);
    valeur = atoi(buffer);
    return valeur;
}

float saisirFlottant() {
    char buffer[100];
    char *endptr;
    float valeur;
    while (1) {
        scanf("%s", buffer);
        valeur = strtof(buffer, &endptr);
        if (*endptr == '\0') 
        return valeur;
        printf("Erreur : Veuillez saisir un nombre : ");
    }
}

void saisirTexte(char *dest, int taille) {
    int valide, i;
    getchar(); 
    do {
        valide = 1;
        fgets(dest, taille, stdin);
        dest[strcspn(dest, "\n")] = 0;
        
        if (strlen(dest) == 0) { valide = 0; }
        for (i = 0; i < strlen(dest); i++) {
            if (isdigit(dest[i])) { 
                valide = 0;
                break;
            }
        }
        if (!valide) printf("Erreur : Veillez saisir des lettres. \n Reessaysez : ");
    } while (!valide);
}

void saisirAlphanumerique(char *chaine, int taille) {
    int valide;
    do {
        valide = 1;
        fgets(chaine, taille, stdin);
        chaine[strcspn(chaine, "\n")] = 0; 

        for (int i = 0; i < strlen(chaine); i++) {
            if (!isalnum(chaine[i])) { 
                printf("Erreur : Utilisez uniquement des lettres et chiffres.\nReessayez : ");
                valide = 0;
                break;
            }
        }
    } while (!valide);
}

void chargerTout();
void sauvegarderTout();

void menuEtudiants();
void ajouterEtudiant();
void modifierEtudiant();
void supprimerEtudiant();
void rechercherEtudiant();
void afficherEtudiants();

void menuMatieres();
void ajouterMatiere();
void afficherMatieres();
void supprimerMatiere();

void menuNotes();
void attribuerNote();
void afficherBulletin();

int main() {
    chargerTout();
    int choix;
    do {
        printf("\n=================================");
        printf("\n   LOGICIEL DE GESTION SCOLAIRE");
        printf("\n=================================");
        printf("\n1. Gestion des Etudiants");
        printf("\n2. Gestion des Matieres");
        printf("\n3. Gestion des Notes");
        printf("\n4. Quitter");
        printf("\nVotre choix : ");        
        choix = saisirEntier();
        switch(choix) { 
            case 1: menuEtudiants(); break;
            case 2: menuMatieres(); break;
            case 3: menuNotes(); break;
        } if (choix != 1, 2, 3, 4) {
            printf("\nErreur : Choix invalide\n");
        }
    } while (choix != 4);
    sauvegarderTout();
    return 0;
}

void menuEtudiants() {
    int choix;
    do {
        printf("\n--- GESTION DES ETUDIANTS ---");
        printf("\n1. Ajouter un etudiant");
        printf("\n2. Modifier un etudiant");
        printf("\n3. Supprimer un etudiant");
        printf("\n4. Rechercher un etudiant");
        printf("\n5. Afficher la liste complete");
        printf("\n6. Retour au menu principal");
        printf("\nChoix : ");        
        choix = saisirEntier();
         switch(choix) {
            case 1: ajouterEtudiant(); break;
            case 2: modifierEtudiant(); break;
            case 3: supprimerEtudiant(); break;
            case 4: rechercherEtudiant(); break;
            case 5: afficherEtudiants(); break;
        } 
    } while (choix != 6);
    if(choix != 1, 2, 3, 4, 5, 6) {
            printf("\nChoix invalide");
        }
}

void ajouterEtudiant() {
    printf("\n-- Ajouter etudiant --\n");
    if (nbEtudiants >= MAX_ETUDIANTS) 
    return;
    getchar();
    printf("\nMatricule : "); saisirAlphanumerique(baseEtudiants[nbEtudiants].matricule, 20);
    printf("Nom : "); saisirTexte(baseEtudiants[nbEtudiants].nom, 50);
    printf("Prenom : "); saisirTexte(baseEtudiants[nbEtudiants].prenom, 50);
    printf("Classe : "); fflush(stdin); saisirAlphanumerique(baseEtudiants[nbEtudiants].classe, 20);

    nbEtudiants++; 
    sauvegarderTout();
    printf("\nEtudiant ajoute avec succes !\n");
}

void modifierEtudiant() {
    printf("\n-- Modifier etudiant --\n");
    char id[20], trouve = 0;
    fflush(stdin);
    printf("\nMatricule de l'etudiant : ");
    saisirAlphanumerique(id, 20);

    for (int i = 0; i < nbEtudiants; i++) {
        if (strcmp(baseEtudiants[i].matricule, id) == 0) {
            trouve = 1;
            int choixModif;
            char s[50];

            do {
                printf("\nQue voulez-vous modifier ?");
                printf("\n1. Le Nom");
                printf("\n2. Le Prenom");
                printf("\n3. La Classe");
                printf("\n4. Terminer la modification");
                printf("\nChoix : ");
                choixModif = saisirEntier();

                if (choixModif == 1) {
                    printf("Nouveau Nom : ");
                    saisirTexte(baseEtudiants[i].nom, 50);
                } else if (choixModif == 2) {
                    printf("Nouveau Prenom : ");
                    saisirTexte(baseEtudiants[i].prenom, 50);
                } else if (choixModif == 3) {
                    printf("Nouvelle Classe  : ");
                    scanf("%s",s, baseEtudiants[i].classe); 
                }
            } while (choixModif != 4);
            
            break; 
        }
    }

    if (!trouve) {
        printf("Etudiant non reconnu.\n");
    } else {
        sauvegarderTout();
        printf("\nEtudiant modifie avec succes !\n");
    }
}

void supprimerEtudiant() {
    printf("\n-- Supprimer etudiant --\n");
    char id[20], index = -1;
    fflush(stdin);
    printf("Matricule de l'etudiant : "); 
    saisirAlphanumerique(id, 20);
    for (int i = 0; i < nbEtudiants; i++) 
    if (strcmp(baseEtudiants[i].matricule, id) == 0) { 
        index = i; 
        break;
    }
    if (index != -1) {
        for (int i = index; i < nbEtudiants - 1; i++) baseEtudiants[i] = baseEtudiants[i + 1];
        nbEtudiants--; 
        sauvegarderTout();
        printf("\nEtudiant supprime avec succes !\n");
    } else {
        printf("Etudiant non reconnu.\n");
    }
}

void rechercherEtudiant() {
    printf("\n-- Rechercher etudiant --\n");
    char id[20]; 
    fflush(stdin);
    printf("Matricule de l'etudiant : "); 
    saisirAlphanumerique(id, 20);
    for (int i = 0; i < nbEtudiants; i++) if (strcmp(baseEtudiants[i].matricule, id) == 0) {
        printf("\n--- RESULTAT ---");
        printf("\nNom: %s | Prenom: %s | Classe: %s\n", baseEtudiants[i].nom, baseEtudiants[i].prenom, baseEtudiants[i].classe);
        return;
    }
    printf("Etudiant non reconnu.\n");
}

void afficherEtudiants() {
    if (nbEtudiants == 0) { 
        printf("\nAucun etudiant enregistre.\n"); 
        return; 
    }
    printf("\n--- LISTE DES ETUDIANTS ---");
    for (int i = 0; i < nbEtudiants; i++) {
        printf("\n----------------------------");
        printf("\nMatricule : %s", baseEtudiants[i].matricule);
        printf("\nNom       : %s", baseEtudiants[i].nom);
        printf("\nPrenom    : %s", baseEtudiants[i].prenom);
        printf("\nClasse    : %s", baseEtudiants[i].classe);
    }
    printf("\n");
}

void menuMatieres() {
    int c; do {
        printf("\n--- GESTION DES MATIERES ---");
        printf("\n1. Ajouter une matiere");
        printf("\n2. Afficher toutes les matieres");
        printf("\n3. Supprimer une matiere");
        printf("\n4. Retour");
        printf("\nChoix : ");
        c = saisirEntier();
        if(c==1) {
            printf("\n-- Ajouter matiere --\n");
            printf("Code : "); scanf("%s", baseMatieres[nbMatieres].code);
            printf("Libelle : "); saisirTexte(baseMatieres[nbMatieres].libelle, 50);
            printf("Coefficient : "); baseMatieres[nbMatieres].coefficient = saisirEntier();
            nbMatieres++; 
            sauvegarderTout();
            printf("\nMatiere ajoute avec succes !\n");
        } else if (c == 2) {
        if (nbMatieres == 0) {
            printf("\nAucune matiere enregistree.\n");
        } else {
            printf("\n--- LISTE DES MATIERES ---");
            for (int i = 0; i < nbMatieres; i++) {
                printf("\n----------------------------");
                printf("\nCode         => %s", baseMatieres[i].code);
                printf("\nLibelle      => %s", baseMatieres[i].libelle);
                printf("\nCoefficient  => %d", baseMatieres[i].coefficient);
                printf("\n----------------------------");
            }
        }
    } else if (c == 3) {
        char code[10];
        int index = -1;
        printf("Code de la matiere a supprimer : ");
        scanf("%s", code);
        for (int i = 0; i < nbMatieres; i++) {
            if (strcmp(baseMatieres[i].code, code) == 0) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            for (int i = index; i < nbMatieres - 1; i++) {
                baseMatieres[i] = baseMatieres[i + 1];
            }
            nbMatieres--;
            sauvegarderTout();
            printf("\nMatiere supprimee avec succes !\n");
        } else {
            printf("\nCode non reconnu.\n");
        }
    }
    } while (c != 4);
}

void menuNotes() {
    int c; 
    do {
        printf("\n--- GESTION DES NOTES ---");
        printf("\n1. Attribuer une note");
        printf("\n2. Voir bulletin d'un etudiant");
        printf("\n3. Retour");
        printf("\nChoix : ");
        c = saisirEntier();

        if (c == 1) {
            char mat[20], trouve = 0; 
            printf("Matricule de l'etudiant : ");
            getchar();
            saisirAlphanumerique(mat, 20);

            for (int i = 0; i < nbEtudiants; i++) {
                if (strcmp(baseEtudiants[i].matricule, mat) == 0) {
                    trouve = 1;
                    break;
                }
            }
            if (trouve) {
                strcpy(baseNotes[nbNotes].matricule, mat); 
                printf("Code Matiere : ");
                scanf("%s", baseNotes[nbNotes].codeMatiere);
                printf("Note : ");
                baseNotes[nbNotes].valeur = saisirFlottant();
                printf("Date d'evaluation : ");
                scanf("%s", baseNotes[nbNotes].dateEval);
                nbNotes++;
                sauvegarderTout();
                printf("\nNote ajoutee avec succes !\n");
            } else {
                printf("\nEtudiant non reconnu.\n");
            }

        } else if (c == 2) {
            char mat[20];
            float s = 0;
            int tc = 0;
            int trouveEtudiant = 0;

            printf("Matricule de l'etudiant : ");
            fflush(stdin); 
            saisirAlphanumerique(mat, 20);

            printf("\n============================================================");
            printf("\n            BULLETIN DE NOTES : %s", mat);
            printf("\n============================================================");
            printf("\n%-15s | %-10s | %-6s | %-12s", "MATIERE", "NOTE", "COEFF", "DATE");
            printf("\n------------------------------------------------------------");

            for (int i = 0; i < nbNotes; i++) {
                if (strcmp(baseNotes[i].matricule, mat) == 0) {
                    trouveEtudiant = 1;
                    int k = 1; 

                    for (int j = 0; j < nbMatieres; j++) {
                        if (strcmp(baseMatieres[j].libelle, baseNotes[i].codeMatiere) == 0) {
                            k = baseMatieres[j].coefficient;
                            break;
                        }
                    }

                    printf("\n%-15s | %-10.2f | %-6d | %-12s", baseNotes[i].codeMatiere, baseNotes[i].valeur, k, baseNotes[i].dateEval); 
                    s += (baseNotes[i].valeur * k);
                    tc += k;
                }
            }

            if (tc > 0) {
                printf("\n------------------------------------------------------------");
                printf("\nMOYENNE GENERALE : %.2f / 20", s / tc);
                printf("\n============================================================\n");
            } else if (trouveEtudiant == 0) {
                printf("\n\nAucune note trouvee pour ce matricule.\n");
            }
        }

            } while (c != 3); 
}

void sauvegarderTout() {
    FILE *f1 = fopen(FICHIER_ETUDIANTS, "w");
    if(f1){ for(int i=0; i<nbEtudiants; i++) fprintf(f1, "%s;%s;%s;%s\n", baseEtudiants[i].matricule, baseEtudiants[i].nom, baseEtudiants[i].prenom, baseEtudiants[i].classe); fclose(f1); }
    FILE *f2 = fopen(FICHIER_MATIERES, "w");
    if(f2){ for(int i=0; i<nbMatieres; i++) fprintf(f2, "%s;%s;%d\n", baseMatieres[i].code, baseMatieres[i].libelle, baseMatieres[i].coefficient); fclose(f2); }
    FILE *f3 = fopen(FICHIER_NOTES, "w");
    if(f3){ for(int i=0; i<nbNotes; i++) fprintf(f3, "%s;%s;%.2f\n", baseNotes[i].matricule, baseNotes[i].codeMatiere, baseNotes[i].valeur); fclose(f3); }
}

void chargerTout() {
    FILE *f1 = fopen(FICHIER_ETUDIANTS, "r");
    if(f1){ 
        while(fscanf(f1, " %19[^;];%49[^;];%49[^;];%19[^\n]\n", 
      baseEtudiants[nbEtudiants].matricule, 
      baseEtudiants[nbEtudiants].nom, 
      baseEtudiants[nbEtudiants].prenom, 
      baseEtudiants[nbEtudiants].classe) == 4) 
    {
    nbEtudiants++; 
     }
        fclose(f1); 
    }
    FILE *f2 = fopen(FICHIER_MATIERES, "r");    if(f2){ while(fscanf(f2, "%9[^;];%49[^;];%d\n", baseMatieres[nbMatieres].code, baseMatieres[nbMatieres].libelle, &baseMatieres[nbMatieres].coefficient) == 3) nbMatieres++; fclose(f2); }
    FILE *f3 = fopen(FICHIER_NOTES, "r");
    if(f3){ 
        while(fscanf(f3, "%19[^;];%9[^;];%f;%10[^\n]\n", 
              baseNotes[nbNotes].matricule, 
              baseNotes[nbNotes].codeMatiere, 
              &baseNotes[nbNotes].valeur, 
              baseNotes[nbNotes].dateEval) == 4) nbNotes++; 
        fclose(f3); 
    }
}


