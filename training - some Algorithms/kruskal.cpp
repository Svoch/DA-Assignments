
#include<iostream>
#include<algorithm>
using namespace std;
const int M=100000;
class yal{
	public:
		int x,y,d;
		operator int(){
			return d;
		}
}y[M];
int n,m,size[M],p[M];

int jad(int v){
	if(v==p[v])
		return v;
	return p[v]=jad(p[v]);
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++)
		cin>>y[i].x>>y[i].y>>y[i].d;
	sort(y,y+m);
	for(int i=0;i<n;i++)
		p[i]=i;
	for(int i=0;i<m;i++){
		int p1=jad(y[i].x),p2=jad(y[i].y);
		if(p1!=p2){
			if(size[p1]<size[p2])
				p[p1]=p2;
			else if(size[p1]>size[p2])
				p[p2]=p1;
			else{
				p[p1]=p2;
				size[p1]++;
			}
			cout<<y[i].x<<' '<<y[i].y<<endl;
		}
	}
}
