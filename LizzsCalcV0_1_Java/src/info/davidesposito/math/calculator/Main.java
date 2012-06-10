package info.davidesposito.math.calculator;

public class Main {
	
	public static final char SIN = 's';
	public static final char COS = 'c';
	public static final char TAN = 't';
	public static final char ARC = 'a';
	public static final char LOG = 'g';
	public static final char SQRT = 'q';
	public static final char LN = 'l';
	
	public static final char E = 'e';
	public static final char PI = 'p';
	

	public static Node parse1(Node eq) {
		return validateParentheses(eq) ? parse(eq, '+', '-') : null;
	}

	public static Node parse2(Node eq) {
		return validateParentheses(eq) ? parse(eq, '*', '/') : null;
	}

	public static Node parse(Node eq, char c1, char c2) {
		Node probe = eq;
		Node ip = eq;
		while (probe != null && probe.next != null) {
			if (probe.c == c1 || probe.c == c2) {
				surround(ip, probe);
				if (ip == eq && ip.prev != null)
					eq = ip.prev;
				ip = probe.next;
			}
			if (probe.c == '(')
				probe = parse(probe.next, c1, c2);
			else if (probe.c == ')') {
				surround(ip, probe);
				return probe.next;
			} else
				probe = probe.next;
		}
		if (probe == null)
			return eq;
		if (eq.prev == null) {
			if (ip != eq) {
				insertBefore(ip, '(');
				if (ip == eq && ip.prev != null)
					eq = ip.prev;
				Node temp = getNode(')');
				temp.prev = probe;
				probe.next = temp;
			}
			return eq;
		}
		if (ip != eq)
			surround(ip, probe);
		return probe.next;
	}

	public static void printList(Node probe) {
		while (probe != null) {
			System.out.print(probe.c);
			probe = probe.next;
		}
		System.out.println();
	}

	private static Node getNode(char c) {
		Node n = new Node();
		n.c = c;
		n.next = null;
		n.prev = null;
		n.match = -1;
		n.val = 0;
		return n;
	}

	private static boolean isNum(char c) {
		return c >= '0' && c <= '9';
	}
	
	private static boolean isConst(char c) {
		return c == E || c == PI;
	}
	
	private static boolean isOp(char c) {
		return c == 's' || c == 'c' || c == 't' || c == 'l' || c == 'a';
	}

	private static Node generateList(String eq) {
		// FIXME: handle negative numbers
		Node head = getNode('h');
		Node probe = head;
		for (int i = 0; i < eq.length(); i++) {
			if (i < eq.length() && isNum(eq.charAt(i))) {
				float temp = 0;
				while (i<eq.length() && isNum(eq.charAt(i))) {
				    temp = (temp * 10) + (eq.charAt(i++) - '0');
				  }
				  if (i<eq.length() && eq.charAt(i) == '.') {
				    char count = 1;
				    while (i<eq.length() && isNum(eq.charAt(++i))) {
				      temp += ((float)(eq.charAt(i) - '0')) / Math.pow(10.0, count++);
				    }    
				  }
				  probe.next = getNode('n');
				  probe.next.val = temp;
				  i--;
			} else if (isConst(eq.charAt(i))) {
				probe.next = getNode('n');
				probe.next.val = (float) ((eq.charAt(i) == E) ? 2.718281828459 : 3.1415926535);
			} else if (isOp(eq.charAt(i))) {
				switch(eq.charAt(i)) {
				case 's' :
					if (eq.charAt(i+1) == 'q') {
						probe.next = getNode(SQRT);
						i += 3;
						break;
					}
				case 'c' :
				case 't' :
				case 'l' :
					if (eq.charAt(i+1) == 'n') {
						probe.next = getNode(LN);
						i += 1;
						break;
					}
				case 'a' :
					probe.next = getNode(eq.charAt(i));
					i += 2;
				}
			} else
				probe.next = getNode(eq.charAt(i));
			probe.next.prev = probe;
			probe = probe.next;
		}
		head = head.next;
		head.prev = null;
		return head;
	}

	private static void surround(Node ip, Node probe) {
		Node left = (ip.prev != null && ip.prev.c == '(') ? ip.prev : ip;
		Node right = probe.c == ')' ? probe : probe.prev;
		if (left.match < 0 || right.match < 0 || left.match != right.match) {
			insertBefore(ip, '(');
			insertBefore(probe, ')');
		}
	}

	private static void insertBefore(Node curr, char c) {
		Node temp = getNode(c);
		if (curr.prev != null)
			curr.prev.next = temp;
		temp.next = curr;
		temp.prev = curr.prev;
		curr.prev = temp;
	}

	private static boolean validateParentheses(Node probe) {
		Node[] arr = new Node[10];
		int count = 0;
		int curr = 0;
		while (probe != null) {
			if (probe.c == '(')
				arr[curr++] = probe;
			else if (probe.c == ')') {
				arr[--curr].match = count;
				probe.match = count++;
			}
			probe = probe.next;
		}
		return curr == 0;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		test("3+4+6");
		test("3+4*6");
		test("3*4*6");
		test("3+(6*8)+42");
		test("3+sin(p*2^(5))^(2)+42");
	}

	private static void test(String eq) {
		System.out.println(eq);
		Node temp = generateList(eq);
		if (validateParentheses(temp)) {
			temp = parse1(temp);
			System.out.print("\t");
			printList(temp);
			temp = parse2(temp);
			System.out.print("\t");
			printList(temp);
		}
	}
}
