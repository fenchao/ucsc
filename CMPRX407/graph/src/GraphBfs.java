import java.util.Arrays;
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

		bfs();
	}

	private void bfs() {
		int from = g.graphHasNode(start);
		Graph.u.myassert(from != -1);

		// General Init
		work[0] = 0;
		size[0] = 0;
		int numv = g.getnumV();
		int[] level = new int[numv];
		Arrays.fill(level, -1);
		int[] path = new int[numv];
		Arrays.fill(path, -1);
		level[from] = 0;
		path[from] = 0;

		// Queue Init
		Queue<Integer> q = new LinkedList<>();
		q.offer(from);

		// Real BFS
		while(!q.isEmpty()) {
			from = q.poll();
			bfsorder[size[0]] = from;
			bfspath[size[0]] = path[from];
			++size[0];

			int f = g.numFanout(from);
			work[0] += 1 + f;
			for(int e = 0; e < f; ++e) {
				int to = g.getNodeFanout(from, e);
				if (level[to] == -1) {
					q.offer(to);
					level[to] = level[from]+1;
					path[to] = from;
				}
			}
		}

		// Get max string length for padding
		int m = 0;
		for(int i = 0; i < numv; ++i) {
			int l = g.getNodeRealName(i).length();
			if (m < l) {
				m = l;
			}
		}

		// Print
		System.out.println("\n"+t);
		System.out.printf("Num Vertices = %d\n", numv);
		System.out.printf("Num Edges    = %d\n", g.getnumE());
		System.out.printf("Work done    = %d\n", work[0]);
		System.out.printf("BFS order =");
		for(int i  = 0; i < size[0]; ++i) {
			System.out.printf(" %"+ m + "s", g.getRealName(bfsorder[i]));
		}
		System.out.printf("\nBFS path  =");
		for(int i  = 0; i < size[0]; ++i) {
			System.out.printf(" %"+ m + "s", g.getRealName(bfspath[i]));
		}
		for(int i  = 0; i < size[0]; ++i) {
			int[] shortestPath = new int[level[bfsorder[i]]+1];
			int cur = bfsorder[i];
			for(int j = shortestPath.length-1; j >= 0; --j) {
				shortestPath[j] = cur;
				cur = path[cur];
			}
			for(int j = 0 ; j < shortestPath.length; ++j) {
				System.out.printf("%s%s", j == 0 ? "\n" : "->", g.getRealName(shortestPath[j]));
			}
		}
		System.out.println();
	}

	public static void main(String[] args) {
		System.out.println("GraphBfs.java starts");
		System.out.println("Use GraphTest.java to test");
		System.out.println("GraphBfs.java Ends");
	}
}
