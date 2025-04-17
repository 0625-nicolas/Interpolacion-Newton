#include <jni.h>
#include "libcalculadora_CalculadoraAnalisis.h"  // Header generado
#include <stdio.h>
#include <stdlib.h>

// Función para calcular diferencias divididas (igual que tu versión en C)
void calcularDiferenciasDivididas(double *x, double **y, int n) {
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            y[i][j] = (y[i + 1][j - 1] - y[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

// Implementación JNI
JNIEXPORT jdouble JNICALL Java_libcalculadora_CalculadoraAnalisis_interpolarNewton(
    JNIEnv *env, jobject obj, jdoubleArray xArray, jdoubleArray yArray, jdouble xp) {
    
    jsize n = (*env)->GetArrayLength(env, xArray);
    
    // Convertir arrays de Java a C
    jdouble *x = (*env)->GetDoubleArrayElements(env, xArray, NULL);
    jdouble *y_values = (*env)->GetDoubleArrayElements(env, yArray, NULL);
    
    // Crear matriz de diferencias divididas
    double **y = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        y[i] = (double *)malloc(n * sizeof(double));
        y[i][0] = y_values[i];  // Valores iniciales de f(x)
    }
    
    calcularDiferenciasDivididas(x, y, n);
    
    double resultado = y[0][0];
    for (int i = 1; i < n; i++) {
        double term = y[0][i];
        for (int j = 0; j < i; j++) {
            term *= (xp - x[j]);
        }
        resultado += term;
    }
    
    // Liberar memoria
    for (int i = 0; i < n; i++) {
        free(y[i]);
    }
    free(y);
    (*env)->ReleaseDoubleArrayElements(env, xArray, x, 0);
    (*env)->ReleaseDoubleArrayElements(env, yArray, y_values, 0);
    
    return resultado;
}
