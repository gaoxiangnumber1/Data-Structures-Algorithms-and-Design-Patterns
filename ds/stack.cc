#include "node.h"

template<typename T>
class Stack
{
public:
	Stack(): top_(nullptr), length_(0) {}
	~Stack();

	void Create();
	void Push(const T &data);
	void Pop();
	T Top() const;

	bool Empty() const;
	int Size() const;
	void ShowContent() const;

private:
	Node<T> *top_;
	int length_;
};

template<typename T>
Stack<T>::~Stack()
{
	while(Empty() == false)
	{
		Node<T> *next = top_->next_;
		delete top_;
		top_ = next;
	}
}

template<typename T>
void Stack<T>::Create()
{
	printf("Input: data_number data_content\n");
	int data_number;
	scanf("%d", &data_number);
	while(data_number-- > 0)
	{
		int data;
		scanf("%d", &data);
		Push(data);
	}
}
template<typename T>
void Stack<T>::Push(const T &data)
{
	Node<T> *new_node = new Node<T>(data, top_);
	top_ = new_node;
	++length_;
}
template<typename T>
void Stack<T>::Pop()
{
	if(Empty() == true)
	{
		return;
	}
	Node<T> *new_top = top_->next_;
	delete top_;
	top_ = new_top;
	--length_;
}
template<typename T>
T Stack<T>::Top() const
{
	if(Empty() == true)
	{
		return T();
	}
	return top_->data_;
}
template<typename T>
bool Stack<T>::Empty() const
{
	return top_ == nullptr;
}
template<typename T>
int Stack<T>::Size() const
{
	return length_;
}
template<typename T>
void Stack<T>::ShowContent() const
{
	printf("%02d data:", Size());
	for(Node<T> *temp = top_; temp != nullptr; temp = temp->next_)
	{
		printf(" %d", temp->data_);
	}
	printf("\n");
}

int main()
{
	Stack<int> object;
	printf("0: Exit\n1: Create\n2: Push\n3: Pop\n4: Top\n");
	int operation, data;
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
			scanf("%d", &data);
			object.Push(data);
			object.ShowContent();
			break;
		case 3:
			object.Pop();
			object.ShowContent();
			break;
		case 4:
			printf("Top = %d\n", object.Top());
			object.ShowContent();
		}
	}
}
/*
1 5 1 2 3 4 5
2 6 2 7
3 3 3 3 3 3 3 3 3 3
4
2 0
4
0
Input: data_number data_content
05 data: 5 4 3 2 1
06 data: 6 5 4 3 2 1
07 data: 7 6 5 4 3 2 1
06 data: 6 5 4 3 2 1
05 data: 5 4 3 2 1
04 data: 4 3 2 1
03 data: 3 2 1
02 data: 2 1
01 data: 1
00 data:
00 data:
00 data:
00 data:
Top = 0
00 data:
01 data: 0
Top = 0
01 data: 0
*/
