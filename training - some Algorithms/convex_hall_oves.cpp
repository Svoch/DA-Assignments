#include<iostream>
#include<complex>
using namespace std;
typedef complex<double> point;
const int M=10000+100;
const double E=1e-7;
int n,ja;
point a[M],saf[M];
double ans;

int f(point p,point q){
	if(p.real()!=q.real())
		return p.real()<q.real();
	return p.imag()<q.imag();
}

double operator^(point p,point q){
	return p.real()*q.imag()-q.real()*p.imag();
}

void insert(point p){
	while(ja>2&&((saf[ja-2]-saf[ja-1])^(saf[ja-2]-p))>-E)
		ja--;
	saf[ja++]=p;
}

int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		double x,y;
		cin>>x>>y;
		a[i]=point(x,y);
	}
	sort(a,a+n,f);
	for(int i=0;i<n;i++)
		insert(a[i]);
	for(int i=n-1;i>=0;i--)
		insert(a[i]);
	for(int i=1;i<ja;i++){
		cerr<<saf[i-1]<<endl;
		ans+=abs(saf[i-1]-saf[i]);
	}
	cerr<<saf[ja-1]<<endl;
	cout<<ans<<endl;
}
