// Search target in [first, last)
// Assume: data points to a valid array, first and last are valid indexes.
// Return: nonnegative if found, otherwise -1.
int BinarySearchIterate(int *data, int first, int last, int target)
{
	while(first < last)
	{
		int middle = first + ((last - first) >> 1);
		// [first, middle), [middle, middle + 1), [middle + 1, last)
		if(data[middle] > target) // Search left half: [first, middle)
		{
			last = middle;
		}
		else if(data[middle] == target) // Return result.
		{
			return middle;
		}
		else // Search right half: [middle + 1, last)
		{
			first = middle + 1;
		}
	}
	return -1;
}
int BinarySearchRecursive(int *data, int first, int last, int target)
{
	if(first >= last)
	{
		return -1;
	}
	int middle = first + ((last - first) >> 1);
	// [first, middle), [middle, middle + 1), [middle + 1, last)
	if(data[middle] > target)
	{
		return BinarySearchRecursive(data, first, middle, target);
	}
	else if(data[middle] == target)
	{
		return middle;
	}
	else
	{
		return BinarySearchRecursive(data, middle + 1, last, target);
	}
}
