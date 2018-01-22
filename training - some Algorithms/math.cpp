
#include<iostream>
using namespace sd;
const int M=101+3;
const double E=1e-7;
double a[M][M+1];
int n,m,ch[M];

void soap(int p,int q){
	for(int i=0;i<m+1;i++)
		swap(a[p][i],a[q][i]);
}

void kam(int p,int q,double r){
	for(int i=0;i<m+1;i++)
		a[p][i]-=a[q][i]*r;
}

int main(){
	cin>>n>>m;
	for(int i=0;i<n;i++)
		for(int j=0;j<m+1;j++)
			cin>>a[i][j];
	int hed=0;
	for(int j=0;j<m;j++){
		int s=n;
		for(int i=n-1;i>=hed;i--)
			if(a[i][j]>E)
				s=i;
		if(s!=n){
			soap(hed,s);
			for(int k=hed+1;k<n;k++)
				if(a[k][j]>E)
					kam(k,hed,a[hed][j]/a[k][j]);
			hed++;
		}
		else{
			ch[j]=1;
		}
	}
}
