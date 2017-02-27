#include <stdio.h>
#include <string.h>

const int kLongStringSize = 1024;
const int kShortStringSize = 64;
const int kNumberOfChar = 128;

int Power(int base, int exponent)
{
	int power = 1;
	while(exponent != 0)
	{
		if((exponent & 0x1) == 1)
		{
			power *= base;
		}
		exponent >>= 1;
		base *= base;
	}
	return power;
}
int HashValue(const char *data, const int length)
{
	int hash_value = 0;
	for(int index = 0; index < length; ++index)
	{
		hash_value += static_cast<int>(data[index]) * Power(kNumberOfChar, length - 1 - index);
	}
	return hash_value;
}
int main()
{
	char long_string[kLongStringSize], short_string[kShortStringSize];
	int long_length, short_length;
	int target_hash_value, hash_value[kLongStringSize];
	while(scanf("%s %s", long_string, short_string) == 2)
	{
		long_length = strlen(long_string);
		short_length = strlen(short_string);
		target_hash_value = HashValue(short_string, short_length);
		hash_value[0] = HashValue(long_string, short_length);
		int last_substring_index = long_length - short_length;
		int to_subtract, to_add;
		for(int index = 1; index <= last_substring_index; ++index)
		{
			to_subtract =
			    static_cast<int>(long_string[index - 1]) * Power(kNumberOfChar, short_length - 1);
			to_add = static_cast<int>(long_string[index + short_length - 1]);
			hash_value[index] = (hash_value[index - 1] - to_subtract) * kNumberOfChar + to_add;
		}
		printf("substring_matched_index = ");
		int hash_value_matched = 0, substring_matched = 0;
		for(int index = 0; index <= last_substring_index; ++index)
		{
			if(hash_value[index] == target_hash_value)
			{
				++hash_value_matched;
				if(strncmp(long_string + index, short_string, short_length) == 0)
				{
					++substring_matched;
					printf("%d ", index);
				}
			}
		}
		double collision_rate = 0.0;
		if(hash_value_matched != 0)
		{
			collision_rate =
			    static_cast<double>(hash_value_matched - substring_matched) / hash_value_matched;
		}
		printf("\nhash_value_matched = %d, substring_matched = %d, collision_rate = %.2f%%\n",
		       hash_value_matched,
		       substring_matched,
		       collision_rate * 100);
	}
}
/*
asdfghjkl 014
substring_matched_index =
hash_value_matched = 0, substring_matched = 0, collision_rate = 0.00%
aaaaaaaa aaa
substring_matched_index = 0 1 2 3 4 5
hash_value_matched = 6, substring_matched = 6, collision_rate = 0.00%
asdfghjklopiuyt fghj
substring_matched_index = 3
hash_value_matched = 1, substring_matched = 1, collision_rate = 0.00%
asdfghjklkjhgfdsasd asd
substring_matched_index = 0 16
hash_value_matched = 2, substring_matched = 2, collision_rate = 0.00%
*/
