#include<iostream>
#include<vector>
using namespace std;
const int M=100000;
int n,m,f[M],ch[M],jf;
vector<int>a[M],a1[M];

void dfs1(int v){
	ch[v]=1;
	for(int i=0;i<a1[v].size();i++)
		if(!ch[a1[v][i]])
			dfs1(a1[v][i]);
	f[jf++]=v;
}

void dfs(int v,int r){
	ch[v]=r;
	for(int i=0;i<a[v].size();i++)
		if(!ch[a[v][i]])
			dfs(a[v][i],r);
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;
		a[x-1].push_back(y-1);
		a1[y-1].push_back(x-1);
	}
	for(int i=0;i<n;i++)
		if(!ch[i])
			dfs1(i);
	memset(ch,0,sizeof ch);
	for(int i=n-1,j=0;i>=0;i--)
		if(!ch[f[i]])
			dfs(f[i],++j);
	for(int i=0;i<n-1;i++)
		cout<<ch[i]<<' ';
	cout<<ch[n-1]<<endl;
}
