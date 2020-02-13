
/**
 * File Name: DagLongestPath.java 
 * Longest path in a DAG
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphTopologicalSort.java DagLongestPath.java
 */

class DagLongestPath{
	//inputs
	private String t ;
	private Graph g ;
	//output
	double [] w ;
	//You can have any numbers of private variables and function
	

	DagLongestPath(String t, Graph g, double [] w) {
		this.t = t ;
		this.g = g ;
		this.w = w ;
		//WRITE CODE
	}

	
	public static void main(String[] args) {
		System.out.println("DagLongestPath.java starts");
		System.out.println("Use GraphTester.java to test");
		System.out.println("DagLongestPath.java Ends");
	}
}