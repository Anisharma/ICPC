#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std ; 
bool cmp(const pair<pair<int, int > , int >& a ,const pair<pair<int, int > , int >& b  ){
	return a.second < b.second ; 
}
int parent(int * arr ,  int x){
	if (arr[x] == -1){
		return x ; 
	}
	arr[x] =  parent(arr , arr[x]);
	return arr[x] ; 
} 
void union__(int * arr, int x , int y){
	int xset = parent(arr , x) ; 
	int yset = parent(arr , y) ; 
	arr[xset] = yset ; 
}
int checkSet(int * arr , int x, int y){
	return (parent(arr , x) == parent(arr , y ));
}
int main(int argc, char const *argv[])
{
	int t ; 
	cin>>t ; 
	while(t>0){
		int n ; 
		cin>>n ; 
		std::vector<pair<double , double > > vertex;
		for (int i = 0; i < n; ++i){
			double x ,y  ; 
			cin>>x>>y ; 
			vertex.push_back(make_pair(x, y )) ; 
		}
		std::vector<pair<pair<int , int> , double > > edges;
		for (int i = 0; i < vertex.size(); ++i){
			for (int j = 0; j < vertex.size(); ++j){
				if (i != j ){
					double dis = sqrt(pow(abs(vertex[i].first - vertex[j].first) , 2) + pow(abs(vertex[i].second - vertex[j].second) , 2)) ; 
					edges.push_back(make_pair(make_pair(i , j ) ,dis ));
				}
			}
		}
		sort(edges.begin() , edges.end() , cmp);
		double ans = 0 ; 
		int * arr = new int [n] ; 
		for (int i = 0; i < n; ++i){
			arr[i] = -1 ; 
		}
		for (int i = 0; i < edges.size(); ++i){
			if (!checkSet(arr , edges[i].first.first ,edges[i].first.second)){
				union__(arr , edges[i].first.first ,edges[i].first.second ) ; 
				ans += edges[i].second ; 
			}
		}
		cout<<setprecision(2) << std::fixed <<ans<<endl;
		t--; 
	}
	return 0;
}