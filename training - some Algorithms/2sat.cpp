#include<iostream>
#include<vector>
using namespace std;
const int M=1000+100;
int ch[M],r[M],n,m;
vector<int>a[M];

int num(int v){
	if(v>0)
		return (v-1)*2;
	return (-v-1)*2+1;
}

int dfs(int v){
	ch[v]=1;
	for(int i=0;i<a[v].size();i++)
		if(a[v][i]&&!ch[i]){
			if(ch[i^1])
				return 0;
			if(!dfs(i))
				return 0;
		}
	return 1;
}

int main(){
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int x,y;
		cin>>x>>y;
		a[num(-x)].push_back(y);
		a[num(-y)].push_back(x);
	}
	for(int i=0;i<2*n;i+=2){
		if(!ch[i]&&!ch[i^1]){
		if(dfs(i))
			for(int i=0;i<2*n;i++)
				ch[i]+=(ch[i]==1);
		else{
			for(int i=0;i<2*n;i++)
				ch[i]-=(ch[i]==1);
			if(dfs(i^1))
				for(int i=0;i<2*n;i++)
					ch[i]+=(ch[i]==1);
			else{
				cout<<"NO ANS"<<endl;
				return 0;
			}
		}
		}
	}
	for(int i=0;i<2*n;i+=2)
		cout<<(ch[i]==2)<<' ';
	cout<<endl;
}
