#include<iostream>
#include<cstring>
using namespace std;

void RadixSort(int sort_array[], int total_digit, int length, int max_number);

int main()
{
	int test_array1[10] = {100, 20, 33, 9, 999999, 8, 56201, 5621, 45, 0};
	int test_array2[9] = {123, 321, 56, 58, 56, 250, 784, 9999999, 5210};
	int test_array3[7] = {329, 457, 657, 839, 436, 720, 355};
	RadixSort(test_array1, 10, 10, 9);
	RadixSort(test_array2, 10, 9, 9);
	RadixSort(test_array3, 10, 7, 9);
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
	for(int index = 0; index < 7; index++)
	{
		cout << test_array3[index] << " ";
	}
	cout << endl;

	return 0;
}

void RadixSort(int sort_array[], int total_digit, int length, int max_number)
// we assume all numbers are in [0, 10^10 - 1], so total_digit = 10 and
// because all numbers are in decimal, so max_number = 9.
{
	int divisor = 1;  // help to get each digit number from least to most significant digits
	for(int digit = 1; digit <= total_digit; digit++)
	// for each digit_number: use counting sort to sort.
	{
		// first store corresponding index element's digit_number of sort_array
		int digit_number[length];
		for(int index = 0; index < length; index++)
		{
			digit_number[index] = (sort_array[index] / divisor) % 10;
		}
		// second use counting sort to sort sort_array base on each digit_number
		int temp[length], count[max_number + 1];
		memset(count, 0, sizeof(count));
		for(int index = 0; index < length; index++)
		{
			count[digit_number[index]]++;
		}
		for(int index = 1; index <= max_number; index++)
		{
			count[index] += count[index - 1];
		}
		for(int index = length - 1; index >= 0; index--)
		{
			temp[count[digit_number[index]] - 1] = sort_array[index];
			count[digit_number[index]]--;
		}
		for(int index = 0; index < length; index++)
		{
			sort_array[index] = temp[index];
		}
		// third, update divisor to get the next high digit_number.
		divisor *= 10;
	}
}
