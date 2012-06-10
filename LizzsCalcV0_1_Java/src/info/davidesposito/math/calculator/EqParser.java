package info.davidesposito.math.calculator;

public class EqParser {

	public static float evaluateEq(Node eq) {
		// S -> <ex>
		return ex(eq);
	}
	
	private static float ex(Node eq) {
		if (eq != null && eq.c == '(') {
			return ex(eq.next);
		} else {
			return ex2(eq);
		}
	}
	
	private static float ex2(Node eq) {
		
		return 0;
	}
	
	private static float op2(Node eq) {
		return 0;
	}
	
	private static float _op2(Node eq) {
		return 0;
	}
	
	private static float op1(Node eq) {
		return 0;
	}
	
	private static float _op1(Node eq) {
		return 0;
	}
	
	private static float geo(Node eq) {
		return 0;
	}
	
	private static float _geo(Node eq) {
		return 0;
	}
	
	private static float arg(Node eq) {
		return 0;
	}
	
	private static float _num(Node eq) {
		return 0;
	}
	
	private static float _const(Node eq) {
		return 0;
	}
	
	private static boolean isNum(Node c) {
		return false;
	}
}
