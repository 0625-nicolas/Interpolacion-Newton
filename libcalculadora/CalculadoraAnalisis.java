package libcalculadora;

public class CalculadoraAnalisis {
    
    static {
        System.loadLibrary("calcanalisis");
    }
    
    public native double interpolarNewton(double[] x, double[] y, double xp);
    
    public double interpolar(double[] x, double[] y, double xp) {
        if (x == null || y == null) {
            throw new IllegalArgumentException("Los arrays no pueden ser nulos");
        }
        if (x.length == 0 || y.length == 0) {
            throw new IllegalArgumentException("Los arrays no pueden estar vacíos");
        }
        if (x.length != y.length) {
            throw new IllegalArgumentException("Los arrays deben tener el mismo tamaño");
        }
        return interpolarNewton(x, y, xp);
    }
}
