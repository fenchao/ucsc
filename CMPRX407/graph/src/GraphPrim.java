import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * File Name: GraphPrim.java 
 * Implements Prim's algorithms
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphPrim.java
 */

class GraphPrim{
	//DATA GIVEN
	private String t ; //Title
	private String dotFile; //Write tree as a dot file
	private Graph g ;
	int [] work ;
	double [] cost ;
	//You can have any number of private variables and private funcions

	GraphPrim(String t, String dotFile, Graph g, int [] work, double [] cost) {
		this.t = t ;
		this.dotFile = dotFile ;
		this.g = g ;
		this.work = work ;
		this.cost = cost ;
		
		//WRITE CODE
	}

	
	public static void main(String[] args) {
		System.out.println("GraphPrim.java starts");
		System.out.println("Use GraphTest.java to test");
		System.out.println("GraphPrim.java Ends");
	}
}