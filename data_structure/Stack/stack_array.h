#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
using std::cout;
using std::cin;
using std::endl;

template<typename T>
class Stack
{
public:
	Stack(int);  // constructor
	~Stack();  // destructor
	void Initialization();  // create a stack
	bool IsEmpty() const;  // check whether the stack is empty
	bool IsFull() const;  // check whether the stack is full
	void Top() const;  // get the top value of stack
	Stack<T>& Push(const T &value);  // insert a new element into the top position of stack
	Stack<T>& Pop(T &value);  // delete the top value from the stack
	void Output();  // print the stack's contents from bottom to top

private:
	int top_;
	int max_top_;
	T *stack_;
};

template<typename T>
void Stack<T>::Initialization()
{
	cout << "Please input your stack's max size and current size:\n";
	int max_stack_size, current_size;
	cin >> max_stack_size >> current_size;
	max_top_ = max_stack_size - 1;
	stack_ = new T[max_stack_size];
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
Stack<T>::Stack(int max_stack_size)
{
	top_ = -1;
	max_top_ = max_stack_size - 1;
	stack_ = new T[max_stack_size];
}

template<typename T>
Stack<T>::~Stack()
{
	top_ = -1;
	max_top_ = -1;
	delete [] stack_;
}

template<typename T>
bool Stack<T>::IsEmpty() const
{
	return top_ == -1;
}

template<typename T>
bool Stack<T>::IsFull() const
{
	return top_ == max_top_;
}

template<typename T>
void Stack<T>::Top() const
{
	if(!IsEmpty())
	{
		cout << "The current top element is " << stack_[top_] << endl;
		return;
	}
	cout << "Error: Can't get top element from an empty stack.\n";
}

template<typename T>
Stack<T>& Stack<T>::Push(const T &value)
{
	if(IsFull())
	{
		cout << "Error: Can't push into a full stack!\n";
		return *this;
	}
	stack_[++top_] = value;
	return *this;
}

template<typename T>
Stack<T>& Stack<T>::Pop(T &value)
{
	if(IsEmpty())
	{
		cout << "Error: Can't pop from an empty stack.\n";
		return *this;
	}
	value = stack_[top_--];
	return *this;
}

template<typename T>
void Stack<T>::Output()
{
	if(IsEmpty())
	{
		cout << "Error: Can't print an empty stack!\n";
		return;
	}
	cout << "The stack's elements are(from bottom to top):\n";
	for(int index = 0; index <= top_; index++)
	{
		cout << stack_[index] << " ";
	}
	cout << endl;
}

void AllOperation()
{
	Stack<int> object1(0);
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a stack.\n";
	cout << "2: check whether the stack is empty.\n";
	cout << "3: check whether the stack is full.\n";
	cout << "4: get the current top value of stack.\n";
	cout << "5: push a new element into stack.\n";
	cout << "6: pop the current top element from stack.\n";
	cout << "7: print stack.\n";
	cout << "8: destroy the stack.\n";

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
				cout <<"stack is empty.\n";
			}
			else
			{
				cout <<"stack is not empty.\n";
			}
			break;
		case 3:
			if(object1.IsFull())
			{
				cout <<"stack is full.\n";
			}
			else
			{
				cout <<"stack is not full.\n";
			}
			break;
		case 4:
			object1.Top();
			break;
		case 5:
			cout << "Please input the specific value: ";
			cin >> value;
			object1.Push(value);
			object1.Output();
			break;
		case 6:
			object1.Pop(value);
			object1.Output();
			break;
		case 7:
			object1.Output();
			break;
		case 8:
			object1.~Stack();
			cout << "You have destroy the stack. Please establish stack before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}


#endif // STACK_H_INCLUDED
