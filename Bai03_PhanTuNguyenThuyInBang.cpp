#include<iostream>
using namespace std;
	int mu(int a, int m, int p){
		if(p==0) return 0;
		long long b=1;
		for(int i=1;i<=m;i++)
			b=(b*a)%p;
		return b;
	}
int main(){
	int p;
	cout<<"p = ";cin>>p;
	for(int a=1;a<p;a++){
		for(int i=1;i<p;i++) 	
			cout<< mu(a,i,p)<<" ";
			cout<<endl;
	}
}
