#ifndef SINGLELINKEDLIST_H_INCLUDED
#define SINGLELINKEDLIST_H_INCLUDED
using std::cout;
using std::cin;
using std::endl;

template<typename T>
class Chain;
template<typename T>
class ChainNode  // represent a node in a single linked list
{
	friend class Chain<T>;  // the list class
private:
	T data_;
	ChainNode<T> *link_;  // a pointer that points to the next node
};

template<typename T>
class Chain  // represent single linked list
{
public:
	Chain(): first_(nullptr) {}  // default constructor
	~Chain();  // destructor
	void Initialization();  // initialize a list in ascending order
	bool IsEmpty() const;  // check whether the list is empty
	int Length() const;  // get the list's length
	// check whether list[position-1] exist; if exist, store it in value
	bool Find(int position, T &value) const;
	int Search(const T &value) const;  // check whether value is in the list
	// delete list[position-1] (if exist); store it in value; return the modified list
	bool Delete(int position, T &value);
	// insert value at list[position], return the modified list
	bool Insert(int position, const T &value);
	void Reverse();  // reverse the list
	void Output() const;  // print the list's contents
	int FindPosition(int value);  // get the proper position for inserting new node

private:
	ChainNode<T> *first_;  // pointer that points to the first node of linked list
};

template<typename T>
void Chain<T> :: Initialization()
{
	cout << "Please input elements' number and all elements: \n";
	int length;
	cin >> length;
	while(length--)
	{
		int value;
		cin >> value;
		Insert(FindPosition(value), value);
	}
	Output();
}

template<typename T>
Chain<T> :: ~Chain()  // free all nodes' memory of list
{
	ChainNode<T> *next;  // local pointer to store current node's next node's address
	while(first_)
	{
		next = first_->link_;
		delete first_;
		first_ = next;
	}
}

template<typename T>
bool Chain<T> :: IsEmpty() const
{
	return first_ == nullptr;
}

template<typename T>
int Chain<T> :: Length() const
{
	ChainNode<T> *current = first_;
	int length = 0;
	while(current)
	{
		length++;
		current = current->link_;
	}
	return length;
}

template<typename T>
bool Chain<T> :: Find(int position, T &value) const
{
	if(position < 1 || position > Length())
	{
		return false;  // if position is out of range
	}
	int current_position = 1;
	ChainNode<T> *current_node = first_;
	while(current_position != position)
	{
		current_node = current_node->link_;
		current_position++;
	}
	value = current_node->data_;
	return true;
}

template<typename T>
int Chain<T> :: Search(const T &value) const
{
	int position = 1;
	ChainNode<T> *current = first_;
	while(current && current->data_ != value)  // we must first guarantee the pointer is in valid
	{
		current = current->link_;
		position++;
	}
	if(current)
	{
		return position;
	}
	return 0;
}

template<typename T>
bool Chain<T> :: Delete(int position, T &value)
{
	if(position < 1 || position > Length())
	{
		cout<<"Error: out of range!\n";
		return false;
	}
	// classified discussion: delete the first node and otherwise
	if(position == 1)
	{
		ChainNode<T> *next = first_->link_;
		value = first_->data_;
		delete first_;
		first_ = next;
	}
	else  //delete the non-first node
	{
		// first, we must get the list(position-1) node(assuming current_node);
		int current_position = 1;
		ChainNode<T> *current_node = first_;
		while(current_position != position-1)
		{
			current_node = current_node->link_;
			current_position++;
		}
		// second, we store list(position) in a local pointer delete_node and update linkage
		ChainNode<T> *delete_node = current_node->link_;
		current_node->link_ = delete_node->link_;
		value = delete_node->data_;
		// third, we free delete_node's memory and make it nullptr for safe
		delete delete_node;
		delete_node = nullptr;
	}
	return true;
}

template<typename T>
bool Chain<T> :: Insert(int position, const T &value)
{
	if(position < 0 || position > Length())
	{
		cout<<"Error: out of range!\n";
		return false;
	}
	ChainNode<T> *new_node = new ChainNode<T>;  // create a new node
	new_node->data_ = value;
	if(position == 0)  // insert at the beginning of list
	{
		new_node->link_ = first_;
		first_ = new_node;
	}
	else
	{
		// first, we must find the list(position), i.e., current_node
		int current_position = 1;
		ChainNode<T> *current_node = first_;
		while(current_position != position)
		{
			current_node = current_node->link_;
			current_position++;
		}
		// second, we insert the new_node after current_node: update linkages
		new_node->link_ = current_node->link_;
		current_node->link_ = new_node;
	}
	return true;
}

template<typename T>
void Chain<T> :: Reverse()
{
	if(first_ == nullptr)
	{
		cout << "Error: can't reverse an empty list.\n";
		return;
	}
	ChainNode<T> *current_pointer, *before_pointer, *after_pointer;
	// current_pointer is the pointer that we want to change its link now
	current_pointer = first_->link_;
	// target: current_pointer->link_ = before_pointer
	before_pointer = first_;
	while(current_pointer)  // when not reach list's end
	{
		// first, we store current pointer's link in after_pointer
		after_pointer = current_pointer->link_;
		// second, we change current pointer's link
		current_pointer->link_ = before_pointer;
		// third, we update pointer backward
		before_pointer = current_pointer;
		current_pointer = after_pointer;
	}
	// finally, we make first pointer to be the last pointer
	first_->link_ = nullptr;
	// and update first pointer
	first_ = before_pointer;
	Output();
}

template<typename T>
void Chain<T> :: Output() const
{
	if(first_ == nullptr)
	{
		cout << "List is empty!\n";
		return;
	}
	cout << "List's contents: ";
	ChainNode<T> *current = first_;
	while(current)
	{
		cout << current->data_ << " ";
		current = current->link_;
	}
	cout << endl;
}

template<typename T>
int Chain<T> :: FindPosition(int value)
{
	ChainNode<T> *current_pointer = first_;
	int current_position = 1;
	while(current_pointer)
	{
		// when value <= current_pointer:
		// insert value at current_pointer's position(i.e.: list[position-1])
		// and current_pointer move back by 1 position.
		if(value <= current_pointer->data_)
		{
			return current_position - 1;
		}
		// when  current_pointer <= value <= current_pointer->link:
		// insert value at current_pointer->link's position(i.e.: list[position])
		// and current_pointer->link move back by 1 position.
		if(current_pointer->data_ <= value && (!current_pointer->link_ || current_pointer->link_->data_ >= value))
		{
			return current_position;
		}
		current_pointer = current_pointer ->link_;
		current_position++;
	}
	return 0;
}

void AllOperation()
{
	Chain<int> object1;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a linear list in ascending order.\n";
	cout << "2: check whether the list is empty.\n";
	cout << "3: get the list's length.\n";
	cout << "4: check whether a specific position exist element.\n";
	cout << "5: check whether a specific value exist in the list.\n";
	cout << "6: delete an element.\n";
	cout << "7: insert an element.\n";
	cout << "8: print the list.\n";
	cout << "9: reverse the list.\n";
	cout << "10: destroy the list.\n";

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
				cout <<"List is empty.\n";
			}
			else
			{
				cout <<"List is not empty.\n";
			}
			break;
		case 3:
			cout << "The length of list is " << object1.Length() <<endl;
			break;
		case 4:
			cout << "Please input the specific position: ";
			cin >> position;
			if(object1.Find(position, value))
			{
				cout << "The value on your position is: " << value <<endl;
			}
			else
			{
				cout << "Element does't exist on your position!\n";
			}
			break;
		case 5:
			cout << "Please input the specific value: ";
			cin >> value;
			int result;
			result = object1.Search(value);
			if(result != 0)
			{
				cout << value << " is on the position " << result << endl;
			}
			else
			{
				cout << "This value does't exist in the list.\n";
			}
			break;
		case 6:
			cout << "Please input the position you want to delete: ";
			cin >> position;
			if(object1.Delete(position, value))
			{
				cout << "The value you delete is " << value <<endl;
				cout << "The new list is ";
				object1.Output();
			}
			break;
		case 7:
			cout << "Please input the position you want to insert into and the insert-value: ";
			cin >> position >> value;
			if(object1.Insert(position, value))
			{
				object1.Output();
			}
			break;
		case 8:
			object1.Output();
			break;
		case 9:
			object1.Reverse();
			break;
		case 10:
			object1.~Chain();
			cout << "You have destroy the list. Please establish list before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}

#endif // SINGLELINKEDLIST_H_INCLUDED
