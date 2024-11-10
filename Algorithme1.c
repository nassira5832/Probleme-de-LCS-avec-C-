#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int LCSRecursive(char *X, char *Y, int n, int m) {
    if (n == 0 || m == 0) {
        return 0;
    }

    if (X[n - 1] == Y[m - 1]) {
        return 1 + LCSRecursive(X, Y, n - 1, m - 1);
    } else {
        return (LCSRecursive(X, Y, n - 1, m) > LCSRecursive(X, Y, n, m - 1))
            ? LCSRecursive(X, Y, n - 1, m)
            : LCSRecursive(X, Y, n, m - 1);
    }
}

double complexite(int k, double t2, double t1) {
    double time = 0;
    double T;
    for (int i = 1; i <= k; i++) {
        time = time + (t2 - t1) / CLOCKS_PER_SEC;
    }
    T = time / k;
    return T;
}

int main() {
    FILE *file = fopen("lcs_results.csv", "w");
    
    fprintf(file, "taille1,taille2,tempMoy,memUsage\n");

    char *X[] = {"AGGTAB", "AAAGGG", "AGCTAGCTAG", "GATTACA", "TTAGG"};
    char *Y[] = {"GXTXAYB", "AGTAG", "GCTTAGCTA", "TACGAT", "GGAATT"};
    
    int nbrCas = sizeof(X) / sizeof(X[0]);
    int k = 120;

    for (int i = 0; i < nbrCas; i++) {
        int n = strlen(X[i]);
        int m = strlen(Y[i]);

        clock_t debut = clock();
        LCSRecursive(X[i], Y[i], n, m);
        clock_t fin = clock();

        double tmpMoy = complexite(k, fin, debut);

        size_t memUsage = sizeof(char) * (n + m) + sizeof(int) * 3; 

        fprintf(file, "%d,%d,%f,%zu\n", n, m, tmpMoy, memUsage);
    }

    fclose(file);
    return 0;
}
