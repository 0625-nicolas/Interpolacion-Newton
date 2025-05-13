package aplicacion;

import libcalculadora.CalculadoraAnalisis;
import java.util.Scanner;

public class Aplicacion {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        CalculadoraAnalisis calc = new CalculadoraAnalisis();

        System.out.print("Ingrese el número de puntos: ");
        int n = scanner.nextInt();

        double[] x = new double[n];
        double[] y = new double[n];

        System.out.println("Ingrese los valores de x:");
        for (int i = 0; i < n; i++) {
            System.out.print("x[" + i + "] = ");
            x[i] = scanner.nextDouble();
        }

        System.out.println("Ingrese los valores de f(x):");
        for (int i = 0; i < n; i++) {
            System.out.print("f(x[" + i + "]) = ");
            y[i] = scanner.nextDouble();
        }

        System.out.print("Ingrese el valor a interpolar (xp): ");
        double xp = scanner.nextDouble();

        try {
            double resultado = calc.interpolar(x, y, xp);
            System.out.println("Resultado de la interpolación: " + resultado);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
