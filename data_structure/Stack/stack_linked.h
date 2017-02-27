#ifndef LinkedStack_H_INCLUDED
#define LinkedStack_H_INCLUDED
using std::cout;
using std::cin;
using std::endl;

template<typename T>
class LinkedStack;
template<typename T>
class Node
{
	friend class LinkedStack<T>;
private:
	T data_;
	Node<T> *link_;
};

template<typename T>
class LinkedStack
{
public:
	LinkedStack(): top_(nullptr) {};  // constructor
	~LinkedStack();  // destructor
	void Initialization();  // create a LinkedStack
	bool IsEmpty() const;  // check whether the LinkedStack is empty
	void Top() const;  // get the top value of LinkedStack
	LinkedStack<T>& Push(const T &value);  // insert a new element into the top position of LinkedStack
	LinkedStack<T>& Pop();  // delete the top value from the LinkedStack
	void Output();  // print the LinkedStack's contents from bottom to top

private:
	Node<T> *top_;
};

template<typename T>
void LinkedStack<T>::Initialization()
{
	cout << "Please input your LinkedStack's current size:\n";
	int current_size;
	cin >> current_size;
	cout << "Please input " << current_size << " elements from bottom to top:\n";
	while(current_size --)
	{
		T value;
		cin >> value;
		Push(value);
	}
	Output();
}

template<typename T>
LinkedStack<T>::~LinkedStack()
{
	Node<T> *next;
	while(top_)
	{
		next = top_->link_;
		delete top_;
		top_ = next;
	}
}

template<typename T>
bool LinkedStack<T>::IsEmpty() const
{
	return top_ == nullptr;
}

template<typename T>
void LinkedStack<T>::Top() const
{
	if(!IsEmpty())
	{
		cout << "The current top element is " << top_->data_ << endl;
		return;
	}
	cout << "Error: Can't get top element from an empty LinkedStack.\n";
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::Push(const T &value)
{
	Node<T> *new_node = new Node<T>;
	new_node->data_ = value;
	new_node->link_ = top_;
	top_ = new_node;
	return *this;
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::Pop()
{
	if(IsEmpty())
	{
		cout << "Error: Can't pop from an empty LinkedStack.\n";
		return *this;
	}
	Node<T> *new_top = top_->link_;
	delete top_;
	top_ = new_top;
	return *this;
}

template<typename T>
void LinkedStack<T>::Output()
{
	if(IsEmpty())
	{
		cout << "Error: Can't print an empty LinkedStack!\n";
		return;
	}
	cout << "The LinkedStack's elements are(from top to bottom):\n";
	Node<T> *pointer = top_;
	while(pointer)
	{
		cout << pointer->data_ <<" ";
		pointer = pointer ->link_;
	}
	cout << endl;
}

void AllOperation()
{
	LinkedStack<int> object1;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a LinkedStack.\n";
	cout << "2: check whether the LinkedStack is empty.\n";
	cout << "3: get the current top value of LinkedStack.\n";
	cout << "4: push a new element into LinkedStack.\n";
	cout << "5: pop the current top element from LinkedStack.\n";
	cout << "6: print LinkedStack.\n";
	cout << "7: destroy the LinkedStack.\n";

	int operate, value, position;
	while(cin >> operate)
	{
		switch(operate)
		{
		case 0:
			goto END;
		case 1:
			object1.Initialization();
			break;
		case 2:
			if(object1.IsEmpty())
			{
				cout <<"LinkedStack is empty.\n";
			}
			else
			{
				cout <<"LinkedStack is not empty.\n";
			}
			break;
		case 3:
			object1.Top();
			break;
		case 4:
			cout << "Please input the specific value: ";
			cin >> value;
			object1.Push(value);
			object1.Output();
			break;
		case 5:
			object1.Pop();
			object1.Output();
			break;
		case 6:
			object1.Output();
			break;
		case 7:
			object1.~LinkedStack();
			cout << "You have destroy the LinkedStack. Please establish LinkedStack before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}


#endif // LinkedStack_H_INCLUDED
