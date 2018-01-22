#include<iostream>
using namespace std;
const int M=500,E=1000000000;
int ans,ch[2*M],chm[2*M],mach[2*M],a[M][M],saf[M],p[2*M],n,m,w[2*M];

int update(int v){
	int u;
	chm[v]=1;
	while(v!=-1){
		u=p[v];
		mach[v]=u;
		mach[u]=v;
		v=p[u];
	}
	chm[u]=1;
}

int bfs(){
	memset(ch,0,sizeof ch);
	int ins=0;
	for(int i=0;i<n;i++)
		if(!chm[i]){
			p[i]=-1;
			ch[i]=1;
			saf[ins++]=i;
		}
	for(int mah=0;mah<ins;mah++){
		int v=saf[mah];
		for(int i=0;i<n;i++)
			if(!ch[i+n]&&a[v][i]==w[v]+w[i+n]){
				int u=i+n;
				ch[u]=1;
				p[u]=v;
				if(!chm[u])
					return u;
				int w=mach[u];
				p[w]=u;
				ch[w]=1;
				saf[ins++]=w;
			}
	}
	return -1;
}

int maching(){
	int v;
	while((v=bfs())!=-1)
		update(v);
	for(int i=0;i<2*n;i++)
		if(!chm[i])
			return 0;
	return 1;
}

int finde(){
	int e=E;
	for(int i=0;i<n;i++)
		if(ch[i])
			for(int j=0;j<n;j++)
				if(!ch[j+n])
					e=min(e,w[i]+w[n+j]-a[i][j]);
	return e;
}

void set(int e){
	for(int i=0;i<n;i++)
		if(ch[i])
			w[i]-=e;
	for(int i=n;i<2*n;i++)
		if(ch[i])
			w[i]+=e;
}

void wmaching(){
	while(!maching())
		set(finde());
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		w[i]=E;
	for(int i=0;i<m;i++){
		int x,y,d;
		cin>>x>>y>>d;
		a[x-1][y-1]=d;
	}
	wmaching();
	for(int i=0;i<n;i++)
		if(chm[i])
			ans+=a[i][mach[i]-n];
	cout<<ans<<endl;
	for(int i=0;i<n;i++)
		if(chm[i])
			cout<<i+1<<' '<<mach[i]-n+1<<endl;
}
