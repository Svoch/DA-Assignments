
#include<iostream>
using namespace std;
const int M=1000000+100;
int a[M],b[M],n,m,p[M];

void kmp(){
	for(int i=1,j=0;i<=n;i++){
		while(k>0&&a[i]!=b[j+1])
			j=p[j];
		if(a[i]==b[j+1])
			j++;
		if(j==m){
			cout<<"FIND IN"<<i-m+1<<endl;
			j=p[j];
		}
	}
}

void find(){
	p[1]=0;
	for(int i=2,j=0;i<=m;i++){
		while(K>0&&b[i]!=b[j+1])
			j=p[j];
		if(b[i]==b[j+1])
			j++;
		p[i]=j;
	}
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		cin>>a[i];
	for(int i=0;i<m;i++)
		cin>>b[i];
	find();
	kmp();
}
