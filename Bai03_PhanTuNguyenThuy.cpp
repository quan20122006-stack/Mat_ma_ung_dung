#include<iostream>
#include<string>
using namespace std;

int main(){
    int p,a,i,j,x,dem;

    cout<<"Nhap p = ";
    cin>>p;

    if(p<2 || p>10000){
        cout<<"p khong hop le";
        return 0;
    }

    for(i=2;i*i<=p;i++){
        if(p%i==0){
            cout<<"p khong phai so nguyen to";
            return 0;
        }
    }

    cout<<"Cac phan tu nguyen thuy la: ";

    for(a=1;a<p;a++){
        x=1;
        dem=0;

        for(i=1;i<p;i++){
            x=(x*a)%p;

            if(x==1){
                dem=i;
                break;
            }
        }

        if(dem==p-1){
            cout<<a<<" ";
        }
    }

    return 0;
}

