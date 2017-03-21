#include "binary_node.h"

template<typename T>
class BinaryTree
{
public:
	BinaryTree(): root_(nullptr) {}
	~BinaryTree();

	void CreateCompleteBinaryTreeByLevel();
	void PreOrderRecursive() const;
	void InOrderRecursive() const;
	void PostOrderRecursive() const;
	void LevelOrder() const;
	void Height() const;
	void NodeCount() const;

private:
	BinaryNode<T> *root_;
};

template<typename T>
BinaryTree<T>::~BinaryTree()
{
	::Delete(root_);
	root_ = nullptr;
}
template<typename T>
void BinaryTree<T>::CreateCompleteBinaryTreeByLevel()
{
	int data_number;
	scanf("%d", &data_number);
	T data_array[data_number];
	for(int index = 0; index < data_number; ++index)
	{
		scanf("%d", &data_array[index]);
	}

	int data_index = 0;
	root_ = new BinaryNode<T>(data_array[data_index++]);
	Queue<BinaryNode<T>*> queue;
	queue.PushBack(root_);
	BinaryNode<T> *node = queue.Front();
	while(data_index < data_number)
	{
		node->left_ = new BinaryNode<T>(data_array[data_index++]);
		if(data_index < data_number)
		{
			node->right_ = new BinaryNode<T>(data_array[data_index++]);
		}
		queue.PushBack(node->left_);
		queue.PushBack(node->right_);
		queue.PopFront();
		node = queue.Front();
	}
}
template<typename T>
void BinaryTree<T>::PreOrderRecursive() const
{
	printf("PreOrder:   ");
	::PreOrderRecursive(root_);
	printf("\n");
}
template<typename T>
void BinaryTree<T>::InOrderRecursive() const
{
	printf("InOrder:    ");
	::InOrderRecursive(root_);
	printf("\n");
}
template<typename T>
void BinaryTree<T>::PostOrderRecursive() const
{
	printf("PostOrder:  ");
	::PostOrderRecursive(root_);
	printf("\n");
}
template<typename T>
void BinaryTree<T>::LevelOrder() const
{
	printf("LevelOrder: ");
	::LevelOrder(root_);
	printf("\n");
}
template<typename T>
void BinaryTree<T>::Height() const
{
	printf("Height:     %d\n", ::Height(root_));
}
template<typename T>
void BinaryTree<T>::NodeCount() const
{
	printf("NodeCount:  %d\n", ::NodeCount(root_));
}

int main()
{
	printf("0: Exit\n1: CreateCompleteBinaryTreeByLevel\n");
	int operation;
	while(scanf("%d", &operation) == 1)
	{
		BinaryTree<int> tree;
		switch(operation)
		{
		case 0:
			return 0;
		case 1:
			tree.CreateCompleteBinaryTreeByLevel();
			break;
		default:
			return 0;
		}
		tree.PreOrderRecursive();
		tree.InOrderRecursive();
		tree.PostOrderRecursive();
		tree.LevelOrder();
		tree.Height();
		tree.NodeCount();
	}
}
/*
1 7 1 2 3 4 5 6 7
1 2 4 5 3 6 7
4 2 5 1 6 3 7
4 5 2 6 7 3 1
1 2 3 4 5 6 7
*/
