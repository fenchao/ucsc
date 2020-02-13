import java.util.ArrayList;

/**
 * File Name: GraphBF.java 
 * Implements Bellman-Ford algorithm
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphBF.java
 */

class GraphBF{
	//DATA GIVEN
	private String t ; //Title
	private String dotFile; //Write tree as a dot file
	private Graph g ;
	String start;
	String end;
	int [] work ;
	double [] cost ;
	//You can have any number of private variables and private funcions

	GraphBF(String t, String dotFile, Graph g, String start,String end, int [] work, double [] cost) {
		this.t = t ;
		this.dotFile = dotFile ;
		this.g = g ;
		this.start = start;
		this.end = end ;
		this.work = work ;
		this.cost = cost ;
		//WRITE YOUR CODE
	}


	public static void main(String[] args) {
		System.out.println("GraphBF.java starts");
		System.out.println("Use GraphTest.java to test");
		System.out.println("GraphBF.java Ends");
	}
}