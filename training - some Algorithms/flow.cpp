
#include<iostream>
using namespace std;
const int M=1000+10,E=1000000000;
int a[M][M],saf[M],p[M],n,m,ch[M],s,t,ans;

void update(int v,int d){
	if(v!=s){
		a[p[v]][v]-=d;
		a[v][p[v]]+=d;
		update(p[v],d);
	}
	else
		ans+=d;
}

int find(int v){
	if(v!=s)
		return min(find(p[v]),a[p[v]][v]);
	return E;
}

int bfs(){
	memset(ch,0,sizeof ch);
	ch[s]=1;
	saf[0]=s;
	for(int mah=0,ins=1;mah<ins;mah++){
		int v=saf[mah];
		if(v==t)
			return 1;
		for(int i=0;i<n;i++)
			if(a[v][i]&&!ch[i]){
				ch[i]=1;
				saf[ins++]=i;
				p[i]=v;
			}
	}
	return 0;
}

void flow(){
	while(bfs())
		update(t,find(t));
}

int main(){
	cin>>n>>m>>s>>t;
	s--;t--;
	for(int i=0;i<m;i++){
		int x,y,d;
		cin>>x>>y>>d;
		a[x-1][y-1]+=d;
	}
	flow();
	cout<<ans<<endl;
}
