#include<iostream>
using namespace std;

void SelectSort(int sort_array[], int length);
void BubbleSort(int sort_array[], int length);

int main()
{
	cout << "SelectSort:\n";
	int test_array1[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array2[9] = {5, 0, -99, 3, 56, 7, 8, -55, 56};
	int test_array3[10] = {-1, -8, 50, 4, 20, 0, 45, 9999, 520, 555555};
	SelectSort(test_array1, 10);
	SelectSort(test_array2, 9);
	SelectSort(test_array3, 10);
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

	cout << "BubbleSort:\n";
	int test_array4[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array5[9] = {5, 0, -99, 3, 56, 7, 8, -55, 56};
	int test_array6[10] = {-1, -8, 50, 4, 20, 0, 45, 9999, 520, 555555};
	BubbleSort(test_array4, 10);
	BubbleSort(test_array5, 9);
	BubbleSort(test_array6, 10);
	cout << "test_array4:\n";
	for(int index = 0; index < 10; index++)
	{
		cout << test_array4[index] << " ";
	}
	cout << "\ntest_array5:\n";
	for(int index = 0; index < 9; index++)
	{
		cout << test_array5[index] << " ";
	}
	cout << "\ntest_array6:\n";
	for(int index = 0; index < 10; index++)
	{
		cout << test_array6[index] << " ";
	}
	cout << endl;

	return 0;
}

void SelectSort(int sort_array[], int length)
{
	for(int index1 = 0; index1 < length; index1++)
	{
		int min_index = index1;
		for(int index2 = index1; index2 < length; index2++)  // find the minimum element's index
		{
			if(sort_array[min_index] > sort_array[index2])
			{
				min_index = index2;
			}
		}
		swap(sort_array[min_index], sort_array[index1]);  // exchange element
	}
}

void BubbleSort(int sort_array[], int length)
{
	for(int cnt = 0; cnt < length; cnt++)
	{
		for(int index = 1; index < length - cnt; index++)
		{
			if(sort_array[index - 1] > sort_array[index])
			{
				swap(sort_array[index - 1], sort_array[index]);
			}
		}
	}
}
