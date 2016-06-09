#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED
using std::cout;
using std::cin;
using std::endl;

template<typename E, typename K>
class SortedChain;
template<typename E, typename K>
class ChainHashTable;
template<typename E, typename K>
class SortedChainNode
{
	friend class SortedChain<E,K>;
	friend class ChainHashTable<E,K>;
public:
	SortedChainNode(E data, SortedChainNode<E, K> *link): data_(data), link_(link) {}
private:
	E data_;
	SortedChainNode<E, K> *link_;
};

template<typename E, typename K>
class ChainHashTable;
template<typename E, typename K>
class SortedChain
{
	friend class ChainHashTable<E, K>;
public:
	SortedChain(): first_(nullptr) {}
	~SortedChain();
	void Insert(const E &element);  // insert new element into hash table in ascending order
	// search key's corresponding element and return its position
	bool Search(const K &key, int &position) const;
	bool Delete(const K &key);  // delete key's corresponding element if exist

private:
	SortedChainNode<E, K> *first_;
};

template<typename E, typename K>
SortedChain<E, K>::~SortedChain()
{
	SortedChainNode<E, K> *next;
	while(first_)
	{
		next = first_->link_;
		delete first_;
		first_ = next;
	}
}

template<typename E, typename K>
void SortedChain<E, K>::Insert(const E &element)
{
	// if hash table isn't empty: before->link_ = current
	SortedChainNode<E, K> *current = first_, *before = nullptr;
	// insert element just before "current"
	for(; current && current->data_ < element; before = current, current = current->link_);
	SortedChainNode<E, K> *new_node = new SortedChainNode<E, K> (element, current);
	if (current && current->data_ == element)  // if the element is already in hash table
	{
		cout << "Error: Can't insert same value into hash table.\n";
	}
	else if(before == nullptr)  // hash table is empty or first_->data > element
		                                        // insert element at the begin of hash table
	{
		first_ = new_node;
	}
	else
	{
		before->link_ = new_node;
	}
}

template<typename E, typename K>
bool SortedChain<E, K>::Search(const K &key, int &position) const
{
	SortedChainNode<E, K> *current = first_;
	E element = key;  // use key to get element
	int index = 0;
	for(; current && current->data_ < element; current = current->link_, index++);
	if(current && current->data_ == element)  // find the element
	{
		position = index + 1;
		return true;
	}
	return false;
}

template<typename E, typename K>
bool SortedChain<E, K>::Delete(const K &key)
{
	SortedChainNode<E, K> *current = first_, *before = nullptr;
	E element = key;
	for(; current && current->data_ < element; before = current, current = current->link_);
	if(current && current->data_ == element)  // if the element is in hash table
	{
		if(before)  // if the element is not the first node
		{
			before->link_ = current->link_;
		}
		else  // delete first node
		{
			first_ = current->link_;
		}
		delete current;
		return true;
	}
	cout << "Error: Can't find your key's element.\n";
	return false;
}

template<typename E, typename K>
class ChainHashTable
{
public:
	ChainHashTable(): divisor_(0), hash_(nullptr) {}
	~ChainHashTable()
	{
		delete [] hash_;
		hash_ = nullptr;
	}
	void Initialization()
	{
		cout << "Please input your ChainHashTable's max size and current number of elements:\n";
		int max_size, number;
		cin >> max_size >> number;
		divisor_ = max_size;
		hash_ = new SortedChain<E, K> [divisor_];
		cout << "Please input "<< number << " elements(we assume element's key = element):\n";
		while(number --)
		{
			E element;
			cin >> element;
			Insert(element);
		}
		Output();
	}
	void Insert(const E &element)
	{
		K key = element;
		hash_[key % divisor_].Insert(element);
	}
	bool Search(const K &key, int &position) const
	{
		return hash_[key % divisor_].Search(key, position);
	}
	void Delete(const K &key)
	{
		hash_[key % divisor_].Delete(key);
	}
	void Output()
	{
		cout << "ChainHashTable's contents are :\n";
		for(int index = 0; index < divisor_; index++)
		{
			cout << index << " : ";
			SortedChainNode<E, K> *current = hash_[index].first_;
			while(current)
			{
				cout << current->data_ << " ";
				current = current->link_;
			}
			cout << endl;
		}
	}
	int divisor()
	{
		return divisor_;
	}

private:
	int divisor_;
	SortedChain<E, K> *hash_;
};


void AllOperation()
{
	ChainHashTable<int, int> object1;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a ChainHashTable.\n";
	cout << "2: search an element in ChainHashTable.\n";
	cout << "3: insert element into ChainHashTable.\n";
	cout << "4: delete an element in ChainHashTable.\n";
	cout << "5: print ChainHashTable's contents.\n";
	cout << "6: destroy a ChainHashTable.\n";

	int operate;
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
			int key, position;
			cout << "Please input your key(equal to element's value):\n";
			cin >> key;
			if(object1.Search(key, position))
			{
				cout << key << " is the " << position <<" (th) element in the " << key%object1.divisor()
				<< "(th) bucket.\n";
			}
			else
			{
				cout <<"Can't find!\n";
			}
			break;
		case 3:
			int element;
			cout << "Please input your element: ";
			cin >> element;
			object1.Insert(element);
			object1.Output();
			break;
		case 4:
			cout << "Please input the element's key: ";
			cin >> key;
			object1.Delete(key);
			object1.Output();
			break;
		case 5:
			object1.Output();
			break;
		case 6:
			object1.~ChainHashTable();
			cout << "You have destroy the ChainHashTable. Please establish ChainHashTable before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}


#endif // HashTable_H_INCLUDED
