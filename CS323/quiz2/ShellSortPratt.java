//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
//A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

package edu.emory.mathcs.cs323.sort.comparison;

import java.util.Collections;
import java.util.Comparator;

public class ShellSortPratt<T extends Comparable<T>> extends ShellSort<T>
{
	public ShellSortPratt()
	{
		this(Comparator.naturalOrder());
	}
	
	public ShellSortPratt(Comparator<T> comparator)
	{
		this(comparator, 1000);
	}
	
	public ShellSortPratt(Comparator<T> comparator, int n)
	{
		super(comparator, n);
	}

	@Override
	protected void populateSequence(int n)
	{
		if (sequence.size() != 0) return;
		int tmp1 = 0, tmp2 = 0;
		sequence.add(1);
		while(true) 
		{
			if (sequence.get(tmp1)*2 < sequence.get(tmp2)*3) 
			{ 
				if (sequence.get(tmp1)*2 < n) sequence.add(sequence.get(tmp1)*2);
				else break;
				tmp1++; 
			} 
			else if (sequence.get(tmp1)*2 > sequence.get(tmp2)*3) 
			{ 
				if(sequence.get(tmp2)*3 < n) sequence.add(sequence.get(tmp2)*3); 
				else break;
				tmp2++; 
			} 
			else 
			{ 
				if(sequence.get(tmp1)*2 < n) sequence.add(sequence.get(tmp1)*2); 
				else break;
				tmp1++; 
				tmp2++; 
			}
		}
	}
	
	@Override
	protected int getSequenceStartIndex(int n)
	{
		int index = Collections.binarySearch(sequence, n);
		if (index < 0) index = -(index+1);
		if (index == sequence.size()) index--;
		return index;
	}
}
