#include<iostream>
using namespace std;

void QuickSort(int sort_array[], int first, int last);
int Partition(int sort_array[], int first, int last);

int main()
{
	int test_array1[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array2[9] = {5, 0, -99, 3, 56, 7, 8, -55, 56};
	int test_array3[10] = {-1, -8, 50, 4, 20, 0, 45, 9999, 520, 555555};
	QuickSort(test_array1, 0, 9);
	QuickSort(test_array2, 0, 8);
	QuickSort(test_array3,0, 9);
	cout << "test_array1:\n";
	for(int index = 0; index < 10; index++)
	{
		cout << test_array1[index] << " ";
	}
	cout << "\ntest_array2:\n";
	for(int index = 0; index < 9; index++)
	{
		cout << test_array2[index] << " ";
	}
	cout << "\ntest_array3:\n";
	for(int index = 0; index < 10; index++)
	{
		cout << test_array3[index] << " ";
	}
	cout << endl;

	return 0;
}

void QuickSort(int sort_array[], int first, int last)  // sort elements in range [first, last]
{
	if(first < last)  // if there is at least 2 elements
	{
		int divide = Partition(sort_array, first, last);  // get the partition number
		// quick sort two sub array
		QuickSort(sort_array, first, divide - 1);
		QuickSort(sort_array, divide + 1, last);
	}
}

int Partition(int sort_array[], int first, int last)
{
	int pivot = sort_array[last];  // pivot number
	int divide = first;  //the return value
	// traversal to partition the array into 2 group:
	// elements of group on the left of pivot number are all <= pivot while
	// elements of group on the right of pivot number are all > pivot
	for(int index = first; index < last; index++)
	{
		if(sort_array[index] <= pivot)
		{
			swap(sort_array[divide], sort_array[index]);
			divide++;
		}
	}
	// place pivot number in the "middle" of array
	swap(sort_array[divide], sort_array[last]);
	return divide;
}
