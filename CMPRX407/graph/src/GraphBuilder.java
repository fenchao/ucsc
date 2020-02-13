import java.io.BufferedReader;
import java.io.FileReader;


/**
 * File Name: GraphBuilder.java 
 * All routines that builds Graph
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphBuilder.java
 */

class GraphBuilder{
	private Graph g ;
	//You can have any number of private variables and private funcions
	
	GraphBuilder(Graph g, String f) {
		this.g = g ;
		//WRITE YOUR CODE
		try {
			BufferedReader br = new BufferedReader(new FileReader(f));
			String line;
			while((line = br.readLine()) != null) {
				String[] entry = line.trim().split("\\s+");
				if (entry.length < 2) {
					// TBD Number of nodes and edges are at the beginning
					// System.out.println("New Input Format. TBD");
				} else {
					Graph.u.myassert((isWeighted() && entry.length == 3) ||
							(!isWeighted() && entry.length == 2));
					int from = g.insertOrFind(entry[0], false);
					int to 	 = g.insertOrFind(entry[1], false);
					double w = isWeighted() ? Double.valueOf(entry[2]) : 0;
					g.createEdge(from, to, w, true);
					g.createEdge(to, from, w, false);
					if (g.isUndirectedGraph()) {
						g.createEdge(from, to, w, false);
						g.createEdge(to, from, w, true);
					}
				}
			}
			br.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private boolean isWeighted() {
	  	return g.getType() == GraphTest.GraphType.WEIGHTED_UNDIRECTED
	  		|| g.getType() == GraphTest.GraphType.WEIGHTED_DIRECTED;
	}

	public static void main(String[] args) {		
		System.out.println("GraphBuilder.java starts");
		System.out.println("Use GraphTester.java to test");
		System.out.println("GraphBuilder.java Ends");
	}
}