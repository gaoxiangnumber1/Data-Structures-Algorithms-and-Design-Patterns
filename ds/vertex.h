#ifndef CPPLIB_DS_VERTEX_H_
#define CPPLIB_DS_VERTEX_H_

#include "queue.h"

template<typename T>
struct Vertex
{
	Vertex():
		index_(),
		weight_(0),
		in_degree_(0),
		out_degree_(0),
		visited_(false),
		next_(nullptr)
	{}
	Vertex(const T &data, int weight = 0, Vertex<T> *next = nullptr):
		index_(data),
		weight_(weight),
		in_degree_(0),
		out_degree_(0),
		visited_(false),
		next_(next)
	{}

	T index_;
	int weight_;
	int in_degree_;
	int out_degree_;
	bool visited_;
	Vertex<T> *next_;
};

template<typename T>
void DFS(int index, Vertex<T> *graph)
{
	if(graph[index].visited_ == false)
	{
		Visit(&graph[index]);
		graph[index].visited_ = true;
		for(Vertex<T> *node = graph[index].next_; node != nullptr; node = node->next_)
		{
			DFS(node->index_, graph);
		}
	}
}
template<typename T>
void BFS(int index, Vertex<T> *graph)
{
	Queue<Vertex<T>*> queue;
	queue.PushBack(&graph[index]);
	graph[index].visited_ = true;
	while(queue.Empty() == false)
	{
		Vertex<T> *root = queue.Front();
		queue.PopFront();
		Visit(root);
		for(Vertex<T> *node = root->next_; node != nullptr; node = node->next_)
		{
			if(graph[node->index_].visited_ == false)
			{
				queue.PushBack(&graph[node->index_]);
				graph[node->index_].visited_ = true;
			}
		}
	}
}
template<typename T>
void Visit(const Vertex<T> *root)
{
	printf("%d ", root->index_);
}
#endif // CPPLIB_DS_VERTEX_H_
