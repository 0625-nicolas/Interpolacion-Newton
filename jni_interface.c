#include <jni.h>
#include "interpolacion.h"
#include "libcalculadora_CalculadoraAnalisis.h"  // Generado después

JNIEXPORT jdouble JNICALL Java_libcalculadora_CalculadoraAnalisis_interpolarNewton(
    JNIEnv *env, jobject obj, jdoubleArray xArray, jdoubleArray yArray, jdouble xp) {

    jsize n = (*env)->GetArrayLength(env, xArray);
    jdouble *x = (*env)->GetDoubleArrayElements(env, xArray, NULL);
    jdouble *y = (*env)->GetDoubleArrayElements(env, yArray, NULL);

    double resultado = interpolar_newton(x, y, n, xp);

    (*env)->ReleaseDoubleArrayElements(env, xArray, x, 0);
    (*env)->ReleaseDoubleArrayElements(env, yArray, y, 0);
    return resultado;
}
