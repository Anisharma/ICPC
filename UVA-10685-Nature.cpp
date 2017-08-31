// lets just think of food chain as undirected graph , then the connected component having maximum number of vertex is the ans 
#include <iostream>
#include <bits/stdc++.h>
using namespace std ;
int max(int a, int b){
	return (a >b)?a:b ; 
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
	while(1){
		int x,y ; 
		cin>>x>>y ; 
		if (x == 0 && y == 0){
			break ;
		}
		std::map<string, int> mp;
		for (int i = 0; i < x; ++i){
			string str ; 
			cin>>str ; 
			mp[str] = i ; 
		}
		int * arr = new int [x] ; 
		for (int i = 0; i < x; ++i){
			arr[i] = -1 ; 
		}
		int *finalans = new int [x] ; 
		int * parentarr = new int [x] ;
		for (int i = 0; i < x; ++i){
			finalans[i] = 0 ; 
			parentarr[i] = -1 ;
		}
		for (int i = 0; i < y; ++i)
		{
			string str1 , str2 ; 
			cin>>str1>>str2 ; 
			int a = mp[str1] ; 
			int b = mp[str2] ; 
			if (!checkSet(arr , a , b) ){
				union__(arr , a , b) ; 
			}
		}
		int ans = 0 ;
		for (int i = 0; i < x; ++i)
		{
			parentarr[i] = parent(arr , i ) ;
			finalans[parentarr[i]] = finalans[parentarr[i]]+ 1 ;  
		}
		for (int i = 0; i < x; ++i)
		{
			ans = max(finalans[i], ans);
		}
		cout<<ans<<endl;
	}
	return 0;
}