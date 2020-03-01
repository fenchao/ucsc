import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;


/**
 * File Name: GraphDijkstra.java 
 * Implements Dijkstra's algorithms
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphDijkstra.java
 */

class GraphDijkstra{
	//You can have any number of private variables and private functions
	//DATA GIVEN
	private String t ; //Title
	private String dotFile; //Write tree as a dot file
	private Graph g ;
	String start;
	String end;
	int [] work ;
	double [] cost ;

	private class dijNode {
		int name;
		double cost;
		dijNode(int name, double cost) {
			this.name = name;
			this.cost = cost;
		}
	}

	private class dijComp implements Comparator<dijNode> {
		@Override
		public int compare(dijNode node1, dijNode node2) {
			return node1.cost < node2.cost ? -1 : 1;
		}
	}

	GraphDijkstra(String t, String dotFile, Graph g, String start,String end, int [] work, double [] cost) {
		this.t = t ;
		this.dotFile = dotFile ;
		this.g = g ;
		this.start = start;
		this.end = end ;
		this.work = work ;
		this.cost = cost ;
		//WRITE YOUR CODE

		int src = g.graphHasNode(start);
		int dst = g.graphHasNode(end);
		Graph.u.myassert(src != -1 && dst != -1);
		int heapAdd = 0;

		int numv = g.getnumV();
		double[] costs = new double[numv];
		Arrays.fill(costs, g.INFINITY);
		costs[src] = 0;
		int[] parents = new int[numv];
		Arrays.fill(parents, -1);
		for(int i = 0; i < parents.length; ++i) {
			parents[i] = i;
		}
		boolean[] visited = new boolean[numv];
		Arrays.fill(visited, false);

		PriorityQueue<dijNode> q = new PriorityQueue<>(new dijComp());
		q.offer(new dijNode(src, 0));
		System.out.printf("\n----------%s----------\n", t);

		try {
			FileWriter fw = new FileWriter(dotFile);
			fw.write("digraph g {\n");
			fw.write("edge [color=black]\n");
			while(!q.isEmpty()) {
				++heapAdd;
				dijNode from = q.poll();
				if (!visited[from.name]) {
					printDijSummary(costs, parents, visited);
					System.out.printf("Working on Vertex: %s\n", g.getRealName(from.name));
					int f = g.numFanout(from.name);
					for(int e = 0; e < f; ++e) {
						++work[0];
						int to = g.getNodeFanout(from.name, e);
						double w = g.getNodeFanoutEdgeWeight(from.name, e);
						if (from.cost + w < costs[to]) {
							costs[to] = from.cost + w;
							parents[to] = from.name;
							q.offer(new dijNode(to, costs[to]));
							fw.write("  " + g.getRealName(from.name) + " -> " + g.getRealName(to));
							fw.write(" [label = " + String.format("%.1f", costs[to]) + "]\n");
						}
					}
					visited[from.name] = true;
				}
			}
			fw.write("}\n");
			fw.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
		printDijSummary(costs, parents, visited);
		printDijPath(costs, parents, src);
		printDijStats(costs, parents, src, dst, heapAdd);
	}

	private void printDijSummary(double[] costs, int[] parents, boolean[] visited) {
		String vstr = "", tfstr = "", cstr = "", pstr = "";
		int numv = g.getnumV();
		for(int v = 0; v < numv; ++v) {
			vstr  += "    " + g.getRealName(v);
			tfstr += "    " + (visited[v] ? "T" : "F");
			cstr  += costs[v] == g.INFINITY ? "    L" : String.format("%5.1f", costs[v]);
			pstr  += "    " + g.getRealName(parents[v]);
		}
		System.out.printf("%s\n%s\n%s\n%s\n", vstr, tfstr, cstr, pstr);
	}

	private void printDijPath(double[] costs, int[] parents, int src) {
		for(int n = 0; n < costs.length; ++n) {
			int dst = n;
			if (dst != src) {
				System.out.printf("The best way to go from %s to city %s is follows\n%s",
						g.getRealName(src), g.getRealName(dst), g.getRealName(src));
				String pstr = "", cstr = "";
				while(dst != src) {
					pstr = String.format(" -> %s", g.getRealName(dst)) + pstr;
					cstr = String.format(" + %.1f", g.getNodeFanoutEdgeWeightE(parents[dst], dst)) + cstr;
					dst = parents[dst];
				}
				System.out.printf("%s Cost = %s = %.1f\n", pstr, cstr.substring(3), costs[n]);
			}
		}
	}

	private void printDijStats(double[] costs, int[] parents, int src, int dst, int heapAdd) {
		System.out.println("WEIGHTED UNDIRECTED GRAPH");
		System.out.printf("Num Vertices = %d\n", g.getnumV());
		System.out.printf("Num Edges    = %d\n", g.getnumE());
		System.out.printf("Work done    = %d\n", work[0]);
		System.out.printf("numberofNodeAddedToHeap = %d\n", heapAdd);
		System.out.printf("Shortest path from city %s to city %s = %.1f\n",
				g.getRealName(src), g.getRealName(dst), costs[dst]);
	}

	public static void main(String[] args) {
		System.out.println("GraphDijkstra.java starts");
		System.out.println("Use GraphTest.java to test");
		System.out.println("GraphDijkstra.java Ends");
	}
}
