package aplicacion;

import libcalculadora.CalculadoraAnalisis;

public class Aplicacion {
    public static void main(String[] args) {
        CalculadoraAnalisis ca = new CalculadoraAnalisis();

        double[] x = {1, 2, 3};
        double[] y = {1, 4, 9};
        double valorInterpolar = 2.5;

        double resultado = ca.interpolarNewton(x, y, valorInterpolar);
        System.out.println("Interpolación de Newton en x = " + valorInterpolar + ": " + resultado);
    }
}

