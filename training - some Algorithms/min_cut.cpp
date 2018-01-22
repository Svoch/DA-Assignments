#include <iostream>
#include <cmath>
using namespace std;
#define N 1000
#define INF (1<<25)
int c[N][N],f[N][N],s,t,n;
bool mark[N];
int flow(int v,int Max){
	if ( v == t ) 
		return Max;
	if ( mark[v] )
		return 0;
	mark[v] = true;
	for ( int i = 0 ; i < n;  i++)if ( c[v][i] - f[v][i] ){
		int size = c[v][i] - f[v][i];
		int temp = 0 ;
		if ( temp = flow(i,min(Max,size))){
			f[v][i]+=temp;
			return temp;
		}
	}
	for ( int i = 0 ; i < n ; i++)if ( f[i][v]){
		int size = f[i][v];
		int temp = 0;
		if ( temp = flow(i,min(Max,size))){
			f[i][v]-=temp;
			return temp;
		}
	}
	return 0;
}
void dfs(int v){
	if ( mark[v])
		return;
	mark[v] = true;
	for ( int i = 0 ; i < n ; i++)
		if ( f[v][i])
			dfs(i);
}	
int main(){
	cin >> n >> s >> t;
	for ( int i = 0 ; i < n ; i++)
		for ( int j = 0 ; j < n ; j++)
			cin >> c[i][j];
	int temp=0;
	int ans=0;
	while ( temp = flow(s,INF)){
		ans+=temp;
		fill(mark,mark+n,false);
	}
	fill(mark,mark+n,false);
	dfs(s);
	for ( int i = 0 ; i < n ; i++)
		if (mark[i])
			cout << v+1 << ' ' ;
	cout << endl;
	return 0;
}

