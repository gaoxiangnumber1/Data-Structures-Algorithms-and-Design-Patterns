#ifndef BinaryTree_H_INCLUDED
#define BinaryTree_H_INCLUDED

#include "queue.h"
#include "stack.h"

using std::cout;
using std::cin;
using std::endl;
int g_create_index;  // index to create binary tree

template<typename T>
class BinaryTree;
template<typename T>
class BinaryTreeNode
{
public:
	BinaryTreeNode(T data, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right):
		data_(data), left_(left), right_(right) {}
	// to make access data conveniently
	T data_;
	BinaryTreeNode<T> *left_, *right_;
};

template<typename T>
class BinaryTree
{
	// create binary tree according preorder and inorder traversal
	template<T>	friend void CreateTreeByPreAndIn
	(BinaryTreeNode<T>* &root, T preorder[], T inorder[], int first, int last);
	// create binary tree according postorder and inorder traversal
	template<T> friend void CreateTreeByPostAndIn
	(BinaryTreeNode<T>* &root, T postorder[], T inorder[], int first, int last);
	template<T>	friend void PreorderRecursive(BinaryTreeNode<T> *root);  // pre-order traversal
	template<T> friend void PreorderLoop(BinaryTreeNode<T> *root);
	template<T>	friend void InorderRecursive(BinaryTreeNode<T> *root);  // in-order traversal
	template<T> friend void InorderLoop(BinaryTreeNode<T> *root);
	template<T>	friend void PostorderRecursive(BinaryTreeNode<T> *root);  // post-order traversal
	template<T> friend void PostorderLoop(BinaryTreeNode<T> *root);
	template<T>	friend void Levelorder(BinaryTreeNode<T> *root);  // level-order traversal
	template<T>	friend void Delete(BinaryTreeNode<T>* &root);  // free a binary tree's memory
	template<T>	friend int Height(BinaryTreeNode<T> *root);  // get tree's height
	template<T>	friend void NodeCount(int &node_count, BinaryTreeNode<T> *node);  // get nodes' amount

public:
	BinaryTree(): root_(nullptr) {}  // default constructor
	~BinaryTree();  // destructor
	void Initialization();
	bool IsEmpty();  // check whether the binary tree is empty

	BinaryTreeNode<T> *root_;
};

template<typename T>
void BinaryTree<T>::Initialization()
{
	cout << "Please input elements's amount:\n";
	int amount;
	cin >> amount;
	T inorder[amount];
	cout << "Please input elements in in-order:\n";
	for(int index = 0; index < amount; index++)
	{
		cin >> inorder[index];
	}
	cout << "input 1 to use pre-order to create binary tree; 2 to use post-order.\n";
	int choose;
	cin >> choose;
	if(choose == 1)
	{
		T preorder[amount];
		cout << "Please input elements in pre-order:\n";
		for(int index = 0; index < amount; index++)
		{
			cin >> preorder[index];
		}
		g_create_index = 0;
		CreateTreeByPreAndIn(root_, preorder, inorder, 0, amount - 1);
	}
	else
	{
		T postorder[amount];
		cout << "Please input elements in post-order:\n";
		for(int index = 0; index < amount; index++)
		{
			cin >> postorder[index];
		}
		g_create_index = amount - 1;
		CreateTreeByPostAndIn(root_, postorder, inorder, 0, amount - 1);
	}
}

template<typename T>
void CreateTreeByPreAndIn(BinaryTreeNode<T>* &root, T preorder[], T inorder[], int first, int last)
{
	if(first > last)
	{
		root = nullptr;
		return;
		// Note: we must use "return" in all "if" clause or use "else if" since if we omit "return",
		// then the change in one "if" cluase will cause undefined result in other "if".
	}
	if(first == last)
	{
		root = new BinaryTreeNode<T> (preorder[g_create_index], nullptr, nullptr);
		g_create_index++;
		return;
	}
	if(first < last)
	{
		int position;
		for(position = first; position <= last; position++)
		{
			if(preorder[g_create_index] == inorder[position])
			{
				break;
			}
		}
		root = new BinaryTreeNode<T> (preorder[g_create_index], nullptr, nullptr);
		g_create_index++;
		CreateTreeByPreAndIn(root->left_, preorder, inorder, first, position - 1);
		CreateTreeByPreAndIn(root->right_, preorder, inorder, position + 1, last);
	}
}

template<typename T>
void CreateTreeByPostAndIn(BinaryTreeNode<T>* &root, T postorder[], T inorder[], int first, int last)
{
	if(first > last)
	{
		root = nullptr;
		return;
	}
	if(first == last)
	{
		root = new BinaryTreeNode<T> (postorder[g_create_index], nullptr, nullptr);
		g_create_index--;
	}
	if(first < last)
	{
		int position;
		for(position = first; position <= last; position++)
		{
			if(postorder[g_create_index] == inorder[position])
			{
				break;
			}
		}
		root = new BinaryTreeNode<T> (postorder[g_create_index], nullptr, nullptr);
		g_create_index--;
		CreateTreeByPostAndIn(root->right_, postorder, inorder, position + 1, last);
		CreateTreeByPostAndIn(root->left_, postorder, inorder, first, position - 1);
	}
}

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	Delete(root_);
}

template<typename T>
bool BinaryTree<T>::IsEmpty()
{
	return root_ == nullptr;
}

template<typename T>
void PreorderRecursive(BinaryTreeNode<T> *root)  // root->left->right
{
	if(root)
	{
		cout << root->data_ << " ";
		PreorderRecursive(root->left_);
		PreorderRecursive(root->right_);
	}
}

template<typename T>
void PreorderLoop(BinaryTreeNode<T> *root)
{
	Stack<BinaryTreeNode<T>* > node_stack;
	while(!node_stack.Empty() || root)  // either the stack is not empty or the root is not null
	{
		while(root)
		{
			cout << root->data_ << " ";  // access the root node
			node_stack.Push(root);  // push root into stack
			root = root->left_;  // access the left child node
		}
		// up to now, we have accessed all nodes and their left children which are in stack
		root = node_stack.Top();  // root can't have left child, but may has right child.
		node_stack.Pop();
		root = root->right_;  // make its right child as root, if any
	}
}

template<typename T>
void InorderRecursive(BinaryTreeNode<T> *root)  // left->root->right
{
	if(root)
	{
		InorderRecursive(root->left_);
		cout << root->data_ << " ";
		InorderRecursive(root->right_);
	}
}

template<typename T>
void InorderLoop(BinaryTreeNode<T> *root)
{
	Stack<BinaryTreeNode<T>* > node_stack;
	while(!node_stack.Empty() || root)  // either the stack is not empty or the root is not null
	{
		while(root)
		{
			node_stack.Push(root);
			root = root->left_;
		}
		root = node_stack.Top();  // root can't have left child, but may has right child.
		node_stack.Pop();
		cout << root->data_ << " ";  // access the root node
		root = root->right_;  // make its right child as root, if any
	}
}

template<typename T>
void PostorderRecursive(BinaryTreeNode<T> *root)  // left->right->root
{
	if(root)
	{
		PostorderRecursive(root->left_);
		PostorderRecursive(root->right_);
		cout << root->data_ << " ";
	}
}

template<typename T>
void PostorderLoop(BinaryTreeNode<T> *root)
{
	// in binary tree's postorder traverse, the root won't be accessed until
	// all its children are accessed, so we use one more stack to solve.
	Stack<BinaryTreeNode<T>* > node_stack;  // store tree's nodes
	// store the accessed number of corresponding nodes in node_stack,
	// i.e., count_stack.Top() is the accessed number of node_stack.Top()
	Stack<int> count_stack;
	while(!node_stack.Empty() || root)
	{
		while(root)
		{
			node_stack.Push(root);
			count_stack.Push(1);  // the 1st accessed time
			root = root->left_;
		}

		if(!count_stack.Empty())
		{
			if(count_stack.Top() == 1)  // if we access current top node once
			{
				root = node_stack.Top();  // access the root for the 2nd time
				count_stack.Top() = 2;  // update accessed number
				root = root->right_;  // access its right child, if any
			}
			else  // we have accessed the current top node for 2 times
			{
				root = node_stack.Top();  // access the root for the 3rd time
				node_stack.Pop();  // delete the root
				count_stack.Pop();  // delete root's accessed number
				cout << root->data_ << " ";
				root = 0;  // NOTE: we must make the root as null pointer!
			}
		}
	}
}

template<typename T>
void Levelorder(BinaryTreeNode<T> *root)  // from top to bottom; from left to right
{
	Queue<BinaryTreeNode<T> *> queue;  // use queue data structure
	queue.Push(root);
	BinaryTreeNode<T> *node = queue.Top();  // get current top node of queue
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
}

template<typename T>
void Delete(BinaryTreeNode<T>* &root)
{
	// free all nodes in post order: left->right->root
	if(root)
	{
		Delete(root->left_);
		Delete(root->right_);
		delete root;
		root = nullptr;  // avoid dangling pointer
	}
}

template<typename T>
int Height(BinaryTreeNode<T> *root)
{
	if(root)
	{
		int left = Height(root->left_);  // get left-subtree's height
		int right = Height(root->right_);  // get right-subtree's height
		return (left > right) ? ++left : ++right;  // return max(left, right) + 1(root's height = 1)
	}
	return 0;
}

template<typename T>
void NodeCount(int &node_count, BinaryTreeNode<T> *node)
{
	if(node)
	{
		node_count++;
		NodeCount(node_count, node->left_);
		NodeCount(node_count, node->right_);
	}
}

void AllOperation()
{
	BinaryTree<char> object;
	cout << "Please some numbers to execute the corresponding operation:\n";
	cout << "0: exit.\n";
	cout << "1: create a binary tree.\n";
	cout << "2: check whether binary tree is empty.\n";
	cout << "3: Preorder Recursive\n";
	cout << "4: Preorder Loop\n";
	cout << "5: Inorder Recursive\n";
	cout << "6: Inorder Loop\n";
	cout << "7: Postorder Recursive\n";
	cout << "8: Postorder Loop\n";
	cout << "9: output binary tree's elements in level-order traversal\n";
	cout << "10: get binary tree's height.\n";
	cout << "11: get binary tree's node number.\n";
	cout << "12: destroy binary tree.\n";

	int operate;
	while(cin >> operate)
	{
		switch(operate)
		{
		case 0:
			goto END;
		case 1:
			object.Initialization();
			break;
		case 2:
			if(object.IsEmpty())
			{
				cout <<"BinaryTree is empty.\n";
			}
			else
			{
				cout <<"BinaryTree is not empty.\n";
			}
			break;
		case 3:
			PreorderRecursive(object.root_);
			cout << endl;
			break;
		case 4:
			PreorderLoop(object.root_);
			cout << endl;
			break;
		case 5:
			InorderRecursive(object.root_);
			cout << endl;
			break;
		case 6:
			InorderLoop(object.root_);
			cout << endl;
			break;
		case 7:
			PostorderRecursive(object.root_);
			cout << endl;
			break;
		case 8:
			PostorderLoop(object.root_);
			cout << endl;
			break;
		case 9:
			Levelorder(object.root_);
			cout << endl;
			break;
		case 10:
			cout << "The height is " << Height(object.root_) << endl;
			break;
		case 11:
			int node_count;
			node_count = 0;
			NodeCount(node_count, object.root_);
			cout << "The node's amount is " << node_count << endl;
			break;
		case 12:
			object.~BinaryTree();
			cout << "You have destroy the BinaryTree. Please establish BinaryTree before executing operations.\n";
			break;
		default:
			cout << "Input Error! Please input again!\n";
			break;
		}
	}
END:
	;
}

#endif // BinaryTree_H_INCLUDED
