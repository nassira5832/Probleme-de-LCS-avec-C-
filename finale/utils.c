#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
int min(int a, int b) {
    return (a < b) ? a : b;
}
void genererChaineAleatoire(char *chaine, int longueur) {
    const char caracteres[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < longueur; i++) {
        int cle = rand() % (int)(sizeof(caracteres) - 1);
        chaine[i] = caracteres[cle];
    }
    chaine[longueur] = '\0';
}

void genererSequenceADN(char *chaine, int longueur) {
    const char bases[] = "ACGT";  
    for (int i = 0; i < longueur; i++) {
        chaine[i] = bases[rand() % 4];
    }
    chaine[longueur] = '\0';
}

void genererCodeSource(char *chaine, int longueur) {
    const char *motsCles[] = {
        "if", "else", "while", "for", "return", "int", "void", 
        "printf", "scanf", "main", "include", "define"
    };
    const int nbMotsCles = 12;
    int position = 0;

    while (position < longueur - 10) {  
        const char *motCle = motsCles[rand() % nbMotsCles];
        int longueurMot = strlen(motCle);
        strcpy(chaine + position, motCle);
        position += longueurMot;
        chaine[position++] = " (){};="[rand() % 7];
    }
    chaine[position] = '\0';
}

void calculerComplexite(char *chaine1, char *chaine2, 
                       int (*fonctionLCS)(char*, char*, int, int), 
                       int (*fonctionLCSRecursive)(char*, char*, int, int),
                       int nbTests, int nbChaines, 
                       const char* nomFichier, char *typeSequence) {
    
    char nomFichier1[100];
    char nomFichier2[100];
    char nomFichier3[100];
    strcpy(nomFichier1, nomFichier);
    strcat(nomFichier1, "Recursive.csv");
    strcpy(nomFichier2, nomFichier);
    strcat(nomFichier2, "Matrice.csv");
    strcpy(nomFichier3, nomFichier);
    strcat(nomFichier3, "Optimale.csv");

    FILE *fichier1 = fopen(nomFichier1, "w");
    FILE *fichier2 = fopen(nomFichier2, "w");
    FILE *fichier3 = fopen(nomFichier3, "w");

      if (fichier1 == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    if (fichier2 == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    if (fichier3 == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s\n", nomFichier);
        return;
    }
    fprintf(fichier1, "taille1,taille2,tempsMoyen,TailleMem\n");
    fprintf(fichier2, "taille1,taille2,tempsMoyen,TailleMem\n");
    fprintf(fichier3, "taille1,taille2,tempsMoyen,TailleMem\n");

    for (int s = 1; s <= nbChaines; s++) {
        int taille1 = rand() % (20);   
        int taille2 = rand() % (20);  
        

        if (strcmp(typeSequence, "ADN") == 0) {
            genererSequenceADN(chaine1, taille1);
            genererSequenceADN(chaine2, taille2);
        } else if (strcmp(typeSequence, "CODE") == 0) {
            genererCodeSource(chaine1, taille1);
            genererCodeSource(chaine2, taille2);
        } else {
            genererChaineAleatoire(chaine1, taille1);
            genererChaineAleatoire(chaine2, taille2);
        }

 double tempsTotal = 0.0;
        /*// Recursive algo 1
       
        for(int i = 0; i < nbTests; i++) {
            clock_t debut = clock();
            int longueur = fonctionLCSRecursive(chaine1, chaine2, taille1, taille2);
            clock_t fin = clock();
            
            double temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
            
             printf("Matrice: %f\n", temps);
            tempsTotal += temps;
        }
        double tempsMoyen = tempsTotal / nbTests;
        size_t TailleMem = sizeof(char) * (taille1 + taille2) + sizeof(int) * 2 * min(taille1 , taille2);

        fprintf(fichier1, "%d,%d,%f,%zu\n", taille1, taille2, tempsMoyen, TailleMem); 
      */
        // matrice algo 2
        tempsTotal = 0.0;
        for (int i = 0; i < nbTests; i++) {
            clock_t debut = clock();
            int longueur = fonctionLCS(chaine1, chaine2, taille1, taille2);
            clock_t fin = clock();

            double temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
            tempsTotal += temps;
            printf("Matrice: %f\n", temps);
        }
        double tempsMoyen = tempsTotal / nbTests;
        size_t TailleMem2 = sizeof(char) * (taille2 +  taille1) + sizeof(int) * (taille2 + 1) * (taille1 + 1);
        fprintf(fichier2, "%d,%d,%f\n", taille1, taille2, tempsMoyen,TailleMem2); 
    }
    fclose(fichier1);
    fclose(fichier2);
    fclose(fichier3);

    printf("Données exportées dans le fichier %s\n", nomFichier);
}