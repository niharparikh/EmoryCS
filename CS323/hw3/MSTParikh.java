//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
//A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

package edu.emory.mathcs.cs323.graph.span;

import java.util.*;

import edu.emory.mathcs.cs323.graph.Edge;
import edu.emory.mathcs.cs323.graph.Graph;
import edu.emory.mathcs.cs323.graph.span.SpanningTree;
import edu.emory.mathcs.cs323.graph.span.MSTAlgorithm;
import edu.emory.mathcs.cs323.graph.span.MSTPrim;

public class MSTParikh implements MSTAll {
	
	private double mstWeight;
	private List<SpanningTree> trees = new ArrayList<SpanningTree>();
	
	@Override
	public List<SpanningTree> getMinimumSpanningTrees(Graph graph) {		
		
		SpanningTree temp;
		MSTAlgorithm prim = new MSTPrim();
		temp = prim.getMinimumSpanningTree(graph);
		mstWeight = temp.getTotalWeight();
		
		PriorityQueue<Edge> queue = new PriorityQueue<>();
		Set<Integer> visited = new HashSet<>();
		SpanningTree tree = new SpanningTree();
		
		List<Edge> startingEdges = new ArrayList<Edge>();
		startingEdges = graph.getIncomingEdges(0);
		
		queue.addAll(startingEdges);
		visited.add(0);
		
		getMinimumSpanningTrees(graph, queue, visited, tree);
		
		return trees;
		
	}
	
	private void getMinimumSpanningTrees(Graph graph, PriorityQueue<Edge> queue, Set<Integer> visited, SpanningTree tree) {
		
		if (tree.getTotalWeight() > mstWeight) return;
		if (visited.size() == graph.size()) {
			trees.add(tree);
			System.out.println(tree + "\n--------\n");
			return;	
		}
		while (!queue.isEmpty()) {
			
			Edge edge = queue.poll();
			
			PriorityQueue<Edge> copied_queue = new PriorityQueue<>(queue);
			Set<Integer> copied_visited = new HashSet<>(visited);
			SpanningTree copied_tree = new SpanningTree(tree);

			copied_tree.addEdge(edge);
			if (!copied_visited.contains(edge.getSource())) copied_visited.add(edge.getSource());
			for (Edge e : graph.getIncomingEdges(edge.getSource())) if (!copied_queue.contains(e)) copied_queue.add(e);
			
			getMinimumSpanningTrees(graph, copied_queue, copied_visited, copied_tree);
			
		}
		
	}

}
