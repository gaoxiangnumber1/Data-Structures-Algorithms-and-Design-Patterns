#ifndef CPPLIB_DS_MIN_HEAP_H_
#define CPPLIB_DS_MIN_HEAP_H_

#include "data.h"

template<typename KeyType, typename ValueType>
void MinHeapFixUp(Data<KeyType, ValueType> *data, int child_index)
{
	int parent_index = (child_index - 1) / 2;
	while(parent_index >= 0 && data[parent_index] > data[child_index])
	{
		std::swap(data[parent_index], data[child_index]);
		child_index = parent_index;
		parent_index = (child_index - 1) / 2;
	}
}
template<typename KeyType, typename ValueType>
void MinHeapFixDown(Data<KeyType, ValueType> *data, int parent_index, int last)
{
	int min_child_index = parent_index * 2 + 1;
	while(min_child_index < last)
	{
		if(min_child_index < last - 1 &&
		        data[min_child_index] > data[min_child_index + 1])
		{
			++min_child_index;
		}
		if(!(data[parent_index] > data[min_child_index]))
		{
			return;
		}
		std::swap(data[parent_index], data[min_child_index]);
		parent_index = min_child_index;
		min_child_index = parent_index * 2 + 1;
	}
}

template<typename KeyType, typename ValueType>
class MinHeap
{
public:
	MinHeap():
		current_length_(0),
		length_(0),
		data_(nullptr)
	{}
	MinHeap(int length):
		current_length_(0),
		length_(length),
		data_(new Data<KeyType, ValueType>[length_])
	{}
	~MinHeap();

	void Create();
	void Insert(const KeyType &key, const ValueType &value);
	ValueType ExtractMinValue();
	bool Empty() const
	{
		return current_length_ == 0;
	}

	void ShowContent() const;

private:
	int current_length_;
	int length_;
	Data<KeyType, ValueType> *data_;
};
template<typename KeyType, typename ValueType>
MinHeap<KeyType, ValueType>::~MinHeap()
{
	delete data_;
}
template<typename KeyType, typename ValueType>
void MinHeap<KeyType, ValueType>::Create()
{
	scanf("%d", &length_);
	data_ = new Data<KeyType, ValueType>[length_];
	KeyType key;
	ValueType value;
	for(int index = 0; index < length_; ++index)
	{
		scanf("%d %d", &key, &value);
		Insert(key, value);
	}
	ShowContent();
}
template<typename KeyType, typename ValueType>
void MinHeap<KeyType, ValueType>::Insert(const KeyType &key, const ValueType &value)
{
	if(current_length_ < length_)
	{
		data_[current_length_++] = Data<KeyType, ValueType>(key, value);
		MinHeapFixUp(data_, current_length_ - 1);
	}
}
template<typename KeyType, typename ValueType>
ValueType MinHeap<KeyType, ValueType>::ExtractMinValue()
{
	if(current_length_ > 0)
	{
		std::swap(data_[0], data_[--current_length_]);
		MinHeapFixDown(data_, 0, current_length_);
		return data_[current_length_].value_;
	}
	return ValueType();
}
template<typename KeyType, typename ValueType>
void MinHeap<KeyType, ValueType>::ShowContent() const
{
	for(int index = 0; index < length_; ++index)
	{
		printf("<%d, %d> ", data_[index].key_, data_[index].value_);
	}
	printf("\n");
}
#endif // CPPLIB_DS_MIN_HEAP_H_

