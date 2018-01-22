#include <iostream>
#include <vector>
using namespace std;
#define N 1000
#define pb push_back
#define INF ( 1000*1000 )
vector<int> V[N];
int w[N][N];
bool ch[N]={false};
int d[N],n,e;
void relax(int u,int v,int w){
	if ( d[v] > d[u] + w )
		d[v] = d[u]+w;
}
int i_min(){
	int min=INF;
	int in = 0 ;
	for ( int i = 0 ; i < n ; i++){
		if ( ch[i])
			continue;
		if ( min > d[i] ){
			in = i ;
			min = d[i];
		}
	}
	return in;
}
void dijesktra(){
	d[0] = 0 ;
	for ( int i = 0 ; i < n ; i++){
		int v = i_min();
		ch[v] = true;
		for ( int j = 0 ; j < V[v].size() ; j++)
			relax(v,V[v][j],w[v][V[v][j]]);
	}	
}
int main(){
	cin >> n >> e;
	for ( int i = 0 ; i < e;  i++){
		int a,b,c;
		cin >> a>>b>>c;
		a--;b--;
		V[a].pb(b);
		w[a][b] = c ;
	}
	fill(d,d+n,INF);
	dijesktra();
	for ( int i = 0 ; i < n ; i++)
		cout << d[i] << ' ';
	cout << endl;
	return 0;
}

