#include<iostream>
#include<cstring>
using namespace std;

void CountingSort(int sort_array[], int length, int max_number);

int main()
{
	int test_array1[10] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	int test_array2[9] = {5, 0, 99, 3, 56, 7, 8, 55, 56};
	int test_array3[10] = {1, 8, 50, 4, 20, 0, 45, 999, 520, 555};
	CountingSort(test_array1, 10, 9);
	CountingSort(test_array2, 9, 99);
	CountingSort(test_array3, 10, 999);
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

void CountingSort(int sort_array[], int length, int max_number)
{
	// temp: store the ordered elements and then copy to sort_array
	// count: count[element] = the count of numbers that are <= element
	int temp[length], count[max_number + 1];
	// Initialize the count array: assign 0 to every element in count
	memset(count, 0, sizeof(count));
	// First we count the frequency of every integer in sort_array
	for(int index = 0; index < length; index++)
	{
		count[sort_array[index]]++;
	}
	// Second we compute for each index = 0; 1; …… ; max_number
	// how many input elements are less than or equal to index
	// by keeping a running sum of the array count
	for(int index = 1; index <= max_number; index++)
	{
		count[index] += count[index - 1];
	}
	// Place each element in sort_array into its correct ordered position
	// in the array temp. we must place element from last to first in order to
	// keep the sorting stability.
	for(int index = length - 1; index >= 0; index--)
	{
		temp[count[sort_array[index]] - 1] = sort_array[index];
		count[sort_array[index]]--;
	}
	// copy the ordered elements into sort_array.
	for(int index = 0; index < length; index++)
	{
		sort_array[index] = temp[index];
	}
}

*************************************************************************
const int kMax = 14;

// This sort algorithm is based on counting sort(O(n)), but unstable and quicker.
void NonStableCountingSort(vector<int> &number, int first, int last)
{
	// First, initialize cnt array to all zeros:
	int cnt[kMax];
	for(int num = 0; num < kMax; ++num)
	{
		cnt[num] = 0;
	}

	// Second, get frequency of each number in array number:
	for(int index = first; index <= last; ++index)
	{
		++cnt[number[index]];
	}

	// Third, fill ordered numbers in array number:
	int pos = first;
	for(int num = 0; num < kMax; ++num)
	{
		while(cnt[num]--)
		{
			number[pos++] = num;
		}
	}
}
