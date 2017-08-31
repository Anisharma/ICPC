#include <iostream>
#include <bits/stdc++.h>
using namespace std ; 
bool cmp(const pair<pair<int, int > , int >& a ,const pair<pair<int, int > , int >& b  ){
	return a.second < b.second ; 
}
int parent(int ** arr , int a){
	if (arr[a][0] == -1)
	{
		return a ; 
	}
	arr[a][0] =  parent(arr , arr[a][0]) ; 
	return arr[a][0];
}
void union__(int ** arr , int x, int y){
	int xset = parent(arr , x) ; 
	int yset = parent(arr , y ) ; 
	if (arr[xset][1] > arr[yset][1] )
	{
		arr[yset][0] = xset ;
	}else if (arr[xset][1] < arr[yset][1])
	{
		arr[xset][0] = yset ; 
	}else if(arr[xset][1] == arr[yset][1]){
	arr[xset][0] = yset ;
	arr[yset][1] = arr[yset][1] +1 ;
	} 
}
bool checkSet(int ** arr , int x, int y){
	return (parent(arr , x)==parent(arr , y )) ; 
}
class Graphs
{
	int vertex ; 
	list<int> *adj ; 
	vector<pair<pair<int , int > , int > > edges;
	vector<vector<int> > scc;
public:
	Graphs(int v);
	void addEdge(int src, int dest , int weight);
	void DFS();
	void DFSTraversal(int i , bool *visited);
	int MSTinput(int airport , int * );
};
Graphs::Graphs(int v){
	this->vertex = v ; 
	adj = new list<int> [v]  ;
}
void Graphs::addEdge(int a, int b , int cost ){
	adj[a].push_back(b) ; 
	adj[b].push_back(a) ; 
	edges.push_back(make_pair(make_pair(a , b ) ,cost ));
}
void Graphs::DFSTraversal(int i , bool *visited){
	visited[i] = true ;
	list<int>::iterator it ; 
	scc[scc.size()-1].push_back(i);
	for(it = adj[i].begin() ; it != adj[i].end() ; it++){
		if (visited[*it] == false){
			DFSTraversal(*it , visited);
		}
	}
}
void Graphs::DFS(){
	bool * visited = new bool [vertex] ; 
	memset(visited , false , sizeof(visited));
	int j = 0  ;  
	for (int i = 0; i < vertex; ++i){
		if (visited[i] == false){
			std::vector<int> v;
			scc.push_back(v) ; 
			DFSTraversal(i , visited); 
		}
	}
}
int Graphs::MSTinput(int airport , int * air ){
	int cost = 0 ; 

	for (int i = 0; i < scc.size(); ++i){
		int indCost = 0 ; 
		bool * includedVertex = new bool [vertex];
		memset(includedVertex , false , sizeof(includedVertex));
		for(int j = 0 ; j < scc[i].size() ; j++){
			includedVertex[scc[i][j]] = true ; 
		}
		
		vector<pair<pair<int , int > , int > > incEdges; // will contains edges included in this strongly component
		for (int j = 0; j < edges.size() ; ++j)
		{
			int x = edges[j].first.first ; 
			int y = edges[j].first.second ; 
			if (includedVertex[x] == true && includedVertex[y] == true){
				incEdges.push_back(make_pair(make_pair(x , y ) ,edges[j].second ));
			}
		}
		sort(incEdges.begin() , incEdges.end() , cmp );
		// using krushkal with edges being in incEdges 
		int ** vertexMST = new int * [vertex] ;
		for (int i = 0; i < vertex; ++i){
			vertexMST[i] = new int [2] ;
		}
		for (int j = 0; j < vertex; ++j)
		{
			vertexMST[j][0] = -1 ;
			vertexMST[j][1] = 0 ; 
		}
		int pole = 0 ;
		for (int j = 0; j < incEdges.size(); ++j){
			if(!checkSet(vertexMST , incEdges[j].first.first , incEdges[j].first.second) && (incEdges[j].second < airport) ){
				union__(vertexMST ,incEdges[j].first.first  , incEdges[j].first.second ); 
				indCost += incEdges[j].second ; 
				includedVertex[incEdges[j].first.first] = false ;
				includedVertex[incEdges[j].first.second] = false ; 
			}
		}
		for (int j = 0; j < vertex; ++j){
			if (includedVertex[j] == true){
				indCost += airport ; 
				pole++ ;
				*air = *air + 1 ;  
			}
		}
		if (pole > 0){
		cost += indCost ; 
		}else{
			*air = *air+ 1 ;
			cost += indCost + airport ; 
		}
	}
	return cost ; 
}
int main(int argc, char const *argv[])
{
	int t ; 
	cin>>t ; 
	int k = 0 ;
	while(t>0){
		k++;
		int vertex , edges , costAir ; 
		cin>>vertex>>edges>>costAir ;
		Graphs g(vertex) ;  
		for (int i = 0; i < edges; ++i)
		{
			int a , b , cost; 
			cin>>a>>b>>cost ; 
			g.addEdge(a-1 ,b-1 , cost);
		}
		g.DFS();
		int air = 0 ;
		int ans = g.MSTinput(costAir, &air) ; 
		//cout<<ans<<" "<<air<<endl ; 
		cout<<"Case #"<<k<<": "<<ans<<" "<<air<<endl;
		t--; 
	}
	return 0;
}