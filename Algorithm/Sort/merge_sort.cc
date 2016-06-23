#include<iostream>
using namespace std;

template<typename T>
void MergeSort(T sort_array[], int first, int last, T temp[]);

int main()
{
	int test_array1[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array2[9] = {5, 0, -99, 3, 56, 7, 8, -55, 56};
	int test_array3[10] = {-1, -8, 50, 4, 20, 0, 45, 9999, 520, 555555};
	int temp[10];
	MergeSort(test_array1, 0, 10, temp);
	MergeSort(test_array2, 0, 9, temp);
	MergeSort(test_array3,0, 10, temp);
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
void MergeSort(T sort_array[], int first, int last, T temp[])
// sort range: [first, last) in sort_array;
// temp is used to temporary store the ordered sub-range elements of sort_array
// in merge process and later copy all ordered elements to sort_array after each merge.
{
	if(last - first > 1)  // only 1 element is automatically ordered and no need to divide
	{
		int middle = first + (last - first) / 2;  // middle index between first and last
		// left is the index of left-subrange array, right is the index of right-subrange array
		// left & right: used in according subrange to merge two subrange into temp array
		// index: used in temp to merge and later copy ordered elements into sort_array
		int left = first, right = middle, index = first;
		// first make the 2 subrange array to be ordered
		MergeSort(sort_array, first, middle, temp);  // merge sort [first, middle)
		MergeSort(sort_array, middle, last, temp);  // merge sort [middle, last)
		// second merge 2 ordered subrange array into sort_array by using temp array
		while(left < middle || right < last)  // continue merging if either subrange is not empty
		{
			// copy left element into temp array when:
			// 1. left is not empty but right is empty: left < middle && right >= last
			// 2. both are not empty and left is smaller or equal than right:
			// left < middle && right < last && sort_array[left] <= sort_array[right]
			// note || is short-circuit and "<=" rather than "<" guarantee sorting stability
			if(right >= last || (left < middle && sort_array[left] <= sort_array[right]))
			{
				temp[index++] = sort_array[left++];  // copy left element into temp array
			}
			else
			{
				temp[index++] = sort_array[right++];  // copy right element into temp array
			}
		}
		// copy ordered elements into sort_array
		for(index = first; index < last; index++)
		{
			sort_array[index] = temp[index];
		}
	}
}
