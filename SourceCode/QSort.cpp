#include <iostream>
#include <cstdlib>

using namespace std;

void print(int first, int last, int *array)
{
	int i;
	for (i = first; i <= last; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}

void swap(int first, int last, int *array)
{
	int temp = array[first];
	array[first] = array[last];
	array[last] = temp;
}

int partition(int first, int last, int *array)
{
	int boundary = first;
	cout << "Pre-partition" << endl;
	print(first, last, array);
	
	int range = last - first;
	int random = rand() % range;
	random += first;
	int pivot = array[random];
	cout << "Random = " << random << ", pivot = " << pivot << endl;
	
	swap(boundary, random, array);
	
	int i;
	for (i = first+1; i <= last; i++)
	{
		if (array[i] >= pivot)
		{
			boundary++;
			swap(boundary, i, array);
		}
	}
	swap(boundary, first, array);
	
	cout << "Post partition" << endl;
	print(first, last, array);
	
	return random;
}

void quicksort(int first, int last, int *array)
{
	int range = last - first;
	if (range >= 1)
	{
		int pivot = partition(first, last, array);
		quicksort(first, pivot, array);
		quicksort(pivot+1, last, array);
	}
}

int main()
{
	int size = 10;
	int *array = (int *)malloc(sizeof(int) * size);
	
	int i;
	for (i = 0; i < size; i++)
	{
		array[i] = rand() % size;
		cout << array[i] << " ";
	}
	cout << endl;
	
	
	quicksort(0, size-1, array);
	for (i = 0; i < size; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
}
