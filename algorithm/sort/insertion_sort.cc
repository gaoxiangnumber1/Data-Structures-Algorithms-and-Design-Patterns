#include<iostream>
using namespace std;

template<typename T>
void InsertionSort(T sort_array[], int length);

int main()
{
	int test_array1[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array2[9] = {5, 0, -99, 3, 56, 7, 8, -55, 56};
	int test_array3[10] = {-1, -8, 50, 4, 20, 0, 45, 9999, 520, 555555};
	InsertionSort(test_array1, 10);
	InsertionSort(test_array2, 9);
	InsertionSort(test_array3, 10);
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

template<typename T>
void InsertionSort(T sort_array[], int length)
{
	// sort_index is the index of element that we want to insert now
	// sort_array[0] is automatically sorted, so sort_index begins from 1
	for(int sort_index = 1; sort_index < length; sort_index++)
	{
		// store element in key
		T key = sort_array[sort_index];
		// compare from end to front only use 1 loop: move elements and
		// find proper position to insert key concurrently. Because when we can't move
		// elements, we find the proper position.
		// Otherwise compare from front to end use 2 loops: find the proper position
		// in one loop; and move elements in the other loop.
		int compare_index = sort_index - 1;  // compare from end to front
		while(compare_index >= 0 && sort_array[compare_index] > key)
		// if key is smaller than some elements in the front-sorted-array, then move
		{
			// we assume sort_array[compare_index + 1] = key before moving
			sort_array[compare_index + 1] = sort_array[compare_index];
			compare_index--;  // continue
		}
		// when we can't move elements, we find the proper position to insert key.
		sort_array[compare_index + 1] = key;
	}
}
