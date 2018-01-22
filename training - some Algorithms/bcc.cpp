#include<iostream>
#include<vector>
using namespace std;
const int M=100000+10,E=(1<<30);
int p[M],n,m,up[M],ub[M],num[M],n,m;
vector<int>a[M];

void dfs(int v){
	ch[v]=1;
	for(int i=0;i<a[v].size();i++)
		if(!ch[a[v][i]]){
			p[a[v][i]]=v;
			num[a[v][i]]=num[v]+1;
			ch[a[v][i]]=1;
			dfs(a[v][i]);
			ub[v]=min(ub[v],min(ub[a[v][i]],up[a[v][i]]));
		}
		else if(a[v][i]!=a[v])
			up[v]=min(up[v],num[a[v][i]]);
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for(int i=0;i<n;i++)
		up=ub=E;
	dfs(0);
}
