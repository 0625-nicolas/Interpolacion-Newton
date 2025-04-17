package libcalculadora;

public class CalculadoraAnalisis {
	static {
        System.loadLibrary("calcanalisis"); 
    }
	 public native double interpolarNewton(double[] x, double[] y, double xp);

}
