#include <iostream>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
#define N 1000
#define INF 0xffff
#define pb push_back
vector<int> V[N];
int w[N][N];
int d[N],p[N];
bool ch[N]={false};
int n,e;
void relax(int u,int v){
	if ( d[v] > w[u][v]){
		p[v] = u;
		d[v] = w[u][v];
	}
}
int find_min(){
	int _min = INF;
	int in = 0;
	for ( int i = 0 ; i < n ; i++)
		if ( ch[i])
			continue;
		else if ( _min > d[i] ){
			_min = d[i];
			in = i;
		}
	return in;
}
void MST(){
	d[0] = 0;
	p[0] = -1;
	for ( int i = 0 ; i < n ; i++){
		int v = find_min();
		ch[v] = true;
		for ( int j = 0 ; j < V[v].size() ; j++)
			relax(v,V[v][j]);
	}
}
int main(){
	cin >>n >> e;
	fill(d,d+n,INF);
	for ( int i = 0 ; i < n ; i++)
		for ( int j = 0 ; j < n ; j++)
			w[i][j] = INF;
	for ( int i = 0 ; i < e ; i++){
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		V[a].pb(b);
		V[b].pb(a);
		w[a][b]=w[b][a] = c;
	}
	MST();
	for ( int i = 0 ; i < n ; i++)
		cout << d[i]<< ' ';
	cout << endl;
	for ( int i = 0 ; i < n ; i++)
		cout << p[i] << ' ';
	cout << endl;
	return 0;
}

