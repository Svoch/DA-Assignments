#include <iostream>
#include <cmath>
using namespace std;
#define N 1000
#define INF ( 1<<25)
int c[N][N],f[N][N],c2[N][N],mark[N],n,s,t;

int flow(int v,int Max){
	if ( v == t )
		return Max;
	if ( mark[v] )
		return 0;
	for ( int i = 0 ; i < n ; i++)if ( c[v][i] - f[v][i] ){
		int size = c[v][i] - f[v][i];
		int temp = 0;
		if ( temp = flow( i , min ( Max, size))){
			f[v][i]+=temp;
			return temp;
		}
	}
	for ( int i = 0 ; i < n ; i++) if ( f[i][v] ){
		int size = f[i][v];
		int temp = 0;
		if ( temp = flow( i , min( Max,size))){
			f[i][v]-=temp;
			return temp;
		}
	}
	return 0;
}
int main(){
	cin >> n >> s >> t;
	int Max = 0 ;
	for (int i = 0 ; i < n ; i++)
		for ( int j = 0 ; j < n ; j++){
			cin >> c2[i][j];
			Max = max ( Max, c2[i][j] );
		}
	for ( int i = 0 ; i < n ; i++)
		for ( int j = 0 ; j < n ; j++)
			c[i][j] = ( c2[j][i] ? Max - c2[j][i]:0 ) ;
	for ( int i = 0 ; i < n ; i++){
		for ( int j = 0 ; j < n ; j++)
			cout << c[i][j] << ' ';
		cout << endl;
	}
	swap(s,t);	
	int temp = 0;
	int ans = 0;
	while ( temp = flow(s,INF)){
		ans+=temp;
		fill(mark,mark+n,false);
	}
	cout << Max - ans << endl;
	return 0;
}

