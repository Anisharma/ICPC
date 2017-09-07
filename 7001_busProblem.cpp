#include <iostream>
#include <bits/stdc++.h>
using namespace std ;
bool cmp(const pair<pair<int , int >, int > & a  ,const pair<pair<int , int >, int > & b  ){
	return a.second < b.second ;  
} 
int parent(int * arr, int x){
	if (arr[x] == -1)
	{
		return x ; 
	}
	return parent(arr , arr[x]) ; 
}
void union__(int * arr, int x, int y){
	int xset = parent(arr , x) ; 
	int yset = parent(arr , y) ; 
	arr[xset] = yset ; 
}
bool checkParent(int * arr , int x, int y){
	return (parent(arr , x) == parent(arr , y)) ; 
}
int main(int argc, char const *argv[])
{
	int t;
	cin>>t; 
	while(t>0){
		int vertex , edges ; 
		cin>>vertex>>edges ; 
		int MSTArray[vertex] ; 
		for (int i = 0; i < vertex; ++i){
			MSTArray[i] = -1 ; 
		}
		std::vector<pair<pair<int , int > ,int > > edge;
		for (int i = 0; i < edges; ++i){
			int src, dest , dist ; 
			cin>>src>>dest>>dist ; 
			edge.push_back(make_pair(make_pair(src , dest ) , dist)) ; 
		}
		sort(edge.begin() , edge.end() , cmp);
		int totalCost = 0 ; 
		int newCost = 0 ; 
		for (int i = 0; i < edges; ++i){
			int src, dest , dist ; 
			src = edge[i].first.first  ; 
			dest = edge[i].first.second ; 
			dist = edge[i].second ;  
			if (!(checkParent(MSTArray , src , dest))){
				union__(MSTArray , src , dest ) ;
				newCost += dist  ; 
			}
			totalCost += dist ; 
		}
		cout<<(totalCost - newCost)<<endl ; 
		t--; 
	} 	
	return 0;
}