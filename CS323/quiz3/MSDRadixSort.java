/* THIS CODE IS MY OWN WORK, IT WAS WRITTEN WITHOUT CONSULTING 
A TUTOR OR CODE WRITTEN BY OTHER STUDENTS - Nihar Parikh */

package edu.emory.mathcs.cs323.sort.distribution;

import java.util.Arrays;
import java.util.Comparator;

public class MSDRadixSort extends BucketSort<Integer>
{
	private final int MAX;
	private int div;
	
	public MSDRadixSort(int maxDigits)
	{
		this(maxDigits, Comparator.naturalOrder());
	}
	
	public MSDRadixSort(int maxDigits, Comparator<Integer> comparator)
	{
		super(10, false, comparator);
		MAX = maxDigits;
	}
	
	@Override
	public void sort(Integer[] array, int beginIndex, int endIndex) {
		sort(array, beginIndex, endIndex - 1, MAX - 1);
		System.out.println(Arrays.toString(array));
	}
	
	private void sort(Integer[] array, int beginIndex, int endIndex, int d)
	{
		
		if (endIndex <= beginIndex + 1) return;
		
		int[] count = new int[12];
		Integer[] temp = new Integer[array.length];
		div = (int)Math.pow(10, d);
		
		for (int i = beginIndex; i <= endIndex; i++) {
//			System.out.println(Arrays.toString(array));
//			System.out.println(((array[i] / div) % 10));
			count[((array[i] / div) % 10) + 2]++;
		
		}
		
		for (int k = 1; k < 10; k++) count[k] += count[k-1];
		
		for (int i = beginIndex; i <= endIndex; i++) temp[count[((array[i] / div) % 10) + 1]++] = array[i];
		
		for (int i = beginIndex; i <= endIndex; i++) array[i] = temp[i];
		
		for (int i = 0; i < 10; i++) {
			sort(array, beginIndex + count[i], beginIndex + count[i+1] - 1, d + 1);
		}
		
		
		

//		if(i < 0) return;
//		if(i == MAX - 1) {
//			div = (int)Math.pow(10, i);
//			super.sort(array, beginIndex, endIndex);
//		}
//		
//		int[] count = new int[10];
//		Arrays.fill(count, 0);
//		for(int j = 0; j < array.length; j++) {
//			for(int k = 0; k < 10; k++) {
//				if ((array[j] >= k*(int)Math.pow(10, i)) && array[j] < (k+2)*(int)Math.pow(10, i)) {
//					count[k]++;
//				}
//			}
//		}
//		
//		int beginIndex_temp = 0, endIndex_temp = count[0] - 1;
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[1];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[2];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[3];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[4];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[5];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[6];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[7];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[8];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		beginIndex_temp = endIndex_temp + 1;
//		endIndex_temp += count[9];
//		sort(array, beginIndex_temp, endIndex_temp);
//		
//		Arrays.fill(count, 0);
		
		
		
//		div = (int)Math.pow(10, i);
//		System.out.println("Div: " + div);
//		super.sort(array, beginIndex, endIndex);
		
		
//		
//		while (i >= 0) {
//			int beginIndex_temp = beginIndex, endIndex_temp = endIndex;
//			for(int j = 0; j < array.length; j++) {
//				if (array[j] >= (int)Math.pow(10, i)) {
//					beginIndex_temp += (endIndex_temp - )
//				}
//			}
//			
//			div = (int)Math.pow(10, i);
//			System.out.println("Div: " + div);
//			super.sort(array, beginIndex, endIndex);
//			
//			i--;
//		}
		
		
		
		
//		for (int i=(MAX-1); i>=0; i--)
//		{
//			div = (int)Math.pow(10, i);
//			System.out.println("Div: " + div);
//			super.sort(array, beginIndex, endIndex);
//		}
//		System.out.println(Arrays.toString(array));
	}
	
	@Override
	protected int getBucketIndex(Integer key)
	{
		return (key / div) % 10;
	}
}
