#ifndef HashTable_H_INCLUDED
#define HashTable_H_INCLUDED
using std::cout;
using std::cin;
using std::endl;

template<typename E, typename K>
class HashTable
{
public:
	HashTable(): hash_(nullptr), empty_(nullptr) {};  // constructor
	~HashTable();  // destructor
	void Initialization();  // initialize the hash table
	// search element whose key value is 'key' and return its position in 'position'
	bool Search(const K &key, int &position) const;
	void Insert(const E &element);  // insert a new element into hash table
	void Output();  // print hash table's contents

private:
	int divisor_;  // hash function's divisor: key%divisor_
	E *hash_;  // hash table array
	bool *empty_;  // an array to indicate whether the same position in hash table has element
	int HashSearch(const K &key) const;  // search hash table
};

template<typename E, typename K>
void HashTable<E, K>::Initialization()
{
	cout << "Please input your HashTable's max size and current size:\n";
	int max_size, current_size;
	cin >> max_size >> current_size;
	divisor_ = max_size;
	hash_ = new E[divisor_];
	empty_ = new bool[divisor_];
	for(int index = 0; index < divisor_; index++)
	{
		empty_[index] = true;
	}
	cout << "Please input " << current_size << " elements(we assume element's key = element):\n";
	while(current_size --)
	{
		E element;
		cin >> element;
		Insert(element);
	}
	Output();
}

template<typename E, typename K>
HashTable<E, K>::~HashTable()
{
	delete [] hash_;
	delete [] empty_;
	hash_ = nullptr;
	empty_ = nullptr;
}

template<typename E, typename K>
int HashTable<E, K>::HashSearch(const K &key) const
{
	int begin_bucket = key % divisor_;
	int current_bucket = begin_bucket;
	E element = key;  // use key to get the element's value
	do
	{
		// condition 1:find element in hash table, return element's index
		if(hash_[current_bucket] == element)
		{
			return current_bucket;
		}
		// condition 2:can't find element, return the index which element can be inserted into
		if(empty_[current_bucket])
		{
			return current_bucket;
		}
		current_bucket = (current_bucket + 1) % divisor_;
	}
	while(current_bucket != begin_bucket);
	// condition 3:can't find element and hash table is full, hash[current_bucket] != element
	return current_bucket;
}

template<typename E, typename K>
bool HashTable<E, K>::Search(const K &key, int &position) const
{
	int index = HashSearch(key);
	E element = key;
	if(empty_[index] || hash_[index] != element)  // condition 2 & 3: can't find element
	{
		return false;
	}
	position = index + 1;  // condition 1
	return true;
}

template<typename E, typename K>
void HashTable<E, K>::Insert(const E &element)
{
	K key = element;  // use element itself as its key
	int index = HashSearch(key);
	if(hash_[index] == element)  // condition 1: the element is already in hash table
	{
		cout << "Error: the key has been in hash table.\n";
	}
	if(empty_[index])  // condition 2: insert is ok
	{
		empty_[index] = false;
		hash_[index] = element;
		Output();
	}
	if(hash_[index] != element)  // condition 3: the hash table is full
	{
		cout << "Error: the hash table is full.\n";
	}
}

template<typename E, typename K>
void HashTable<E, K>::Output()
{
	cout << "HashTable' contents are: \n";
	for(int index = 0; index < divisor_; index++)
	{
		cout << index << " : ";
		if(empty_[index])
		{
			cout << "None\n";
		}
		else
		{
			cout << hash_[index] <<endl;
		}
	}
}

void AllOperation()
{
	HashTable<int, int> object1;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a HashTable.\n";
	cout << "2: search an element in HashTable.\n";
	cout << "3: insert element into HashTable.\n";
	cout << "4: print HashTable's contents.\n";
	cout << "5: destroy a HashTable.\n";

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
			int key, position;
			cout << "Please input your key(equal to element's value): ";
			cin >> key;
			if(object1.Search(key, position))
			{
				cout << key << " is the " << position <<" (th) element in hash table.\n";
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
			break;
		case 4:
			object1.Output();
			break;
		case 5:
			object1.~HashTable();
			cout << "You have destroy the HashTable. Please establish HashTable before executing operations.\n";
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
