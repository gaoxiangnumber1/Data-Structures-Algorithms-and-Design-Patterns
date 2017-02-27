#ifndef MAXHEAP_H_INCLUDED
#define MAXHEAP_H_INCLUDED

using std::cout;
using std::cin;
using std::endl;

template<typename T>
class MaxHeap
{
public:
	MaxHeap(): current_size_(0), max_size_(0), heap_(0) {}  // default constructor
	~MaxHeap();  // destructor
	void CreateMaxHeap();  // create a max heap
	void Insert(const T &element);  // insert element into max heap
	void Delete(T &delete_element);  // delete the max element from heap
	void Output();  // print max heap's contents
	void HeapSort();  // execute heap sort

private:
	// current_size_ is the amount of elements now
	// max_size_ is the max amount of all elements the heap can hold
	int current_size_, max_size_;
	T *heap_;
};

template<typename T>
MaxHeap<T>::~MaxHeap()
{
	delete heap_;
	heap_ = 0;  // avoid dangling pointer
	current_size_ = 0;  // very important: avoid access invalid memory
	max_size_ = 0;
}

template<typename T>
void MaxHeap<T>::CreateMaxHeap()
{
	cout << "Please input heap's max size and current size:\n";
	int max_size, current_size;
	cin >> max_size >> current_size;
	max_size_ = max_size;
	heap_ = new T [max_size_ + 1];  // element index begin from 1, so we need one more element space
	cout << "Please input " << current_size << " elements:\n";
	for(int index = 1; index <= current_size; index++)
	{
		T element;
		cin >> element;
		Insert(element);
	}
	Output();
}

template<typename T>
void MaxHeap<T>::Insert(const T &element)
{
	if(current_size_ < max_size_)  // if there is free memory in heap
	{
		int position = ++current_size_;  // we should insert element into heap[position]
		// if element is bigger than it's parent node's value
		// position != 1: indicate the element has parent node
		while(position != 1 && element > heap_[position/2])
		{
			heap_[position] = heap_[position/2];  // move it's parent node down
			position = position / 2;  // move element to parent node's position
		}
		heap_[position] = element;  // insert element
	}
}

template<typename T>
void MaxHeap<T>::Delete(T &delete_element)
{
	if(current_size_ != 0)  // if heap is not empty
	{
		delete_element = heap_[1];
		T last_element = heap_[current_size_--];  // get the last element from heap and decrement size
		// we will insert last_element into heap[empty_position]
		// heap[max_child_position] is the bigger child node of parent node heap[empty_position]
		int empty_position = 1, max_child_position = 2;
		while(max_child_position <= current_size_)
		{
			// check whether heap_[max_child_position] is the bigger child node
			if(max_child_position < current_size_ &&
				heap_[max_child_position] < heap_[max_child_position + 1])
			{
				max_child_position++;
			}
			// if last_element is bigger than the bigger child node, then we find the right position
			if(last_element > heap_[max_child_position])
			{
				break;
			}
			// else exchange child node and parent node
			heap_[empty_position] = heap_[max_child_position];
			empty_position = max_child_position;
			max_child_position = max_child_position * 2;
		}
		heap_[empty_position] = last_element;  // insert last_element into heap
	}
}

template<typename T>
void MaxHeap<T>::Output()
{
	if(current_size_ == 0)
	{
		cout << "Error: empty max heap.\n";
		return;
	}
	cout << "The heap's contents are :\n";
	for(int index = 1; index <= current_size_; index++)
	{
		cout << heap_[index] << " ";
	}
	cout << endl;
}

template<typename T>
void MaxHeap<T>::HeapSort()
{
	// 1: store the unsorted elements in sort_array
    cout << "Please input elements' amount: \n";
    int amount;
    cin >> amount;
    T sort_array[amount];
    cout << "Please input " << amount << " elements:\n";
    for(int index = 0; index < amount; index++)
	{
		cin >> sort_array[index];
	}
	// 2: initialize sort_object
	max_size_ = amount;
	heap_ = new T [amount + 1];
	// 3: insert all elements of sort_array into heap sort_object
    for(int index = 0; index < amount; index++)
	{
		Insert(sort_array[index]);
	}
	// 4: delete all elements of heap sort_object and store the sorted elements in sort_array
    for(int index = 0; index < amount; index++)
	{
		Delete(sort_array[index]);
	}
	// 5: output the sorted elements
	cout << "The array after sorting are:\n";
    for(int index = 0; index < amount; index++)
	{
		cout << sort_array[index] << " ";
	}
	cout << endl;
}

void AllOperation()
{
	MaxHeap<int> object, sort_object;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a MaxHeap.\n";
	cout << "2: insert element into MaxHeap.\n";
	cout << "3: delete max element from MaxHeap.\n";
	cout << "4: print MaxHeap's contents.\n";
	cout << "5: destroy MaxHeap.\n";
	cout << "6: heap sort.\n";

	int operate;
	while(cin >> operate)
	{
		switch(operate)
		{
		case 0:
			goto END;
		case 1:
			object.CreateMaxHeap();
			break;
		case 2:
			cout << "Please input your element:\n";
			int element;
			cin >> element;
			object.Insert(element);
			object.Output();
			break;
		case 3:
			int delete_element;
			object.Delete(delete_element);
			cout << "The deleted element is " << delete_element <<endl;
			object.Output();
			break;
		case 4:
			object.Output();
			break;
		case 5:
			object.~MaxHeap();
			cout << "You have destroy the MaxHeap. Please establish MaxHeap before executing operations.\n";
			break;
		case 6:
			sort_object.HeapSort();
			sort_object.~MaxHeap();
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}

#endif // MAXHEAP_H_INCLUDED
