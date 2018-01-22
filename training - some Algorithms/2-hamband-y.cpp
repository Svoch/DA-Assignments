#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define N 1000
#define pb push_back
int V[N][N];
int ch[N],p[N],part[N],n,e,t=1;
int dfs(int v){
	int ret = ch[v] = t;
	for ( int i = 0 ;i < n ; i++){
		if ( !V[v][i] )
			continue;
		t++;
		if ( !ch[i] ){
			p[i] = v;
			ret = min ( ret , dfs(i));
		}
		else if ( p[v] != i)
			ret = min ( ret , ch[i]);
		t--;
	}
	if ( ret == ch[v] && p[v] != -1){
		cout << p[v] + 1 << ':' << v+1 << endl;
		V[v][p[v]] = V[p[v]][v] = 0;
	}
	return ret;
}
void dfs1(int v){
	ch[v] = 1;
	part[v] = t;
	for ( int i = 0 ; i < n ; i++){
		if ( !V[v][i] )
			continue;
		if ( !ch[i])
			dfs1(i);
	}

}

int main(){
	cin >> n >> e ;
	for ( int i = 0 ; i < e ; i++){
		int a,b;
		cin >> a >> b;a--;b--;
		V[a][b] = 1;
		V[b][a] = 1;
	}
	for ( int i = 0 ; i < n ; i++)
		if ( !ch[i]){
			p[i] = -1;
			dfs(i);
			}
	fill(ch,ch+n,0);
	t=0;
	for ( int i = 0 ; i < n ; i++)
		if ( !ch[i]){
			p[i] = -1;
			dfs1(i);
			t++;
		}
	for ( int i = 0 ; i < n ; i++)
		cout << part[i] << ' ';
	cout << endl;
	return 0;
}


