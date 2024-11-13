#include <stdio.h>
#include "utils.c"


int LCSRecursive(char *X, char *Y, int n, int m) {
    if (n == 0 || m == 0) {
        return 0;
    }
    if (X[n - 1] == Y[m - 1]) {
        return 1 + LCSRecursive(X, Y, n - 1, m - 1);
    } else {
       return (LCSRecursive(X, Y, n - 1, m) > LCSRecursive(X, Y, n, m - 1)) 
       ? LCSRecursive(X, Y, n- 1, m) : LCSRecursive(X, Y, n, m - 1);
    }
}


int lcsDP(char *X, char *Y, int m, int n) {
    int table[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                table[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                table[i][j] = table[i - 1][j - 1] + 1;
            else
                table[i][j] = (table[i - 1][j] > table[i][j - 1]) ? table[i - 1][j] : table[i][j - 1];
        }
    }
    return table[m][n];
}

int lcsDPOptimized(char *X, char *Y, int m, int n) {

  int table[n + 1];
    int previous, temp;
    for (int j = 0; j <= n; j++) {
        table[j] = 0;
    }
    for (int i = 1; i <= m; i++) {
        previous = 0;  
        for (int j = 1; j <= n; j++) {
            temp = table[j];  
            if (X[i - 1] == Y[j - 1])
                table[j] = previous + 1;
            else
                table[j] = (table[j] > table[j - 1]) ? table[j] : table[j - 1];
            previous = temp; 
        }
    }

    return table[n];
}

int main() {
    srand(time(0));  
    int numTests = 30;  
    int numStrings = 100; 
    char X[30], Y[30]; 
    const char* filename = "complexite";
    calculerComplexite(X, Y, LCSRecursive,lcsDP,lcsDPOptimized, numTests, numStrings, filename,"PireCas");
    return 0;
}
   