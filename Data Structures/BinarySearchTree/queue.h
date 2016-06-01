#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template<typename T>
class Queue;
template<typename T>
class QueueNode
{
	friend class Queue<T>;
public:
	QueueNode(T data, QueueNode<T> *link): data_(data), link_(link) {}

private:
	T data_;
	QueueNode<T> *link_;
};

template<typename T>
class Queue
{
public:
	Queue(): first_(nullptr), last_(nullptr) {};
	~Queue()
	{
		QueueNode<T> *next;
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
		QueueNode<T> *new_node = new QueueNode<T> (data, nullptr);
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
				QueueNode<T> *next = first_->link_;
				delete first_;
				first_ = next;
			}
		}
	}

private:
	QueueNode<T> *first_, *last_;
};

#endif // QUEUE_H_INCLUDED
