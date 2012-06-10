package info.davidesposito.math.calculator;

public class Node {

	public char c;
	public Node next;
	public Node prev;
	public int match;
	public float val;
	
	@Override
	public String toString() {
		return (c == 'n' ? (val+"") : (c+"")) + (next == null ? "" : next.toString());
	}
}
