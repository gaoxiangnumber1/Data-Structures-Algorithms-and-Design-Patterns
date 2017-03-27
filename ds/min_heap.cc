#include <stdio.h>
#include <utility>

template<typename T>
void MinHeapFixUp(T *data, int child_index)
{
	int parent_index = (child_index - 1) / 2;
	while(parent_index >= 0 && data[parent_index] > data[child_index])
	{
		std::swap(data[parent_index], data[child_index]);
		child_index = parent_index;
		parent_index = (child_index - 1) / 2;
	}
}
template<typename T>
void MinHeapFixDown(T *data, int parent_index, int last)
{
	int min_child_index = parent_index * 2 + 1;
	while(min_child_index < last)
	{
		if(min_child_index < last - 1 &&
		        data[min_child_index] > data[min_child_index + 1])
		{
			++min_child_index;
		}
		if(data[parent_index] <= data[min_child_index])
		{
			return;
		}
		std::swap(data[parent_index], data[min_child_index]);
		parent_index = min_child_index;
		min_child_index = parent_index * 2 + 1;
	}
}

template<typename T>
struct MinHeap
{
	MinHeap(): current_length_(0), length_(0), data_(nullptr) {}
	~MinHeap();

	void Create();
	void Insert(const T &data);
	void Delete();

	void ShowContent() const;

	int current_length_;
	int length_;
	T *data_;
};
template<typename T>
MinHeap<T>::~MinHeap()
{
	delete data_;
}
template<typename T>
void MinHeap<T>::Create()
{
	scanf("%d", &length_);
	data_ = new T[length_];
	int data;
	for(int index = 0; index < length_; ++index)
	{
		scanf("%d", &data);
		Insert(data);
	}
	ShowContent();
}
template<typename T>
void MinHeap<T>::Insert(const T &data)
{
	data_[current_length_++] = data;
	MinHeapFixUp(data_, current_length_ - 1);
}
template<typename T>
void MinHeap<T>::Delete()
{
	if(current_length_ > 0)
	{
		std::swap(data_[0], data_[--current_length_]);
		MinHeapFixDown(data_, 0, current_length_);
	}
}
template<typename T>
void MinHeap<T>::ShowContent() const
{
	for(int index = 0; index < length_; ++index)
	{
		printf("%d ", data_[index]);
	}
	printf("\n");
}

int main()
{
	printf("0: Exit\n1: Create\n2: Delete\n");
	int op;
	MinHeap<int> heap;
	while(scanf("%d", &op) == 1)
	{
		switch(op)
		{
		case 0:
			return 0;
		case 1:
			heap.Create();
			break;
		case 2:
			heap.Delete();
			heap.ShowContent();
			break;
		}
	}
}
/*
1 7 7 6 5 4 3 2 1
2
2
2
2
2
2
2
0
1 4 2 7 5 6 3
2 4 3 7 5 6 1
3 4 6 7 5 2 1
4 5 6 7 3 2 1
5 7 6 4 3 2 1
6 7 5 4 3 2 1
7 6 5 4 3 2 1
*/
