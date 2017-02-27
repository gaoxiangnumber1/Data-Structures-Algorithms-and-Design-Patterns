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
