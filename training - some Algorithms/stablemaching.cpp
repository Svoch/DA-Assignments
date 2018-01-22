
#include<iostream>
#include<cstdio>
using namespace std;
const int M=10000+100;
int n,saf[M],ja,p[M],a[M][M],how[M],b[M][M];

void send(int g,int man,int j){
	if(how[g]==-1){
		how[g]=man;
		saf[j]=saf[--ja];
	}
	if(a[g][how[g]]>a[g][man]){
		saf[j]=how[g];
		how[g]=man;
	}
}

int oneday(){
	if(!ja)
		return 0;
	for(int man=0;man<ja;man++)
		send(a[saf[man]][p[saf[man]]++],saf[man],man);
}

int main(){
	cin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			scanf("%d",&a[i][j]);
			a[i][j]--;
		}
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			int x;
			scanf("%d",&x);
			b[i][x-1]=j;
		}
	for(int i=0;i<n;i++){
		saf[ja++]=i;
		how[i]=-1;
	}
	while(oneday())
		;
	for(int i=0;i<n-1;i++)
		cout<<how[i]+1<<' ';
	cout<<how[n-1]+1<<endl;
}
