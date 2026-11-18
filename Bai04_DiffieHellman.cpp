#include<iostream>
#include<string>
using namespace std;

int main(){
    int p,a,XA,XB,YA=1,YB=1,KA=1,KB=1;

    cout<<"Nhap p = ";cin>>p;
    cout<<"Nhap a = ";cin>>a;
    cout<<"Nhap XA = ";cin>>XA;
    cout<<"Nhap XB = ";cin>>XB;

    if(p<3 || a<=0 || a>=p || XA<=0 || XB<=0){
        cout<<"Du lieu khong hop le";
        return 0;
    }

    for(int i=1;i<=XA;i++){
        YA=(YA*a)%p;
    }

    for(int i=1;i<=XB;i++){
        YB=(YB*a)%p;
    }

    cout<<"YA = "<<YA<<endl;
    cout<<"YB = "<<YB<<endl;

    for(int i=1;i<=XA;i++){
        KA=(KA*YB)%p;
    }

    for(int i=1;i<=XB;i++){
        KB=(KB*YA)%p;
    }

    cout<<"Khoa chung cua A = "<<KA<<endl;
    cout<<"Khoa chung cua B = "<<KB<<endl;

    return 0;
}

