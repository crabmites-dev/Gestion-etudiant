# 🏫 Logiciel de Gestion Scolaire

Une application robuste développée en **Langage C** permettant de gérer efficacement les dossiers académiques des étudiants, l'administration des matières et le calcul automatisé des bulletins de notes.

---

## 🚀 Fonctionnalités Principales

* **Gestion des Étudiants :** Ajout, modification, suppression et recherche d'élèves via un matricule alphanumérique unique.
* **Gestion des Matières :** Configuration des modules d'enseignement avec coefficients personnalisés.
* **Calcul des Bulletins :** Saisie des notes d'évaluation et génération automatique de la moyenne générale pondérée.
* **Persistance des Données :** Sauvegarde et chargement automatique des fichiers textes (`etudiants.txt`, `matieres.txt`, `notes.txt`).

---

## 📊 Organisation de la Base de Données (Fichiers Textes)

Voici comment les données sont structurées et comparées au sein de l'application :

| Entité | Fichier de Stockage | Attributs Clés | Type de Clé |
| :--- | :--- | :--- | :--- |
| **Étudiant** | `etudiants.txt` | Matricule, Nom, Prénom, Classe | Alphanumérique |
| **Matière** | `matieres.txt` | Code, Libellé, Coefficient | Alphanumérique / Entier |
| **Note** | `notes.txt` | Matricule, CodeMatiere, Valeur, Date | Mixte |

---

## 💻 Aperçu du Code Source (Architecture C)

L'application s'appuie sur des structures de données dynamiques et des fonctions de filtrage strictes pour sécuriser les saisies utilisateur :

```c
typedef struct {
    char matricule[20];
    char nom[50], prenom[50], classe[20];
} Etudiant;

// Fonction de filtrage alphanumérique pour les matricules
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