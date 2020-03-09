import java.util.Comparator;
import java.util.PriorityQueue;

public class Hauffman {
	private static final int ASCII_MAX = 256;
	private String filename;
	private boolean show;
	private String origStr, encodedStr, decodedStr;
	private HauffmanNode hauffmanRoot;
	private String[] hauffmanDictionary; // mapping: char -> codes
	private int hauffmanCnt;
	
	private static final IntUtil u = new IntUtil();
	
	public Hauffman(String str, boolean show, String filename) {
		this.origStr = str;
		this.show = show;
		this.filename = filename;
		
		buildHauffmanTree();
		buildHauffmanDictionary();
	}
	
	public String encode() {
		StringBuffer buffer = new StringBuffer();
		for(int i = 0; i < origStr.length(); ++i) {
			int chr = (int) origStr.charAt(i);
			String codes = hauffmanDictionary[chr];
			buffer.append(codes);
		}
		encodedStr = buffer.toString();
		return encodedStr;
	}
	
	public String decode() {
		StringBuffer buffer = new StringBuffer();
		HauffmanNode cur = hauffmanRoot;
		for(int i = 0; i < encodedStr.length(); ++i) {
			char code = encodedStr.charAt(i);
			cur = decodeTraverse(cur, code, buffer);
		}
		decodedStr = buffer.toString();
		return decodedStr;
	}

	private class HauffmanNode {
		int id;
		char chr;
		int freq;
		HauffmanNode left, right;
		
		// Constructor for leaf nodes
		HauffmanNode(char chr, int freq) {
			this.chr = chr;
			this.freq = freq;
			this.left = null;
			this.right = null;
			this.id = ++hauffmanCnt;
			if (show) {
				System.out.printf("Leaf    node %2d: Character is '%c' Weight is %2d\n",
						  		  this.id, chr, freq);
			}
		}
		
		// Constructor for transit nodes
		HauffmanNode(HauffmanNode nodeLeft, HauffmanNode nodeRight) {
			// nodeLeft is never null for transit node
			this.freq = nodeLeft.freq +
					    (nodeRight == null ? 0 : nodeRight.freq);
			this.left = nodeLeft;
			this.right = nodeRight;
			this.id = ++hauffmanCnt;
			if (show) {
				System.out.printf("Transit node %2d: Left %c(%2d) Right %c(%2d) Weight = %2d\n",
				  		  		  this.id, nodeLeft.isLeaf() ? nodeLeft.chr : ' ', nodeLeft.freq,
				  		  		  nodeRight == null || !nodeRight.isLeaf() ? ' ' : nodeRight.chr,
				  		  		  nodeRight == null ? 0 : nodeRight.freq, this.freq);
				u.appendDotFile(filename, String.format("  %s -> %s [color=red]", this, nodeLeft));
				if (nodeRight != null) {
					u.appendDotFile(filename, String.format("  %s -> %s [color=blue]", this, nodeRight));
				}
			}
		}
		
		boolean isLeaf() {
			return left == null && right == null;
		}
		
		public String toString() {
			return "\""+this.id+"\\n"+this.freq+(this.isLeaf() ? "\\n"+this.chr : "")+"\"";
		}
	}
	
	private class HauffmanComparator implements Comparator<HauffmanNode> {
		@Override
		public int compare(HauffmanNode node1, HauffmanNode node2) {
			return node1.freq - node2.freq;
		}
	}
	
	private void buildHauffmanTree() {
		int[] freq = new int[ASCII_MAX];
		for(int i = 0; i < origStr.length(); ++i) {
			int chr = (int) origStr.charAt(i);
			++freq[chr];
		}
		
		if (show) {
			System.out.printf("============ %s +++++++++++++++\n", origStr);
			for(int chr = 0; chr < freq.length; ++chr) {
				if (freq[chr] != 0) {
					System.out.printf("'%c' occurs %2d times\n", (char) chr, freq[chr]);
				}
			}
			System.out.println("===Tree built in this order===============");
			u.openDotFile(filename);
			u.appendDotFile(filename, String.format("  label = \" %s \"", origStr));
		}

		PriorityQueue<HauffmanNode> q = new PriorityQueue<>(new HauffmanComparator());
		for(int chr = 0; chr < freq.length; ++chr) {
			if (freq[chr] != 0) {
				HauffmanNode node = new HauffmanNode((char) chr, freq[chr]);
				q.offer(node);
			}
		}
		
		while(q.size() > 1) {
			HauffmanNode nodeLeft = q.poll();
			HauffmanNode nodeRight = q.poll();
			HauffmanNode nodeTransit = new HauffmanNode(nodeLeft, nodeRight);
			q.offer(nodeTransit);
		}
		
		HauffmanNode node = q.poll();
		if (node == null || !node.isLeaf()) {
			hauffmanRoot = node;
		} else {
			// Add a root transit node if we have only one char
			hauffmanRoot = new HauffmanNode(node, null);
		}
		
		if (show) {
			u.closeDotFile(filename);
			System.out.printf("==== Tree has %d nodes =========\n", hauffmanCnt);
		}
	}
	
	private void buildHauffmanDictionary() {
		hauffmanDictionary = new String[ASCII_MAX];
		char[] codes = new char[ASCII_MAX];
		encodeTraverse(hauffmanRoot, codes, 0);
	}
	
	private void encodeTraverse(HauffmanNode node, char[] codes, int len) {
		if (node == null) {
			return;
		}
		
		if (node.isLeaf()) {
			StringBuffer buffer = new StringBuffer();
			for(int i = 0; i < len; ++i) {
				buffer.append(codes[i]);
			}
			int chr = (int) node.chr;
			hauffmanDictionary[chr] = buffer.toString();
		} else {
			codes[len] = '0';
			encodeTraverse(node.left, codes, len+1);
			codes[len] = '1';
			encodeTraverse(node.right, codes, len+1);
		}
	}
	
	// visit current node and return next node to visit
	private HauffmanNode decodeTraverse(HauffmanNode node, char code, StringBuffer buffer) {
		if (code == '0') {
			node = node.left;
		} else {
			node = node.right;
		}
		if (node.isLeaf()) {
			buffer.append(node.chr);
			node = hauffmanRoot;
		}
		return node;
	}
}
