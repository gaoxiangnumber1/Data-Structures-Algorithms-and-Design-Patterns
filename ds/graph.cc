#include "graph_node.h"

template<typename T>
class Graph
{
public:
	Graph(): size_(0), graph_(nullptr) {}
	~Graph();

	void Create();
	void Insert(const T &src, const T &dest, int weight);
	void DFS();
	void BFS();

private:
	void Refresh();

	int size_;
	GraphNode<T> *graph_;
};

template<typename T>
Graph<T>::~Graph()
{
	for(int index = 0; index < size_; ++index)
	{
		GraphNode<T> *node = graph_[index].next_;
		while(node != nullptr)
		{
			GraphNode<T> *next = node->next_;
			delete node;
			node = next;
		}
	}
	delete [] graph_;
}
template<typename T>
void Graph<T>::Create()
{
	scanf("%d", &size_);
	graph_ = new GraphNode<T> [size_];
	for(int index = 0; index < size_; ++index)
	{
		graph_[index].data_ = index;
	}
	int edge_number;
	scanf("%d", &edge_number);
	while(edge_number-- > 0)
	{
		T src, dest;
		int weight;
		scanf("%d %d %d", &src, &dest, &weight);
		Insert(src, dest, weight);
	}
}
template<typename T>
void Graph<T>::Insert(const T &src, const T &dest, int weight)
{
	GraphNode<T> *new_node = new GraphNode<T>(dest, weight);
	GraphNode<T> *node = graph_[src].next_;
	if(node == nullptr || node->data_ > new_node->data_)
	{
		graph_[src].next_ = new_node;
		new_node->next_ = node;
	}
	else
	{
		while(node->data_ < new_node->data_ &&
		        node->next_ != nullptr &&
		        node->next_->data_ < new_node->data_)
		{
			node = node->next_;
		}
		new_node->next_ = node->next_;
		node->next_ = new_node;
	}
}
template<typename T>
void Graph<T>::DFS()
{
	printf("DFS: ");
	::DFS(0, graph_);
	printf("\n");
	Refresh();
}
template<typename T>
void Graph<T>::BFS()
{
	printf("BFS: ");
	::BFS(0, graph_);
	printf("\n");
	Refresh();
}
template<typename T>
void Graph<T>::Refresh()
{
	for(int index = 0; index < size_; ++index)
	{
		graph_[index].visited_ = false;
	}
}

int main()
{
	printf("0: Exit\n1: Create\n");
	Graph<int> graph;
	int op;
	while(scanf("%d", &op) == 1)
	{
		switch(op)
		{
		case 0:
			return 0;
		case 1:
			graph.Create();
			graph.DFS();
			graph.BFS();
			break;
		}
	}
}
/*
1 5 10
0 1 10
0 3 5
1 3 2
1 2 1
2 4 4
3 2 9
3 4 2
3 1 3
4 2 6
4 0 7
0
DFS: 0 1 2 4 3
BFS: 0 1 3 2 4
*/
