#include "interpolacion.h"
#include <stdlib.h>

double interpolar_newton(double *x, double *y, int n, double xp) {
    double **tabla = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        tabla[i] = (double *)calloc(n, sizeof(double));
        tabla[i][0] = y[i];
    }

    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            tabla[i][j] = (tabla[i + 1][j - 1] - tabla[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    double resultado = tabla[0][0];
    for (int i = 1; i < n; i++) {
        double termino = tabla[0][i];
        for (int j = 0; j < i; j++) {
            termino *= (xp - x[j]);
        }
        resultado += termino;
    }

    for (int i = 0; i < n; i++) free(tabla[i]);
    free(tabla);
    return resultado;
}
