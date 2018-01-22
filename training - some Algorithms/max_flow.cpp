#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#define N 1000
#define pb push_back
#define INF ( 1 << 25 )
int c[N][N],f[N][N],mark[N],n,s,t;
int flow(int v,int Max){
	if ( v == t )
		return Max;
	if ( mark[v] )
		return 0;
	mark[v] = true;

	for ( int i = 0 ; i < n ; i++)
		if ( c[v][i] > f[v][i] ){
			int size = c[v][i] - f[v][i];
			int temp = 0 ;
			if ( temp = flow(i,min(Max,size))){
				f[v][i] += temp;
				return temp;
				}
			}
	for ( int i = 0 ; i < n ; i++)
		if ( f[i][v] ){
			int size = f[i][v];
			int temp = 0;
			if ( temp = flow(i,min(Max,size))){
				f[i][v]-=temp;
				return temp;
			}
		}
	return 0;
}
int main(){
	cin >> n >> s >> t;
	for ( int i = 0 ; i < n ; i++)
		for ( int j = 0 ; j < n ; j++)
			cin >> c[i][j];
	int ans = 0 ;
	int temp = 0;
	while ( temp = flow(s,INF)){
		ans+=temp;
		fill(mark,mark+n,false);
	}
	cout << ans << endl;
	return 0;
}

