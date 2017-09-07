#include <iostream>
#include <bits/stdc++.h>
using namespace std ;
class Graph
{
 	int vertex ; 
 	list<int> * adj ; 
 	list<int> * adjTranspose ; 
 public:
 	Graph(int vertex);
 	void addEdge(int src , int dest) ; 
 	bool isStronglyConnected() ; 
 	void DFS(int x , bool * visited );
 	void DFSTranspose(int x , bool * visited );
 }; 
Graph::Graph(int v){
 	this->vertex = v ; 
 	adj = new list<int> [vertex]  ;
 	adjTranspose = new list<int> [vertex]  ;
}
void Graph::addEdge(int src , int dest){
	adj[src].push_back(dest);
	adjTranspose[dest].push_back(src) ; 
}
void Graph::DFS(int x , bool * visited ){
	visited[x] = true ; 
	list<int>::iterator it ; 
	for (it = adj[x].begin(); it != adj[x].end() ; ++it){
		if (visited[*it] == false){
			Graph::DFS(*it , visited ) ; 
		}
	} 
}
void Graph::DFSTranspose(int x , bool * visited ){
	visited[x] = true ; 
	list<int>::iterator it ; 
	for (it = adjTranspose[x].begin(); it != adjTranspose[x].end() ; ++it){
		if (visited[*it] == false){
			Graph::DFSTranspose(*it , visited ) ; 
		}
	} 
}

bool Graph::isStronglyConnected(){
	std::vector<int> topologicalSort;
	bool * visited = new bool[vertex] ; 
	for (int i = 0; i < vertex; ++i){
		visited[i] = false ;
	}
	DFS( 0 , visited );
	for (int i = 0; i < vertex; ++i){
		if (visited[i] == false){
			return false ; 
		}
	}
	for (int i = 0; i < vertex; ++i){
		visited[i] = false ; 
	}
	DFSTranspose( 0 , visited );
	for (int i = 0; i < vertex; ++i){
		if (visited[i] == false){
			return false ; 
		}
	}
	return true ; 
}
int main(){
	while(1){
		int vertex ,edges ; 
		cin>>vertex>>edges ; 
		if (vertex == 0 && edges == 0 ){
			break ; 
		}
		Graph g(vertex) ; 
		for (int i = 0; i < edges; ++i){
			int src, dest , check ; 
			cin>>src>>dest>>check ;
			src-- ; 
			dest--  ;  
			if (check == 1 ){
				g.addEdge(src , dest);
			}else if (check == 2){
				g.addEdge(src , dest ) ; 
				g.addEdge(dest , src ) ; 
			}
		}
		if (g.isStronglyConnected()){
			cout<<"1\n" ; 
		}else{
			cout<<"0\n";
		}
	}
	return  0 ; 
}