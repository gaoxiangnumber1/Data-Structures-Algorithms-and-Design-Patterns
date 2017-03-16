#include <stdio.h>

template<typename T>
class LinkedList;
template<typename T>
class Node
{
	friend class LinkedList<T>;
public:
	Node(): data_(T()), next_(nullptr) {}
	Node(const T &data): data_(data), next_(nullptr) {}
private:
	T data_;
	Node<T> *next_;
};

template<typename T>
class LinkedList
{
public:
	LinkedList(): first_(nullptr), length_(0) {}
	~LinkedList();

	void Create();
	void Insert(int index, const T &data);
	void ShowContent();
	void Delete(int index);
	void Reverse();

private:
	Node<T> *first_;
	int length_;
};

template<typename T>
LinkedList<T>::~LinkedList()
{
	while(first_ != nullptr)
	{
		Node<T> *next = first_->next_;
		delete first_;
		first_ = next;
	}
}
template<typename T>
void LinkedList<T>::Create()
{
	int data_number, data;
	scanf("%d", &data_number);
	while(data_number-- > 0)
	{
		scanf("%d", &data);
		Insert(length_, data);
	}
}
template<typename T>
void LinkedList<T>::Insert(int index, const T &data)
{
	if(index < 0 || index > length_) // index must be in [0, length_]
	{
		index = (index < 0 ? 0 : length_);
	}
	Node<T> *new_node = new Node<T>(data);
	if(index == 0) // Insert as the first node.
	{
		new_node->next_ = first_;
		first_ = new_node;
	}
	else
	{
		Node<T> *before_node = first_;
		for(int before_node_index = 0; before_node_index + 1 != index; ++before_node_index)
		{
			before_node = before_node->next_;
		}
		new_node->next_ = before_node->next_;
		before_node->next_ = new_node;
	}
	++length_;
}
template<typename T>
void LinkedList<T>::ShowContent()
{
	printf("%02d data:", length_);
	for(Node<T> *node = first_; node != nullptr; node = node -> next_)
	{
		printf(" %d", node->data_);
	}
	printf("\n");
}
template<typename T>
void LinkedList<T>::Delete(int index)
{
	if(first_ == nullptr) // Can't delete from empty linked list.
	{
		return;
	}
	if(index < 0 || index >= length_) // index must be in [0, length_ - 1]
	{
		index = (index < 0 ? 0 : length_ - 1);
	}
	if(index == 0)
	{
		Node<T> *new_first = first_->next_;
		delete first_;
		first_ = new_first;
	}
	else
	{
		Node<T> *before_node = first_;
		for(int before_node_index = 0; before_node_index + 1 != index; ++before_node_index)
		{
			before_node = before_node->next_;
		}
		Node<T> *delete_node = before_node->next_;
		before_node->next_ = delete_node->next_;
		delete delete_node;
	}
	--length_;
}
template<typename T>
void LinkedList<T>::Reverse()
{
	if(first_ == nullptr)
	{
		return;
	}
	Node<T> *before_node = first_, *after_node = first_->next_;
	first_->next_ = nullptr;
	while(after_node != nullptr)
	{
		Node<T> *next_after_node = after_node->next_;
		after_node->next_ = before_node;
		before_node = after_node;
		after_node = next_after_node;
	}
	first_ = before_node;
}

int main()
{
	LinkedList<int> object; // Stack object's dtor is auto called when scope ends.
	printf("0: Exit\n");
	printf("1: Create\n");
	printf("2: Insert\n");
	printf("3: Delete\n");
	printf("4: Reverse\n");

	int operation, data, index;
	while(scanf("%d", &operation) == 1)
	{
		switch(operation)
		{
		case 0:
			return 0;
		case 1:
			object.Create();
			object.ShowContent();
			break;
		case 2:
			scanf("%d %d", &index, &data);
			object.Insert(index, data);
			object.ShowContent();
			break;
		case 3:
			scanf("%d", &index);
			object.Delete(index);
			object.ShowContent();
			break;
		case 4:
			object.Reverse();
			object.ShowContent();
		}
	}
}
/*
1 5 1 2 3 4 5
4
2 -1 0
2 0 6
2 4 7
2 7 8
2 9 9
2 100 10
4
3 -1
3 0
3 5
3 7
3 5
4
05 data: 1 2 3 4 5
05 data: 5 4 3 2 1
06 data: 0 5 4 3 2 1
07 data: 6 0 5 4 3 2 1
08 data: 6 0 5 4 7 3 2 1
09 data: 6 0 5 4 7 3 2 8 1
10 data: 6 0 5 4 7 3 2 8 1 9
11 data: 6 0 5 4 7 3 2 8 1 9 10
11 data: 10 9 1 8 2 3 7 4 5 0 6
10 data: 9 1 8 2 3 7 4 5 0 6
09 data: 1 8 2 3 7 4 5 0 6
08 data: 1 8 2 3 7 5 0 6
07 data: 1 8 2 3 7 5 0
06 data: 1 8 2 3 7 0
06 data: 0 7 3 2 8 1
*/
