#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
using std::cout;
using std::cin;
using std::endl;

template<typename T>
class Queue
{
public:
	Queue(): front_(0), rear_(0), max_size_(0), queue_(nullptr) {};  // default constructor
	~Queue();  // destructor
	void Initialization();  // create a Queue
	bool IsEmpty() const;  // check whether the Queue is empty
	bool IsFull() const;  // check whether the Queue is full
	void First() const;  // get the first value of Queue
	void Last() const;  // get the last value of Queue
	Queue<T>& PushRear(const T &value);  // insert a new element into Queue
	Queue<T>& PopFront();  // delete a value from the Queue
	void Output();  // print the Queue's contents from front to rear

private:
	// assume queue_array is cyclic and front_ is a flag 1 position before the first element
	int front_;
	int rear_;  // the last element's position
	int max_size_;  // the size of queue_array; 1 more than the max number of elements
	T *queue_;  // the pointer of queue_array
};

template<typename T>
void Queue<T>::Initialization()
{
	cout << "Please input your Queue's max size and current size:\n";
	int max_queue_size, current_size;
	cin >> max_queue_size >> current_size;
	max_size_ = max_queue_size + 1;  // the 1 more space is for the flag front_
	queue_ = new T[max_size_];
	cout << "Please input " << current_size << " elements from front to rear:\n";
	while(current_size --)
	{
		T value;
		cin >> value;
		PushRear(value);
	}
	Output();
}

template<typename T>
Queue<T>::~Queue()
{
	front_ = rear_ = 0;
	delete [] queue_;
	// always make the deleted pointer as nullptr to avoid dangling pointer
	queue_ = nullptr;
}

template<typename T>
bool Queue<T>::IsEmpty() const
{
	return front_ == rear_;
}

template<typename T>
bool Queue<T>::IsFull() const
{
	// must % max_size_ to make the result index in range
	return (rear_ + 1) % max_size_ == front_;
}

template<typename T>
void Queue<T>::First() const
{
	if(!IsEmpty())
	{
		cout << "The first element is " << queue_[(front_ + 1) % max_size_] << endl;
		return;
	}
	cout << "Error: Can't get the first element from an empty Queue.\n";
}

template<typename T>
void Queue<T>::Last() const
{
	if(!IsEmpty())
	{
		cout << "The last element is " << queue_[rear_] << endl;
		return;
	}
	cout << "Error: Can't get the last element from an empty Queue.\n";
}

template<typename T>
Queue<T>& Queue<T>::PushRear(const T &value)
{
	if(IsFull())
	{
		cout << "Error: Can't insert element into a full queue.\n";
		return *this;
	}
	rear_ = (rear_ + 1) % max_size_;
	queue_[rear_] = value;
	return *this;
}

template<typename T>
Queue<T>& Queue<T>::PopFront()
{
	if(IsEmpty())
	{
		cout << "Error: Can't delete element from an empty Queue.\n";
		return *this;
	}
	front_ = (front_ + 1) % max_size_;  // just move flag front_ to indicate deleting element
	return *this;
}

template<typename T>
void Queue<T>::Output()
{
	if(IsEmpty())
	{
		cout << "Error: Can't print an empty Queue!\n";
		return;
	}
	cout << "The Queue's elements are(from front to rear):\n";
	// draw graph to understand this formula:
	int current_size = (max_size_ + rear_ - front_) % max_size_;
	int index = (front_ + 1) % max_size_;
	for(int cnt = 1; cnt <= current_size; cnt++)
	{
		cout << queue_[index] << " ";
		index = (index + 1) % max_size_;
	}
	cout << endl;
}

void AllOperation()
{
	Queue<int> object1;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a Queue.\n";
	cout << "2: check whether the Queue is empty.\n";
	cout << "3: check whether the Queue is full.\n";
	cout << "4: get the first value of Queue.\n";
	cout << "5: get the last value of Queue.\n";
	cout << "6: insert a new element into Queue.\n";
	cout << "7: delete the an element from Queue.\n";
	cout << "8: print Queue.\n";
	cout << "9: destroy the Queue.\n";

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
				cout <<"Queue is empty.\n";
			}
			else
			{
				cout <<"Queue is not empty.\n";
			}
			break;
		case 3:
			if(object1.IsFull())
			{
				cout <<"Queue is full.\n";
			}
			else
			{
				cout <<"Queue is not full.\n";
			}
			break;
		case 4:
			object1.First();
			break;
		case 5:
			object1.Last();
			break;
		case 6:
			int value;
			cout << "Please input the new element value: ";
			cin >> value;
			object1.PushRear(value);
			object1.Output();
			break;
		case 7:
			object1.PopFront();
			object1.Output();
			break;
		case 8:
			object1.Output();
			break;
		case 9:
			object1.~Queue();
			cout << "You have destroy the Queue. Please establish Queue before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}


#endif // QUEUE_H_INCLUDED
