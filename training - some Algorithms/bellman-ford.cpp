#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define N 1000
#define pb push_back
#define INF ( 1000*1000 )
int p[N],d[N],n,e;
vector<int> V[N];
int w[N][N];
bool relax(int u,int v,int w){
	bool c = ( d[v] > d[u] + w ) ;
	if ( c ){
		p[v] = u ;
		d[v] = d[u] + w ;
	}
	return c;
}
bool b_ford(){
	d[0] = 0 ;
	for ( int k = 0 ; k < n-1 ; k++)
		for ( int i = 0 ; i < n ; i++)
			for ( int j = 0 ; j < V[i].size() ; j++)
				relax(i,V[i][j],w[i][V[i][j]]);
}
int main(){
	cin >> n >> e;
	for ( int i = 0 ; i < e ; i++){
		int a,b,c;
		cin >> a>>b>>c;
		a--;b--;
		w[a][b] = c;
		V[a].pb(b);
	}
	fill(d,d+n,INF);
	b_ford();
	for ( int i = 0 ; i < n ; i++)
		cout << d[i] << ' ' ;
	cout << endl;
	return 0;
}

