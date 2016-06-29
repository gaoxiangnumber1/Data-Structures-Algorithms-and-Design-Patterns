// search target in [first, last)
// Return: nonnegative if find, -1 on error.
int BinarySearchLoop1(int array[], int first, int last, int target)
{
	// negative data:
	if(!array || first < 0 || last < 0)
	{
		return -1;
	}

	while(first < last)  // when the search scope is not empty
	{
		int middle = first + ((last - first) >> 1);  // first + last may overflow
		if(array[middle] == target)
		{
			return middle;
		}
		else if(array[middle] > target)
		{
			last = middle;  // [first, last) -> [first, middle)
		}
		else
		{
			first = middle + 1;  // [first, last) -> [middle + 1, last)
		}
	}

	return -1;  // not find
}

// search target in [first, last]
// Return: nonnegative if find, -1 on not find.
int BinarySearchLoop2(int array[], int first, int last, int target)
{
	// negative data:
	if(!array || first < 0 || last < 0)
	{
		return -1;
	}

	while(first <= last)  // when the search scope is not empty
	{
		int middle = first + ((last - first) >> 1);  // first + last may overflow
		if(array[middle] == target)
		{
			return middle;
		}
		else if(array[middle] > target)
		{
			last = middle - 1;  // [first, last] -> [first, middle - 1]
		}
		else
		{
			first = middle + 1;  // [first, last] -> [middle + 1, last]
		}
	}

	return -1;  // not find
}

int BinarySearchRecursive(int array[], int first, int last, int target)  // [first, last)
{
	// negative data:
	if(!array || first < 0 || last < 0)
	{
		return -1;
	}

	if (first >= last)
	{
		return -1;  // not find
	}

	int middle = first + ((last - first) >> 1);
	if (array[middle] == target)
	{
		return middle;
	}
	else if (array[middle] > target)
	{
		return BinarySearchRecursive(array, first, middle, target);
	}
	else
	{
		return BinarySearchRecursive(array, middle + 1, last, target);
	}
}
