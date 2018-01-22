
#include<iostream>
#include<algorithm>
using namespace std;
const int M=100000+4,E=(1<<30);
int a[M],d[M],p[M],ki[M+1],n,m;

void chap(int v){
	if(p[v]!=-1)
		chap(p[v]);
	cout<<a[v]<<' ';
}

int main(){
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	d[0]=-1;
	ki[0]=-1;
	for(int i=1;i<=n;i++)
		d[i]=E;
	for(int i=0;i<n;i++){
		int j=upper_bound(d,d+n+1,a[i])-d;
		if(a[i]<d[j]){
			d[j]=a[i];
			ki[j]=i;
			p[i]=ki[j-1];
		}
	}
	for(int i=n;i>0;i--)
		if(d[i]!=E){
			cout<<i<<endl;
			chap(ki[i]);
			cout<<endl;
			return 0;
		}
}
