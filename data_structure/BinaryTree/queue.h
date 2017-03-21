#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template<typename T>
class Queue;
template<typename T>
class Node
{
	friend class Queue<T>;
public:
	Node(T data, Node<T> *link): data_(data), link_(link) {}

private:
	T data_;
	Node<T> *link_;
};

template<typename T>
class Queue
{
public:
	Queue(): first_(nullptr), last_(nullptr) {};

	~Queue()
	{
		Node<T> *next;
		while(first_)
		{
			next = first_->link_;
			delete first_;
			first_ = next;
		}
		last_ = nullptr;
	}

	T Top()
	{
		if(first_)
		{
			return first_->data_;
		}
		return nullptr;
	}

	void Push(T data)
	{
		Node<T> *new_node = new Node<T> (data, nullptr);
		if(first_ == nullptr)
		{
			first_ = last_ = new_node;
		}
		else
		{
			last_->link_ = new_node;
			last_ = new_node;
		}
	}

	void Pop()
	{
		if(first_)
		{
			if(first_ == last_)
			{
				delete first_;
				first_ = last_ = nullptr;
			}
			else
			{
				Node<T> *next = first_->link_;
				delete first_;
				first_ = next;
			}
		}
	}

private:
	Node<T> *first_, *last_;
};

#endif // QUEUE_H_INCLUDED
