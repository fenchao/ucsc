import java.util.Arrays;

/**
 * File Name: GraphDfs.java 
 * Depth First Search on a graph
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphDfs.java
 */

class GraphDfs{
	//You can have any number of private variables and private functions
	private String t ;
	private Graph g ;
	String start;
	//Output
	boolean [] cycle;
	int [] work ;
	int [] size ;
	int [] dfsorder;

	private int dfsIdx;
	private enum Visit {
		NONE, PARTIAL, FULL
	}
	Visit [] visit;
	
	GraphDfs(String t, Graph g, String start, boolean [] cycle, int [] work, int [] size, int [] dfsorder) {
		this.t = t ;
		this.g = g ;
		this.start = start;
		this.cycle = cycle ;
		this.work = work ;
		this.size = size ;
		this.dfsorder = dfsorder ;

		//WRITE YOUR CODE
		cycle[0] = false;
		work[0] = 0;
		dfsIdx = g.getnumV();
		visit = new Visit[g.getnumV()];
		Arrays.fill(this.visit, Visit.NONE);
		
		int from = g.graphHasNode(start);
		Graph.u.myassert(from != -1);
		dfs(from);
		
		if (g.isUndirectedGraph()) {
			cycle[0] = g.getnumE()/2 > g.getnumV() - 1;
		}
		size[0] = g.getnumV() - dfsIdx;
		
		System.out.println("\n" + this.t);
		System.out.printf("Num Verticies = %d\n", g.getnumV());
		System.out.printf("Num Edges     = %d\n", g.getnumE());
		System.out.printf("Work done     = %d\n", work[0]);
		System.out.printf("Has Cycle     = %s\n", cycle[0] ? "YES" : "NO");
		System.out.printf("DFS topological order =");
		for(int i = 0; dfsIdx < dfsorder.length; ++i, ++dfsIdx) {
			dfsorder[i] = dfsorder[dfsIdx];
			System.out.printf(" %s", g.getRealName(dfsorder[i]));
		}
		System.out.println();
		if (cycle[0]) {
			System.out.println("This order has no meaning");
		}
		if (size[0] < dfsorder.length) {
			System.out.printf("We have unvisited vertices starting from %s\n", start);
		}
	}
	
	private void dfs(int from) {
		switch(visit[from]) {
		case NONE:
			visit[from] = Visit.PARTIAL;
			int f = g.numFanout(from);
			work[0] += 1+f;
			for(int e = 0; e < f; ++e) {
				int to = g.getNodeFanout(from, e);
				dfs(to);
			}
			visit[from] = Visit.FULL;
			dfsorder[--dfsIdx] = from;
			break;
		case PARTIAL:
			cycle[0] = true;
			break;
		case FULL:
			break;
		default:
			// Impossible Default
			break;
		}
	}

	public static void main(String[] args) {
		System.out.println("GraphDfs.java starts");
		System.out.println("Use GraphTester.java to test");
		System.out.println("GraphDfs.java Ends");
	}
}