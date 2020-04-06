//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
//A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

package edu.emory.mathcs.cs323.graph.path;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

import edu.emory.mathcs.cs323.graph.Graph;

/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public class SPWikiParikh
{
	List<String> titles;
	int[][] links;
	
	public SPWikiParikh(InputStream inTitles, InputStream inLinks) throws Exception
	{
		titles = getTitles(inTitles);
		links  = getLinks(inLinks, titles.size());
		
		Graph g = new Graph(titles.size());
		Dijkstra d = new Dijkstra();
		
		for (int i = 0; i < links.length; i++) {
			for (int j = 0; j < links[i].length; j++) g.setDirectedEdge(i, links[i][j], 1);
		}
		
		// Hardcoded source titles and target titles
		int[] sources = {10, 47, 3419, 92, 456, 678, 2928, 958, 385, 2748};
		int[] targets = {364, 1946, 247, 65, 3892, 230, 4321, 12, 981, 809};
		
		for (int k = 0; k < sources.length; k++) {
			
			int source = sources[k];
			int target = targets[k];
			
			String s_path = titles.get(source);
			
			Integer[] solution_path = new Integer[g.size()];
			solution_path = d.getShortestPath(g, source, target);
			
			Integer temp = solution_path[0];
			int count = 0;
			
			if (temp == null) s_path += " -> " + "No path found";
			
			while (temp != null) {
				s_path += " -> " + titles.get(solution_path[count]);
				temp = solution_path[solution_path[count]];
				count = solution_path[count];
			}
			
			System.out.println(k+1 + ".\t" + s_path);
		}
	}
	
	public List<String> getTitles(InputStream in) throws Exception
	{
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));
		List<String> list = new ArrayList<>();
		String line;
		
		while ((line = reader.readLine()) != null)
			list.add(line.trim());
		
		reader.close();
		return list;
	}
	
	public int[][] getLinks(InputStream in, int size) throws Exception
	{
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));
		Pattern p = Pattern.compile(" ");
		int[][] array = new int[size][];
		int[] links;
		String line;
		String[] t;
		int i, j;
		
		for (i=0; (line = reader.readLine()) != null; i++)
		{
			line = line.trim();
			
			if (line.isEmpty())
				array[i] = new int[0];
			else
			{
				t = p.split(line);
				links = new int[t.length];
				array[i] = links;

				for (j=0; j<links.length; j++)
					links[j] = Integer.parseInt(t[j]);	
			}
		}
		
		return array;
	}
	
	static public void main(String[] args) throws Exception
	{
		// Replace links below
		final String TITLE_FILE = "/Users/Nihar/Downloads/wiki-titles-small.txt";
		final String LINK_FILE  = "/Users/Nihar/Downloads/wiki-links-small.txt";
		new SPWikiParikh(new FileInputStream(TITLE_FILE), new FileInputStream(LINK_FILE));
	}
}
