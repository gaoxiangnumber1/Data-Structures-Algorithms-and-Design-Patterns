#ifndef CPPLIB_DS_BINARY_NODE_H_
#define CPPLIB_DS_BINARY_NODE_H_
#include "queue.h"
#include <stdio.h>

template<typename T>
struct BinaryNode
{
	BinaryNode(const T &data,
	           BinaryNode<T> *left = nullptr,
	           BinaryNode<T> *right = nullptr):
		data_(data), left_(left), right_(right) {}

	T data_;
	BinaryNode<T> *left_;
	BinaryNode<T> *right_;
};

template<typename T>
void PreOrderRecursive(BinaryNode<T> *root)
{
	if(root != nullptr)
	{
		Visit(root);
		PreOrderRecursive(root->left_);
		PreOrderRecursive(root->right_);
	}
}
template<typename T>
void InOrderRecursive(BinaryNode<T> *root)
{
	if(root != nullptr)
	{
		InOrderRecursive(root->left_);
		Visit(root);
		InOrderRecursive(root->right_);
	}
}
template<typename T>
void PostOrderRecursive(BinaryNode<T> *root)
{
	if(root != nullptr)
	{
		PostOrderRecursive(root->left_);
		PostOrderRecursive(root->right_);
		Visit(root);
	}
}
template<typename T>
void LevelOrder(BinaryNode<T> *root)
{
	Queue<BinaryNode<T>*> queue;
	queue.PushBack(root);
	BinaryNode<T> *node = queue.Front();
	while(node != nullptr)
	{
		Visit(node);
		if(node->left_ != nullptr)
		{
			queue.PushBack(node->left_);
		}
		if(node->right_ != nullptr)
		{
			queue.PushBack(node->right_);
		}
		queue.PopFront();
		node = queue.Front();
	}
}
template<typename T>
void Visit(BinaryNode<T> *node)
{
	printf("%d ", node->data_);
}
template<typename T>
void Delete(BinaryNode<T> *root)
{
	if(root != nullptr)
	{
		Delete(root->left_);
		Delete(root->right_);
		delete root;
	}
}
template<typename T>
int Height(BinaryNode<T> *root)
{
	if(root == nullptr)
	{
		return 0;
	}
	int left_height = Height(root->left_);
	int right_height = Height(root->right_);
	return left_height > right_height ? left_height + 1 : right_height + 1;
}
template<typename T>
int NodeCount(BinaryNode<T> *root)
{
	if(root == nullptr)
	{
		return 0;
	}
	return NodeCount(root->left_) + NodeCount(root->right_) + 1;
}
#endif // CPPLIB_DS_BINARY_NODE_H_
