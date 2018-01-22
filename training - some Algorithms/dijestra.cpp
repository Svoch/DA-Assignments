#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N=1000+3,M=N*N,E=1000000000;

class ras{
	public:
		ras(int v=0,int d=E):v(v),d(d){};
		operator int(){
			return d;
		}
		int d,v;
}h[N+1];
vector<ras>a[N];
int n,m,ja[N],s,t,jh,ch[N];

void soap(int i,int j){
	swap(ja[h[i].v],ja[h[j].v]);
	swap(h[i],h[j]);
}

void bubup(int j){
	if(j>1&&h[j]<h[j/2]){
		soap(j,j/2);
		bubup(j/2);
	}
}

void bubdown(int j){
	int mn=j;
	if(2*j<jh&&h[2*j]<h[j])
		mn=2*j;
	if(2*j+1<jh&&h[2*j+1]<h[mn])
		mn=2*j+1;
	if(mn!=j){
		soap(mn,j);
		bubdown(mn);
	}
}

void del(){
	soap(1,--jh);
	bubdown(1);
}

int main(){
	cin>>n>>m>>s>>t;
	jh=n+1;
	s--;t--;
	for(int i=0;i<m;i++){
		int x,y,d;
		cin>>x>>y>>d;
		x--;y--;
		a[x].push_back(ras(y,d));
	}
	for(int i=0;i<n;i++){
		h[i+1].v=i;
		ja[i]=i+1;
	}
	h[ja[s]].d=0;
	bubup(ja[s]);
	for(int t=0;t<n;t++){
		int v=h[1].v,d=h[1].d;
		del();
		for(int i=0;i<a[v].size();i++){
			int u=a[v][i].v,dis=h[ja[u]];
			if(a[v][i].d+d<dis){
				h[ja[u]].d=a[v][i]+d;
				bubup(ja[u]);
			}
		}
	}
	cout<<h[ja[t]]<<endl;
}
