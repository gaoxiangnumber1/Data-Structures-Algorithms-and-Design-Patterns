#include "vertex.h"

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
	void TopologicalSort();

private:
	void Refresh();

	int size_;
	Vertex<T> *graph_;
};

template<typename T>
Graph<T>::~Graph()
{
	for(int index = 0; index < size_; ++index)
	{
		Vertex<T> *vertex = graph_[index].next_;
		while(vertex != nullptr)
		{
			Vertex<T> *next = vertex->next_;
			delete vertex;
			vertex = next;
		}
	}
	delete [] graph_;
}
template<typename T>
void Graph<T>::Create()
{
	scanf("%d", &size_);
	graph_ = new Vertex<T> [size_];
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
	Vertex<T> *new_node = new Vertex<T>(dest, weight);
	Vertex<T> *vertex = graph_[src].next_;
	if(vertex == nullptr || vertex->data_ > new_node->data_)
	{
		graph_[src].next_ = new_node;
		new_node->next_ = vertex;
	}
	else
	{
		while(vertex->data_ < new_node->data_ &&
		        vertex->next_ != nullptr &&
		        vertex->next_->data_ < new_node->data_)
		{
			vertex = vertex->next_;
		}
		new_node->next_ = vertex->next_;
		vertex->next_ = new_node;
	}
	++graph_[src].out_degree_;
	++graph_[dest].in_degree_;
}
template<typename T>
void Graph<T>::DFS()
{
	printf("DFS: ");
	::DFS(0, graph_);
	Refresh();
}
template<typename T>
void Graph<T>::BFS()
{
	printf("BFS: ");
	::BFS(0, graph_);
	Refresh();
}
template<typename T>
void Graph<T>::TopologicalSort()
{
	printf("TLS: ");
	T data[size_];
	int sorted_index = -1;
	for(int index = 0; index < size_; ++index)
	{
		if(graph_[index].visited_ == false && graph_[index].in_degree_ == 0)
		{
			data[++sorted_index] = index;
			printf("%d ", data[sorted_index]);
			graph_[index].visited_ = true;
		}
	}
	int process_index = 0;
	while(sorted_index < size_ - 1)
	{
		for(; process_index <= sorted_index; ++process_index)
		{
			for(Vertex<T> *vertex = graph_[data[process_index]].next_;
			        vertex != nullptr;
			        vertex = vertex->next_)
			{
				--graph_[data[process_index]].out_degree_;
				if(--graph_[vertex->data_].in_degree_ == 0 &&
				        graph_[vertex->data_].visited_ == false)
				{
					data[++sorted_index] = vertex->data_;
					printf("%d ", data[sorted_index]);
					graph_[vertex->data_].visited_ = true;
				}
			}
		}
	}
	Refresh();
}
template<typename T>
void Graph<T>::Refresh()
{
	for(int index = 0; index < size_; ++index)
	{
		graph_[index].visited_ = false;
		graph_[index].in_degree_ = 0;
		graph_[index].out_degree_ = 0;
	}
	for(int index = 0; index < size_; ++index)
	{
		for(Vertex<T> *vertex = graph_[index].next_; vertex != nullptr; vertex = vertex->next_)
		{
			++graph_[index].out_degree_;
			++graph_[vertex->data_].in_degree_;
		}
	}
	printf("\n");
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
			break;
		}
		graph.DFS();
		graph.BFS();
		graph.TopologicalSort();
	}
}
/*
1 5 7
0 1 10
0 3 5
1 2 1
3 2 9
3 4 2
3 1 3
4 2 6
0
DFS: 0 1 2 4 3
BFS: 0 1 3 2 4
TLS: 0 3 1 4 2
*/
