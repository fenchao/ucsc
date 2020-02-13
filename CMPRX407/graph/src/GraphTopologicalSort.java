import java.util.LinkedList;
import java.util.Queue;

/**
 * File Name: GraphTopologicalSort.java 
 * Topological Sort on a Graph
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphTopologicalSort.java
 */

class GraphTopologicalSort{
	private String t ;
	private Graph g ;
	//Output
	boolean [] cycle;
	int [] work ;
	int [] size ;
	int [] topoorder;
	//You can have any number of private variables and private funcions
	
	GraphTopologicalSort(String t, Graph g, boolean [] cycle, int [] work, int [] size, int [] topoorder) {
		this.t = t ;
		this.g = g ;
		this.cycle = cycle ;
		this.work = work ;
		this.size = size ;
		this.topoorder = topoorder ;
		
		//WRITE CODE
	}

	public static void main(String[] args) {
		System.out.println("GraphTopologicalSort.java starts");
		System.out.println("Use GraphTester.java to test");
		System.out.println("GraphTopologicalSort.java Ends");
	}
}
