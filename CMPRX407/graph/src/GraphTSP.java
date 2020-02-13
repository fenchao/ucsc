import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;


/**
 * File Name: GraphTSP.java 
 * Breadth First Search on a graph
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphTSP.java
 */

class GraphTSP{
	private String t ;
	private Graph g ;
	String start;
	//Output
	private int [] work ;
	private double [] cost ;
	
	//You can have any number of private variables and private funcions
	

	GraphTSP(String t, Graph g, String start, int [] work, double[] cost) {
		this.t = t ;
		this.g = g ;
		this.start = start;
		this.work = work ;
		this.cost = cost ;
		
		//WRITE CODE
	}

	public static void main(String[] args) {
		System.out.println("GraphTSP.java starts");
		System.out.println("Use GraphTest.java to test");
		System.out.println("GraphTSP.java Ends");
	}
}
