//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
//A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

package edu.emory.mathcs.cs323.hw.hybridsort;

import java.lang.reflect.Array;
import java.util.Arrays;
//import java.util.Comparator;
//import java.util.PriorityQueue;

import edu.emory.mathcs.cs323.sort.AbstractSort;
import edu.emory.mathcs.cs323.sort.divide_conquer.QuickSort;
//import edu.emory.mathcs.cs323.sort.divide_conquer.MergeSort;
//import edu.emory.mathcs.cs323.sort.comparison.InsertionSort;
import edu.emory.mathcs.cs323.sort.comparison.ShellSortKnuth;

/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public class HybridSortParikh<T extends Comparable<T>> implements HybridSort<T>
{
	private AbstractSort<T> engine;
	private AbstractSort<T> engine2;
//	private PriorityQueue<Node> pq;
	
	public HybridSortParikh ()
	{
		engine = new ShellSortKnuth<>();
		engine2 = new QuickSort<>();
//		Comparator<Node> comparator = new MyComparator();
//		pq = new PriorityQueue<Node>(comparator);
	}
	
	@Override
	@SuppressWarnings("unchecked")
	public T[] sort (T[][] input)
	{
		// Initialize length values to save time calling functions
		int l_rows = input.length;
		double threshold = 0.90;
		
		// Figure out how sorted it is
		int[] sorted_asc = new int[l_rows];
		int[] sorted_desc = new int[l_rows];
		
		// If element is greater or less than last, count it
		for(int i = 0; i < l_rows; i++) {
			for (int j = 1; j < input[i].length; j++) {
				if (input[i][j].compareTo(input[i][j-1]) >= 0) sorted_asc[i]++;
				else if (input[i][j].compareTo(input[i][j-1]) <= 0) sorted_desc[i]++;
			}
		}
		
		// For each case, run appropriate sort
		for(int i = 0; i < l_rows; i++) {
			int l_columns = input[i].length;
			if(sorted_asc[i] == (l_columns - 1)) 
				continue;
			if(sorted_desc[i] == (l_columns - 1)) {
				for(int j = 0; j < l_columns / 2; j++) {
					T tmp;
					tmp = input[i][j];
					input[i][j] = input[i][l_columns - j - 1];
					input[i][l_columns - j - 1] = tmp;
				}
				continue;
			}
			if(((double)sorted_asc[i] / (l_columns - 1)) >= threshold) 
				engine.sort(input[i]);
			if(((double)sorted_desc[i] / (l_columns - 1)) >= threshold) {
				for(int j = 0; j < l_columns / 2; j++) {
					T tmp;
					tmp = input[i][j];
					input[i][j] = input[i][l_columns - j - 1];
					input[i][l_columns - j - 1] = tmp;
				}
				engine.sort(input[i]);
			}
			engine2.sort(input[i]);
		}
				
		// Combine 2D array into 1D array
		int size = Arrays.stream(input).mapToInt(t -> t.length).sum();
		T[] output = (T[])Array.newInstance(input[0][0].getClass(), size);
		int beginIndex = 0;
		
		
//		PriorityQueue implementation did not work because could not identify comparable max value of generic T.

//		T max = null;
//		
//		int count = 0;
//		int[] pointers = new int[l_rows];
//		for (int i = 0; i < pointers.length; i++) {
//			pointers[i] = 0;
//		}
//		for (int i = 0; i < l_rows; i++) {
//			if (pointers[i] < input[i].length) {
//				Node test = new Node(input[i][pointers[i]], i);
//				pq.add(test);
//			} else {
//				Node test = new Node(max, i);
//				pq.add(test);
//			}
//
//		}
//		while (count < size) {
//			Node h = pq.poll(); 
//			output[count] = h.data; 
//			pointers[h.listNo]++; 
//			
//			
//			if (pointers[h.listNo] < input[h.listNo].length) { 
//				Node test = new Node(input[h.listNo][pointers[h.listNo]], h.listNo);
//				pq.add(test); 
//			} else {
//				Node test = new Node(max, h.listNo);
//				pq.add(test); 
//			}
//			count++;
//		}
		
		
		
		for (T[] t : input)
		{
			System.arraycopy(t, 0, output, beginIndex, t.length);
			beginIndex += t.length;
		}
		
		// QuickSort final list
		engine2.sort(output);
		return output;
	}
	

//	class Node {
//		T data;
//		int listNo;
//
//		public Node(T data, int listNo) {
//			this.data = data;
//			this.listNo = listNo;
//		}
//	}
//	
//	class MyComparator implements Comparator<Node> {
//
//	    public int compare(Node a, Node b) {
//	        return a.data.compareTo(b.data);
//	    }
//	}
}


