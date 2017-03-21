#include <stdio.h>

template<typename T>
struct Node
{
	Node(const T &data, Node<T> *next = nullptr): data_(data), next_(next) {}

	T data_;
	Node<T> *next_;
};
