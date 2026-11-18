#include<iostream>
#include<string>
using namespace std;

int main(){
    int p,q,n,phi,e,d=0,P,C=1,M=1;

    cout<<"Nhap p = ";cin>>p;
    cout<<"Nhap q = ";cin>>q;

    n=p*q;
    phi=(p-1)*(q-1);

    cout<<"n = "<<n<<endl;
    cout<<"phi = "<<phi<<endl;

    cout<<"Nhap e = ";cin>>e;

    for(int i=1;i<phi;i++){
        if((e*i)%phi==1){
            d=i;
            break;
        }
    }

    if(d==0){
        cout<<"e khong hop le!";
        return 0;
    }

    cout<<"Khoa cong khai: ("<<e<<","<<n<<")"<<endl;
    cout<<"Khoa bi mat: ("<<d<<","<<n<<")"<<endl;

    cout<<"Nhap ban ro P = ";cin>>P;

    if(P<0 || P>=n){
        cout<<"P phai nam trong [0,n-1]";
        return 0;
    }

    for(int i=1;i<=e;i++){
        C=(C*P)%n;
    }

    cout<<"Ban ma C = "<<C<<endl;

    for(int i=1;i<=d;i++){
        M=(M*C)%n;
    }

    cout<<"Giai ma M = "<<M<<endl;

    return 0;
}

