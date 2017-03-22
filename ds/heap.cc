#include <stdio.h>

template<typename T>
class Heap
{
public:
	Heap(): current_length_(0), length_(0), data_(nullptr) {}
	~Heap();

//	void Create();
	void Insert(const T &data);
	void Delete(T &delete_data);
	void HeapSort();

//	void ShowContent();

private:
	int current_length_;
	int length_;
	T *data_;
};

template<typename T>
Heap<T>::~Heap()
{
	delete data_;
	data_ = nullptr;
}
template<typename T>
void Heap<T>::Insert(const T &data)
{
	if(current_length_ < length_)
	{
		int index = ++current_length_;
		while(index != 1 && data > data_[index/2])
		{
			data_[index] = data_[index/2];
			index /= 2;
		}
		data_[index] = data;
	}
}
template<typename T>
void Heap<T>::Delete(T &delete_data)
{
	if(current_length_ > 0)
	{
		delete_data = data_[1];
		T last_data = data_[current_length_--];
		int empty_index = 1, max_child_index = 2;
		while(max_child_index <= current_length_)
		{
			if(max_child_index < current_length_ &&
			        data_[max_child_index] < data_[max_child_index + 1])
			{
				++max_child_index;
			}
			if(last_data > data_[max_child_index])
			{
				break;
			}
			data_[empty_index] = data_[max_child_index];
			empty_index = max_child_index;
			max_child_index *= 2;
		}
		data_[empty_index] = last_data;
	}
}

template<typename T>
void Heap<T>::HeapSort()
{
	scanf("%d", &length_);
	data_ = new T [length_ + 1];
	T data[length_];
	for(int index = 0; index < length_; ++index)
	{
		scanf("%d", &data[index]);
	}
	for(int index = 0; index < length_; ++index)
	{
		Insert(data[index]);
	}
	for(int index = 0; index < length_; ++index)
	{
		Delete(data[index]);
		printf("%d ", data[index]);
	}
	printf("\n");
}

int main()
{
	for(;;)
	{
		Heap<int> heap;
		heap.HeapSort();
	}
}
