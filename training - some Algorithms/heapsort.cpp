
#include<iostream>
using namespace std;
const int M=1000001,E=200000001;
int a[M],n,jh=1;

template<class T>
class heap{
	public:
		T &operator[](int x){
			return a[x];
		}
		T a[M];
};
heap<int>h;

template<class T>
void soap(T &a,T &b){
	T t=a;
	a=b;
	b=t;
}

template<class T>
void bubup(T j){
	if(j==1)
		return;
	if(h[j]<h[j/2]){
		soap(h[j],h[j/2]);
		bubup(j/2);
	}
}

template<class T>
void bubdown(T j){
	if(2*j>jh)
		return;
	else if(2*j==jh){
		if(h[jh-1]<h[j])
			soap(h[j],h[jh-1]);
	}
	else if(h[2*j]<h[2*j+1]){
		if(h[2*j]<h[j]){
			soap(h[j],h[2*j]);
			bubdown(2*j);
		}
	}
	else if(h[2*j+1]<h[j]){
			soap(h[j],h[2*j+1]);
			bubdown(2*j+1);
	}
}

template<class T>
void insert(T x){
	h[jh++]=x;
	bubup(jh-1);
}

template<class T>
void del(T j){
	h[j]=h[jh-1];
	jh--;
	bubdown(j);
}

template<class T>
void scan(T){
	for(int i=0;i<n;i++){
		T x;
		cin>>x;
		insert(x);
	}
}

int main(){
	cin>>n;
	scan(int());
	for(int i=0;i<n;i++){
		cout<<h[1]<<'\n';
		del(1);
	}
}
