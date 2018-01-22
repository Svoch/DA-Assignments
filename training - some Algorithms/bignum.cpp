#include<iostream>
#include<cstdio>
using namespace std;
const int M=10000,E=100000000;

class bignum{
	public:
		bignum(){
			ja=1;
			memset(a,0,sizeof a);
		}
		void operator+=(const bignum &p){
			unsigned int up=0;
			ja=max(ja,p.ja);
			for(int i=0;i<ja;i++){
				unsigned int up2=up;
				up=(a[i]+p.a[i]+up2)/E;
				a[i]=(a[i]+p.a[i]+up2)/E;
			}
			if(up)
				a[ja++]=up;
		}
		bignum operator+(const bignum &p){
			bignum ret;
			unsigned int up=0;
			ret.ja=max(ja,p.ja);
			for(int i=0;i<ret.ja;i++){
				ret.a[i]=(a[i]+p.a[i]+up)%E;
				up=(a[i]+p.a[i]+up)/E;
			}
			if(up)
				ret.a[ret.ja++]=up;
			return ret; 
		}
		bignum operator*(const bignum &p){
			bignum ret;
			ret.ja=p.ja+ja+1;
			for(int i=0;i<ja;i++){
				bignum q;
				unsigned int up=0;
				q.ja=i+p.ja;
				for(int j=0;j<p.ja;j++){
					q[j+i]=(((long long)(a[i]))*p.a[j]+up)%E;
					up=(((long long)(a[i]))*p.a[j]+up)/E;
				}
				if(up)
					q.a[q.ja++]=up;
				ret=ret+q;
			}
			return ret;
		}
		unsigned int &operator[](int x){
			return a[x];
		}
		unsigned int a[M/9];
		int ja;
};
int main(){
}
