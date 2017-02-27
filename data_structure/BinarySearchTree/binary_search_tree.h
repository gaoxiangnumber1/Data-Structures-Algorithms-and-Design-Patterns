#ifndef BINARYSEARCHTREE_H_INCLUDED
#define BINARYSEARCHTREE_H_INCLUDED

#include "Queue.h"
using std::cout;
using std::cin;
using std::endl;

template<typename E, typename K>
class BinarySearchTree;
template<typename T>
class Node
{
	template<typename E, typename K>
	class BinarySearchTree;
public:
	Node(T data, Node<T> *left, Node<T> *right): data_(data), left_(left), right_(right) {}

	T data_;
	Node<T> *left_, *right_;
};

template<typename E, typename K>
class BinarySearchTree
{
	template<E>	friend void Output(Node<E> *root);  // level-order traversal
	template<E>	friend int Height(Node<E> *root);  // get tree's height

public:
	BinarySearchTree(): root_(0) {}  // default constructor
	~BinarySearchTree();  // destructor
	void Initialization();  // create a binary search tree
	bool Search(const K &key) const;  // search key in binary search tree
	bool Insert(const E &element);  // insert element into binary search tree
	bool Delete(const K &key);  // delete key's corresponding element


	Node<E> *root_;
};

template<typename E, typename K>
BinarySearchTree<E, K>::~BinarySearchTree()
{
	delete root_;
	root_ = 0;
}

template<typename E, typename K>
void BinarySearchTree<E, K>::Initialization()
{
	cout << "Please input your elements' amount:\n";
	int amount;
	cin >> amount;
	cout << "Please input " << amount << " elements:\n";
	for(int index = 0; index < amount; index++)
	{
		int element;
		cin >> element;
		Insert(element);
	}
}

template<typename E, typename K>
bool BinarySearchTree<E, K>::Search(const K &key) const
{
	Node<E> *pointer = root_;
	while(pointer)
	{
		if(key < pointer->data_)  // search in the sub-left-tree
		{
			pointer = pointer->left_;
		}
		else if(key == pointer->data_)  // find
		{
			return true;
		}
		else  // search in the sub-right-tree
		{
			pointer = pointer->right_;
		}
	}
	return false;  // can't find
}

template<typename E, typename K>
bool BinarySearchTree<E, K>::Insert(const E &element)
{
	Node<E> *search_pointer = root_, *parent_pointer = 0;
	// check whether the element already exist in the binary search tree
	while(search_pointer)
	{
		// if the tree is not empty, then parent_pointer is the parent node of search_pointer
		parent_pointer = search_pointer;
		if(element < search_pointer->data_)  // check in the sub-left-tree
		{
			search_pointer = search_pointer->left_;
		}
		else if(element > search_pointer->data_)// check in the right-left-tree
		{
			search_pointer = search_pointer->right_;
		}
		else
		{
			return false;  // can't insert duplicate element into tree
		}
	}
	// insert element into tree
	Node<E> *new_node = new Node<E> (element, 0, 0);
	if(root_)
	{
		if(element < parent_pointer->data_)
		{
			parent_pointer->left_ = new_node;
		}
		else
		{
			parent_pointer->right_ = new_node;
		}
	}
	else
	{
		root_ = new_node;
	}
	return true;
}

template<typename E, typename K>
bool BinarySearchTree<E, K>::Delete(const K &key)
{
	// we assume delete_node->data_ = key, that is, we should delete delete_node
	// and if the tree is not empty: parent_node is the parent node of delete_node
	Node<E> *delete_node = root_, *parent_node = 0;
	while(delete_node && delete_node->data_ != key)
	{
		parent_node = delete_node;
		if(key < delete_node->data_)
		{
			delete_node = delete_node->left_;
		}
		else
		{
			delete_node = delete_node->right_;
		}
	}
	if(delete_node == 0)  // key is not in the tree, so we can't delete it's element
	{
		return false;
	}
	// first we consider if the delete_node has two children and
	// convert this condition to the delete_node only has one child condition
	if(delete_node->left_ && delete_node->right_)
	{
		// left_max is the biggest node in the sub-left-tree of delete_node and
		// left_max_parent is the parent node of left_max
		Node<E> *left_max = delete_node->left_, *left_max_parent = delete_node;
		while(left_max->right_)  // the rightmost node in sub-left-tree is the biggest node
		{
			left_max_parent = left_max;
			left_max = left_max->right_;
		}
		// transfer the condition:
		delete_node->data_ = left_max->data_;  // assign left_max node's value to delete_node
		// update the nodes
		delete_node = left_max;
		parent_node = left_max_parent;
	}
	// up to now, the delete_node either has no child node or has only one child node
	// child_node is delete_node->left_ or delete_node->left_ or 0
	Node<E> *child_node = (delete_node->left_) ? delete_node->left_ : delete_node->right_;
	if(delete_node == root_)  // if delete_node is root, then update root to its' child_node
	{
		root_ = child_node;
	}
	// else update parent node's child to delete_node's child according delete_node's position
	else if(delete_node == parent_node->left_)
	{
		parent_node->left_ = child_node;
	}
	else if(delete_node == parent_node->right_)
	{
		parent_node->right_ = child_node;
	}
	delete delete_node;  // free memory
	delete_node = 0;  // and set it to zero
	return true;
}

template<typename E>
void Output(Node<E> *root)  // from top to bottom; from left to right
{
	if(root == 0)
	{
		cout << "Error: empty binary search tree!\n";
		return;
	}
	cout << "BinarySearchTree contents in level order are:\n";
	Queue<Node<E> *> queue;  // use queue data structure
	queue.Push(root);
	Node<E> *node = queue.Top();  // get current top node of queue
	while(node)  // while queue is not empty
	{
		cout << node->data_ << " ";  // access node itself
		if(node->left_)
		{
			queue.Push(node->left_);  // push left-sub-node into queue's rear
		}
		if(node->right_)
		{
			queue.Push(node->right_);  // push right-sub-node into queue's rear
		}
		queue.Pop();  // delete the accessed node
		node = queue.Top();  // get the next node of queue
	}
	cout << endl;
}

template<typename E>
int Height(Node<E> *root)
{
	if(root)
	{
		int left = Height(root->left_);  // get left-subtree's height
		int right = Height(root->right_);  // get right-subtree's height
		return (left > right) ? ++left : ++right;  // return max(left, right) + 1(root's height = 1)
	}
	return 0;
}

void AllOperation()
{
	BinarySearchTree<int, int> object;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a BinarySearchTree.\n";
	cout << "2: search key in BinarySearchTree.\n";
	cout << "3: insert element into BinarySearchTree.\n";
	cout << "4: delete element from BinarySearchTree.\n";
	cout << "5: get BinarySearchTree's height.\n";
	cout << "6: print BinarySearchTree's contents.\n";
	cout << "7: destroy BinarySearchTree.\n";

	int operate;
	while(cin >> operate)
	{
		switch(operate)
		{
		case 0:
			goto END;
		case 1:
			object.Initialization();
			Output(object.root_);
			break;
		case 2:
			cout << "Please input your key:\n";
			int key;
			cin >> key;
			if(object.Search(key))
			{
				cout << "Find Successfully!\n";
			}
			else
			{
				cout << "Error: Can't Find!\n";
			}
			break;
		case 3:
			cout << "Please input your element:\n";
			int element;
			cin >> element;
			if(object.Insert(element))
			{
				Output(object.root_);
			}
			else
			{
				cout << "Error: Elements in binary search tree can't be duplicate!\n";
			}
			break;
		case 4:
			cout << "Please input your element:\n";
			cin >> key;
			if(object.Delete(key))
			{
				Output(object.root_);
			}
			else
			{
				cout << "Error: Can't find your key!\n";
			}
			break;
		case 5:
			cout << "Binary search tree's height is " << Height(object.root_) << endl;
			break;
		case 6:
			Output(object.root_);
			break;
		case 7:
			object.~BinarySearchTree();
			cout << "You have destroy the BinarySearchTree. "
			"Please establish BinarySearchTree before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}

#endif // BINARYSEARCHTREE_H_INCLUDED
