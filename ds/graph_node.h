#include "queue.h"
#include <stdio.h>

template<typename T>
struct GraphNode
{
	GraphNode(): data_(), weight_(0), visited_(false), next_(nullptr) {}
	GraphNode(const T &data, int weight = 0, GraphNode<T> *next = nullptr):
		data_(data),
		weight_(weight),
		visited_(false),
		next_(next)
	{}

	T data_;
	int weight_;
	bool visited_;
	GraphNode<T> *next_;
};

template<typename T>
void DFS(int index, GraphNode<T> *graph)
{
	if(graph[index].visited_ == false)
	{
		Visit(&graph[index]);
		graph[index].visited_ = true;
		for(GraphNode<T> *node = graph[index].next_; node != nullptr; node = node->next_)
		{
			DFS(node->data_, graph);
		}
	}
}
template<typename T>
void BFS(int index, GraphNode<T> *graph)
{
	Queue<GraphNode<T>*> queue;
	queue.PushBack(&graph[index]);
	graph[index].visited_ = true;
	while(queue.Empty() == false)
	{
		GraphNode<T> *root = queue.Front();
		queue.PopFront();
		Visit(root);
		for(GraphNode<T> *node = root->next_; node != nullptr; node = node->next_)
		{
			if(graph[node->data_].visited_ == false)
			{
				queue.PushBack(&graph[node->data_]);
				graph[node->data_].visited_ = true;
			}
		}
	}
}
template<typename T>
void Visit(const GraphNode<T> *root)
{
	printf("%d ", root->data_);
}
