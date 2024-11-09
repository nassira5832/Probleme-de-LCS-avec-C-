#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
int LCSRecursive(char *X, char *Y, int n, int m, char *LCSResult, int index) {
    if (n == 0 || m == 0) {
        LCSResult[index] = '\0'; 
        return 0;
    }

    if (X[n - 1] == Y[m - 1]) {
        LCSResult[index] = X[n - 1];
        return 1 + LCSRecursive(X, Y, n - 1, m - 1, LCSResult, index + 1);
    } else {

        
       return (LCSRecursive(X, Y, n - 1, m, LCSResult, index) > LCSRecursive(X, Y, n, m - 1, LCSResult, index)) 
       ? LCSRecursive(X, Y, n- 1, m, LCSResult, index) : LCSRecursive(X, Y, n, m - 1, LCSResult, index);
    }
}

void printLCS(char *X, char *Y) {
    int n = strlen(X);
    int m = strlen(Y);
    char LCSResult[n + 1]; 
    LCSResult[0] = '\0'; 
    int length = LCSRecursive(X, Y, n, m, LCSResult, 0);
    printf("Longueur de la LCS: %d\n", length);
    printf("LCS: %s\n", LCSResult);
}

int main() {
    char X[] = "AGGTAB";
    char Y[] = "GXTXAYB";
    printLCS(X, Y);

    return 0;
}


