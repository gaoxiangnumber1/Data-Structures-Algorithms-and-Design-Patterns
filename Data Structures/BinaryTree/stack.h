#ifndef LinkedStack_H_INCLUDED
#define LinkedStack_H_INCLUDED

template<typename T>
class Stack;
template<typename T>
class StackNode
{
	friend class Stack<T>;
public:
	StackNode(T data, StackNode<T> *link): data_(data), link_(link) {}

private:
	T data_;
	StackNode<T> *link_;
};

template<typename T>
class Stack
{
public:
	Stack(): top_(nullptr) {};  // constructor

	~Stack()
	{
		StackNode<T> *next;
		while(top_)
		{
			next = top_->link_;
			delete top_;
			top_ = next;
		}
	}

	bool Empty() const
	{
		return top_ == 0;
	}

	T& Top() const
	{
		if(top_)
		{
			return top_->data_;
		}
	}

	void Push(const T &value)
	{
		StackNode<T> *new_node = new StackNode<T>(value, 0);
		new_node->link_ = top_;
		top_ = new_node;
	}

	void Pop()
	{
		if(top_ != 0)
		{
			StackNode<T> *new_top = top_->link_;
			delete top_;
			top_ = new_top;
		}
	}

private:
	StackNode<T> *top_;
};

#endif // LinkedStack_H_INCLUDED
