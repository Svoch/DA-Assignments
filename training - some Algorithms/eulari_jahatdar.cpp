
#include<iostream>
#include<vector>
using namespace std;
const int N=10000+100,M=1000000+100;
vector<int>a[N],a2[N];
int ch[N],p[N],ja[N],n,m;

void dfsp(int v){//cerr<<"p "<<v+1<<endl;
	ch[v]=1;
	for(int i=0;i<a2[v].size();i++)
		if(!ch[a2[v][i]]){
			p[a2[v][i]]=v;
			dfsp(a2[v][i]);
		}
}

void dfs(int v){
	cout<<v+1<<' ';
	for(int i=ja[v];i<a[v].size();i++){
		//cerr<<v<<' '<<a[v][i]<<' '<<p[v]<<endl;
		ja[v]++;
		if(a[v][i]!=p[v])
			dfs(a[v][i]);
	}
	if(p[v]!=-1)
		dfs(p[v]);
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++){
		int x,y;
		cin>>x>>y;
		x--;y--;
		a[x].push_back(y);
		a2[y].push_back(x);
	}
	for(int i=0;i<n;i++)
		if(a[i].size()!=a2[i].size()){
			cout<<"NO WAY"<<endl;
			return 0;
		}
	dfsp(0);
	p[0]=-1;
	for(int i=0;i<n;i++)
		if(!ch[i]){
			cout<<"NO WAY"<<endl;
			return 0;
		}
	dfs(0);
	cout<<endl;
}

