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

void genererSequenceADN(int longueur1,int longueur2, char *complexite, char *chaine, char *chaine2) {
    const char bases[] = "ACGT";
    
    if (strcmp(complexite, "grande") == 0) {
        char choix1 = bases[rand() % 4];
        char choix2;
        do {
            choix2 = bases[rand() % 4];
        } while (choix2 == choix1);  
        for (int i = 0; i < longueur1; i++) {
            chaine[i] = choix1;
        }
        for (int i = 0; i < longueur2; i++) {
            chaine2[i] = choix2;
        }
    } else if (strcmp(complexite, "petite") == 0) {
        char choix = bases[rand() % 4];
        
        for (int i = 0; i < longueur1; i++) {
            chaine[i] = choix;
        }
        for (int i = 0; i < longueur2; i++) {
            chaine2[i] = choix;
        }
    }
    
    chaine[longueur1] = '\0';
    chaine2[longueur2] = '\0';
}

void genererCodeSource(int longueur1,int longueur2, char *complexite, char *chaine1, char *chaine2) {
    const char *motsCles[] = {
        "if", "else", "while", "for", "return", "int", "void", 
        "printf", "scanf", "main", "include", "define"
    };
    const int nbMotsCles = 12;
    int position1 = 0, position2 = 0;

    if (strcmp(complexite, "grande") == 0) {
        // Complexité élevée : génère des chaînes avec différents mots clés pour chaque chaîne
        while (position1 < longueur1 - 10 && position2 < longueur2 - 10) {
            const char *motCle1 = motsCles[rand() % nbMotsCles];
            const char *motCle2;
            do {
                motCle2 = motsCles[rand() % nbMotsCles];
            } while (strcmp(motCle1, motCle2) == 0);  // Assure que les mots clés ne soient pas identiques

            int longueurMot1 = strlen(motCle1);
            int longueurMot2 = strlen(motCle2);

            if (position1 + longueurMot1 < longueur1) {
                strcpy(chaine1 + position1, motCle1);
                position1 += longueurMot1;
                chaine1[position1++] = " (){};="[rand() % 7];
            }

            if (position2 + longueurMot2 < longueur2) {
                strcpy(chaine2 + position2, motCle2);
                position2 += longueurMot2;
                chaine2[position2++] = " (){};="[rand() % 7];
            }
        }
    } else if (strcmp(complexite, "petite") == 0) {
        // Complexité faible : utilise le même mot-clé pour les deux chaînes
        const char *motCle = motsCles[rand() % nbMotsCles];
        int longueurMot = strlen(motCle);
        while (position1 < longueur1 - longueurMot && position2 < longueur2 - longueurMot) {
            strcpy(chaine1 + position1, motCle);
            position1 += longueurMot;
            if (position1 < longueur1) {
                chaine1[position1++] = ' ';
            }

            strcpy(chaine2 + position2, motCle);
            position2 += longueurMot;
            if (position2 < longueur2) {
                chaine2[position2++] = ' ';
            }
        }
    }
    
    chaine1[position1] = '\0';
    chaine2[position2] = '\0';
}

void calculerComplexite(char *chaine1, char *chaine2, 
                       int (*fonctionLCS)(char*, char*, int, int), 
                       int (*fonctionLCSRecursive)(char*, char*, int, int),
                       int (*fonctionLCSOptimal)(char*, char*, int, int),
                       int nbTests, int nbChaines, 
                       const char* nomFichier, char *typeSequence , char *complexite) {
    
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
        int taille1 = rand() % (25);   
        int taille2 = rand() % (25);  
        

        if (strcmp(typeSequence, "ADN") == 0) {
            if(complexite=="petite"){
                 genererSequenceADN( taille1, taille2 , "petite", chaine1, chaine2);
            }
            if(complexite=="grande"){
                genererSequenceADN( taille1, taille2 , "grande", chaine1, chaine2);
            }


           
        } else if (strcmp(typeSequence, "CODE") == 0) {
            if(complexite=="petite"){
                 genererSequence( taille1, taille2 , "petite", chaine1, chaine2);
            }
            if(complexite=="grande"){
                genererSequence( taille1, taille2 , "grande", chaine1, chaine2);
            }
           
        } else {
            genererChaineAleatoire(chaine1, taille1);
            genererChaineAleatoire(chaine2, taille2);
        }

 
        // Recursive algo 1
        double tempsTotal = 0.0;
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
        tempsMoyen = tempsTotal / nbTests;
        size_t TailleMem2 = sizeof(char) * (taille2 +  taille1) + sizeof(int) * (taille2 + 1) * (taille1 + 1);
        fprintf(fichier2, "%d,%d,%f,%zu\n", taille1, taille2, tempsMoyen,TailleMem2); 

         tempsTotal = 0.0;
        for (int i = 0; i < nbTests; i++) {
            clock_t debut = clock();
            int longueur = fonctionLCSOptimal(chaine1, chaine2, taille1, taille2);
            clock_t fin = clock();

            double temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
            tempsTotal += temps;
            // printf("Matrice: %f\n", temps);
        }
        tempsMoyen = tempsTotal / nbTests;
        size_t TailleMem3 = sizeof(char) * (taille1 + taille2) + sizeof(int) * (taille2 + 1);
        fprintf(fichier3, "%d,%d,%f,%zu\n", taille1, taille2, tempsMoyen,TailleMem3); 
    }
    fclose(fichier1);
    fclose(fichier2);
    fclose(fichier3);

    printf("Données exportées dans le fichier %s\n", nomFichier);
}