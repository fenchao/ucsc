import java.util.HashMap;

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
		HashMap<Integer, Integer> mp = new HashMap<>();
		for (int[] ladder : l) {
			if (ladder[0] > ladder[1]) {
				int tmp = ladder[0];
				ladder[0] = ladder[1];
				ladder[1] = tmp;
			}
			mp.put(ladder[0], ladder[1]);
		}
		for (int[] snake : s) {
			if (snake[0] < snake[1]) {
				int tmp = snake[0];
				snake[0] = snake[1];
				snake[1] = tmp;
			}
			mp.put(snake[0], snake[1]);
		}

		double w = 0;
		for(int i = 1; i < n; ++i) {
			if (mp.containsKey(i)) {
//				continue;
			}
			int from = g.insertOrFind(Integer.toString(i), false);
			for(int j = 1; j <= 6 && i+j <= n; ++j) {
				int to = mp.containsKey(i+j) ?
						g.insertOrFind(Integer.toString(mp.get(i+j)), false) :
						g.insertOrFind(Integer.toString(i+j), false);
				g.createEdge(from, to, w, true);
				g.createEdge(to, from, w, false);
			}
		}
	}

	public static void main(String[] args) {
		System.out.println("GraphSnakeandLadderBuilder starts");
		System.out.println("Use GraphTester.java to test");
		System.out.println("GraphSnakeandLadderBuilder Ends");
	}
}