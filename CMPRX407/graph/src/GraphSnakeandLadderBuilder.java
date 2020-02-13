
/**
 * File Name: GraphSnakeandLadderBuilder.java 
 * All routines that builds SnakeandLadder Graph
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2018
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphSnakeandLadderBuilder.java
 */

class GraphSnakeandLadderBuilder{
	//given data
	private Graph g ;
	private int n ; //Max number on board
	private int[][] l; //ladder
	private int[][] s; //snakes
	//You can have any number of private variables
	
	
	GraphSnakeandLadderBuilder(Graph g, int n, int[][] l, int [][] s) {
		this.g = g ;
		this.n = n ;
		this.l = l ;
		this.s = s;
		buildGraph() ;
	}
	
	private void buildGraph() {
		//WRITE YOUR CODE
	}

	public static void main(String[] args) {
		System.out.println("GraphSnakeandLadderBuilder starts");
		System.out.println("Use GraphTester.java to test");
		System.out.println("GraphSnakeandLadderBuilder Ends");
	}
}