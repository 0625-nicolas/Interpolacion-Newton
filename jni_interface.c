#include <jni.h>
#include "libcalculadora_CalculadoraAnalisis.h"
#include "interpolacion.h"
#include <stdio.h>
#include <stdlib.h>

void calcularDiferenciasDivididas(double *x, double **y, int n) {
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            y[i][j] = (y[i + 1][j - 1] - y[i][j - 1]) / (x[i + j] - x[i]);
        }
    }
}

JNIEXPORT jdouble JNICALL Java_libcalculadora_CalculadoraAnalisis_interpolarNewton(
    JNIEnv *env, jobject obj, jdoubleArray xArray, jdoubleArray yArray, jdouble xp) {
    
    // Validación de entrada
    if (xArray == NULL || yArray == NULL) {
        jclass exception = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        (*env)->ThrowNew(env, exception, "Los arrays de entrada no pueden ser nulos");
        return 0;
    }

    jsize n = (*env)->GetArrayLength(env, xArray);
    
    if (n == 0) {
        jclass exception = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        (*env)->ThrowNew(env, exception, "Los arrays no pueden estar vacíos");
        return 0;
    }

    if (n != (*env)->GetArrayLength(env, yArray)) {
        jclass exception = (*env)->FindClass(env, "java/lang/IllegalArgumentException");
        (*env)->ThrowNew(env, exception, "Los arrays deben tener el mismo tamaño");
        return 0;
    }

    // Convertir arrays
    jdouble *x = (*env)->GetDoubleArrayElements(env, xArray, NULL);
    jdouble *y_values = (*env)->GetDoubleArrayElements(env, yArray, NULL);

    // Reservar memoria con verificación
    double **y = (double **)malloc(n * sizeof(double *));
    if (y == NULL) {
        (*env)->ReleaseDoubleArrayElements(env, xArray, x, 0);
        (*env)->ReleaseDoubleArrayElements(env, yArray, y_values, 0);
        jclass exception = (*env)->FindClass(env, "java/lang/OutOfMemoryError");
        (*env)->ThrowNew(env, exception, "Error al reservar memoria en JNI");
        return 0;
    }

    for (int i = 0; i < n; i++) {
        y[i] = (double *)malloc(n * sizeof(double));
        if (y[i] == NULL) {
            // Liberar memoria ya reservada
            for (int j = 0; j < i; j++) free(y[j]);
            free(y);
            (*env)->ReleaseDoubleArrayElements(env, xArray, x, 0);
            (*env)->ReleaseDoubleArrayElements(env, yArray, y_values, 0);
            jclass exception = (*env)->FindClass(env, "java/lang/OutOfMemoryError");
            (*env)->ThrowNew(env, exception, "Error al reservar memoria en JNI");
            return 0;
        }
        y[i][0] = y_values[i];
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
