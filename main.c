#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "libcalculadora_CalculadoraAnalisis.h"

JNIEXPORT jdouble JNICALL Java_libcalculadora_CalculadoraAnalisis_interpolarNewton
  (JNIEnv *env, jobject obj, jdoubleArray xArray, jdoubleArray yArray, jdouble xp) {

    int n = (*env)->GetArrayLength(env, xArray);

    // Convertir arrays de Java a C
    jdouble *x = (*env)->GetDoubleArrayElements(env, xArray, NULL);
    jdouble *y0 = (*env)->GetDoubleArrayElements(env, yArray, NULL);

    // Crear tabla de diferencias divididas
    double **y = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        y[i] = (double *)calloc(n, sizeof(double));
        y[i][0] = y0[i];
    }

    // Calcular diferencias divididas
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            y[i][j] = (y[i + 1][j - 1] - y[i][j - 1]) / (x[i + j] - x[i]);
        }
    }

    // Evaluar el polinomio en xp
    double result = y[0][0];
    for (int i = 1; i < n; i++) {
        double term = y[0][i];
        for (int j = 0; j < i; j++) {
            term *= (xp - x[j]);
        }
        result += term;
    }

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(y[i]);
    }
    free(y);
    (*env)->ReleaseDoubleArrayElements(env, xArray, x, 0);
    (*env)->ReleaseDoubleArrayElements(env, yArray, y0, 0);

    return result;
}
