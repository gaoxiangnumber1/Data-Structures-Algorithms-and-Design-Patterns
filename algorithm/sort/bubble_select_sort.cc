#include <stdio.h>

#include <utility>

using namespace std;

template<typename T>
void BubbleSort(T *data, int first, int last) // [first, last)
{
	for(int left_index = first; left_index < last - 1; ++left_index)
	{
		for(int right_index = left_index + 1; right_index < last; ++right_index)
		{
			if(data[left_index] > data[right_index])
			{
				swap(data[left_index], data[right_index]);
			}
		}
	}
}
template <typename T>
void SelectionSort(T *data, int first, int last)
{
	for(int left_index = first; left_index < last - 1; ++left_index)
	{
		int min_index = left_index;
		for(int right_index = left_index + 1; right_index < last; ++right_index)
		{
			if(data[min_index] > data[right_index])
			{
				min_index = right_index;
			}
		}
		swap(data[left_index], data[min_index]);
	}
}
void Print(const char *name, int *data, int first, int last)
{
	printf("%s:\n", name);
	for(int index = 0; index < last; ++index)
	{
		printf("%d ", data[index]);
	}
	printf("\n");
}

int main()
{
	printf("BubbleSort:\n");
	int test_array1[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array2[9] = {5, 0, -99, 3, 56, 7, 8, -55, 56};
	int test_array3[10] = {-1, -8, 50, 4, 20, 0, 45, 9999, 520, 555555};
	BubbleSort(test_array1, 0, 10);
	BubbleSort(test_array2, 0, 9);
	BubbleSort(test_array3, 0, 10);
	Print("test_array1", test_array1, 0, 10);
	Print("test_array2", test_array2, 0, 9);
	Print("test_array3", test_array3, 0, 10);

	printf("SelectionSort:\n");
	int test_array4[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array5[9] = {5, 0, -99, 3, 56, 7, 8, -55, 56};
	int test_array6[10] = {-1, -8, 50, 4, 20, 0, 45, 9999, 520, 555555};
	SelectionSort(test_array4, 0, 10);
	SelectionSort(test_array5, 0, 9);
	SelectionSort(test_array6, 0, 10);
	Print("test_array4", test_array4, 0, 10);
	Print("test_array5", test_array5, 0, 9);
	Print("test_array6", test_array6, 0, 10);

	return 0;
}

