import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;


/**
 * File Name: GraphBfs.java 
 * Breadth First Search on a graph
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphBfs.java
 */

class GraphBfs{
	private String t ;
	private Graph g ;
	String start;
	//Output
	private int [] work ;
	private int [] size ;
	private int [] bfsorder;
	private int [] bfspath ;
	//You can have any number of private variables and private funcions
	
	GraphBfs(String t, Graph g, String start, int [] work, int[] size, int [] bfsorder, int [] bfspath) {
		this.t = t ;
		this.g = g ;
		this.start = start;
		this.work = work ;
		this.size = size ;
		this.bfsorder = bfsorder ;
		this.bfspath = bfspath ;
    //WRITE YOUR CODE
		
	}

	public static void main(String[] args) {
		System.out.println("GraphBfs.java starts");
		System.out.println("Use GraphTest.java to test");
		System.out.println("GraphBfs.java Ends");
	}
}
