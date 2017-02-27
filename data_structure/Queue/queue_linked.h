#ifndef LinkedQueue_H_INCLUDED
#define LinkedQueue_H_INCLUDED
using std::cout;
using std::cin;
using std::endl;

template<typename T>
class LinkedQueue;
template<typename T>
class Node
{
	friend class LinkedQueue<T>;
public:
	Node(T value, Node<T> *pointer): data_(value), link_(pointer) {}
private:
	T data_;
	Node<T> *link_;
};

template<typename T>
class LinkedQueue
{
public:
	LinkedQueue(): front_(nullptr), rear_(nullptr) {};  // constructor
	~LinkedQueue();  // destructor
	void Initialization();  // create a LinkedQueue
	bool IsEmpty() const;  // check whether the LinkedQueue is empty
	void First() const;  // get the first value of LinkedQueue
	void Last() const;  // get the last value of LinkedQueue
	LinkedQueue<T>& PushRear(const T &value);  // insert a new element into LinkedQueue
	LinkedQueue<T>& PopFront();  // delete a value from the LinkedQueue
	void Output();  // print the LinkedQueue's contents from first to last

private:
	Node<T> *front_;  // point to the first node
	Node<T> *rear_;  // point to the last node
};

template<typename T>
void LinkedQueue<T>::Initialization()
{
	cout << "Please input your LinkedQueue's current size:\n";
	int current_size;
	cin >> current_size;
	cout << "Please input " << current_size << " elements from first to last:\n";
	while(current_size --)
	{
		T value;
		cin >> value;
		PushRear(value);
	}
	Output();
}

template<typename T>
LinkedQueue<T>::~LinkedQueue()
{
	Node<T> *next;
	while(front_)
	{
		next = front_->link_;
		delete front_;
		front_ = next;
	}
	rear_ = nullptr;  // always make the deleted pointer nullptr
}

template<typename T>
bool LinkedQueue<T>::IsEmpty() const
{
	return front_ == nullptr;
}

template<typename T>
void LinkedQueue<T>::First() const
{
	if(!IsEmpty())
	{
		cout << "The current first element is " << front_->data_ << endl;
		return;
	}
	cout << "Error: Can't get first element from an empty LinkedQueue.\n";
}

template<typename T>
void LinkedQueue<T>::Last() const
{
	if(!IsEmpty())
	{
		cout << "The current last element is " << rear_->data_ << endl;
		return;
	}
	cout << "Error: Can't get last element from an empty LinkedQueue.\n";
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::PushRear(const T &value)
{
	Node<T> *new_node = new Node<T> (value, nullptr);
	if(IsEmpty())
	{
		front_ = new_node;
	}
	else
	{
		rear_->link_ = new_node;
	}
	rear_ =new_node;
	return *this;
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::PopFront()
{
	if(IsEmpty())
	{
		cout << "Error: Can't delete from an empty LinkedQueue.\n";
		return *this;
	}
	if(front_ == rear_)
	{
		delete front_;
		front_ = rear_ = nullptr;
	}
	else
	{
		Node<T> *next = front_->link_;
		delete front_;
		front_ = next;
	}
	return *this;
}

template<typename T>
void LinkedQueue<T>::Output()
{
	if(IsEmpty())
	{
		cout << "Error: Can't print an empty LinkedQueue!\n";
		return;
	}
	cout << "The LinkedQueue's elements are(from first to last):\n";
	Node<T> *pointer = front_;
	while(pointer)
	{
		cout << pointer->data_ <<" ";
		pointer = pointer ->link_;
	}
	cout << endl;
}

void AllOperation()
{
	LinkedQueue<int> object1;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a LinkedQueue.\n";
	cout << "2: check whether the LinkedQueue is empty.\n";
	cout << "3: get the current first value of LinkedQueue.\n";
	cout << "4: get the current last value of LinkedQueue.\n";
	cout << "5: insert a new element into LinkedQueue.\n";
	cout << "6: delete a value from LinkedQueue.\n";
	cout << "7: print LinkedQueue.\n";
	cout << "8: destroy the LinkedQueue.\n";

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
				cout <<"LinkedQueue is empty.\n";
			}
			else
			{
				cout <<"LinkedQueue is not empty.\n";
			}
			break;
		case 3:
			object1.First();
			break;
		case 4:
			object1.Last();
			break;
		case 5:
			cout << "Please input the specific value: ";
			cin >> value;
			object1.PushRear(value);
			object1.Output();
			break;
		case 6:
			object1.PopFront();
			object1.Output();
			break;
		case 7:
			object1.Output();
			break;
		case 8:
			object1.~LinkedQueue();
			cout << "You have destroy the LinkedQueue. Please establish LinkedQueue before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}


#endif // LinkedQueue_H_INCLUDED
