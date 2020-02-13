import java.io.FileWriter;


/**
 * File Name: GraphDot.java 
 * Writes graph as a dot file
 * 
 * @author Jagadeesh Vasudevamurthy
 * @year 2019s
 */

/*
 * To compile you require: IntUtil.java RandomInt.java Graph.java GraphTest.javs GraphDot.java
 */

class GraphDot{
	private Graph g ;
	private String fname;
	//You can have any number of private variables

	GraphDot(Graph g, String s) {
		this.g = g ;
		this.fname = s ;
		//WRITE CODE
		try {
			FileWriter fw = new FileWriter(this.fname);
			fw.write("digraph g {\n");
			fw.write("edge [" + (g.isUndirectedGraph() ? "dir=none, " : "") + "color=red]\n");
			for(int from = 0; from < g.getnumV(); ++from) {
				int f = g.numFanout(from);
				for(int e = 0; e < f; ++e) {
					int to = g.getNodeFanout(from, e);
					if (g.isUndirectedGraph() && from > to) {
						continue;
					}
					fw.write("  " + g.getRealName(from) + " -> " + g.getRealName(to));
					if(isWeighted()) {
						fw.write(" [label = " + g.getNodeFanoutEdgeWeight(from, e) + "]");
					}
					fw.write("\n");
				}
			}
			fw.write("}\n");
			fw.close();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private boolean isWeighted() {
	  	return g.getType() == GraphTest.GraphType.WEIGHTED_UNDIRECTED
	  		|| g.getType() == GraphTest.GraphType.WEIGHTED_DIRECTED;
	}


	public static void main(String[] args) {
		System.out.println("GraphDot.java starts");
		System.out.println("Use GraphTester.java to test");
		System.out.println("GraphDot.java Ends");
	}
}