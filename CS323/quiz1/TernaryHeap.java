//THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING
//A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh

package edu.emory.mathcs.cs323.queue;


import java.util.*;

public class TernaryHeap<T extends Comparable<T>> extends AbstractPriorityQueue<T>
{
	private List<T> keys;
	private int size;
	
	public TernaryHeap()
	{
		this(Comparator.naturalOrder());
	}
	
	public TernaryHeap(Comparator<T> comparator)
	{
		super(comparator);
		keys = new ArrayList<>();
		keys.add(null);	// initialize the first item as null
		size = 0;
	}

	@Override
	public int size()
	{
		return size;
	}

	@Override
	public void add(T key)
	{
		keys.add(key);
		swim(++size);
	}
	
	private void swim(int k)
	{
		if(k == 2 && comparator.compare(keys.get(k-1), keys.get(k)) < 0) 
		{
			Collections.swap(keys, k-1, k);
			return;
		}
		while (k > 2 && comparator.compare(keys.get((k+1)/3), keys.get(k)) < 0)
		{
			Collections.swap(keys, (k+1)/3, k);
			k = (k+1)/3;
			if(k == 2 && comparator.compare(keys.get(k-1), keys.get(k)) < 0) 
			{
				Collections.swap(keys, k-1, k);
				break;
			}
		}
	}

	@Override
	public T removeAux()
	{
		Collections.swap(keys, 1, size);
		T max = keys.remove(size--);
		sink(1);
		return max;
	}
	
	private void sink(int k)
	{
		int largest;
		for (int i=k+1; i<=size; k=largest,i=(largest*3)-1)
		{
			largest = i;
			if (i < size && (comparator.compare(keys.get(i), keys.get(i+1)) < 0)) largest = i+1;
			if (i < (size-1) && (comparator.compare(keys.get(i+1), keys.get(i+2)) < 0)) largest = i+2;
			if (comparator.compare(keys.get(k), keys.get(largest)) >= 0) break;
			Collections.swap(keys, k, largest);	
		}
	}
}