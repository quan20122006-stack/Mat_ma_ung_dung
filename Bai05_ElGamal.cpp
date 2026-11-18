#include<iostream>
#include<string>
using namespace std;

int main(){
    int p,a,XA,XB,P;
    int YA=1,YB=1,K=1,C,nghichDao=0;

    cout<<"Nhap p = ";cin>>p;
    cout<<"Nhap a = ";cin>>a;
    cout<<"Nhap XA = ";cin>>XA;
    cout<<"Nhap XB = ";cin>>XB;
    cout<<"Nhap P = ";cin>>P;

    if(p<3 || a<=0 || a>=p || XA<=0 || XB<=0 || P<0 || P>=p){
        cout<<"Du lieu khong hop le";
        return 0;
    }

    for(int i=1;i<=XA;i++){
        YA=(YA*a)%p;
    }

    for(int i=1;i<=XB;i++){
        YB=(YB*a)%p;
    }

    for(int i=1;i<=XA;i++){
        K=(K*YB)%p;
    }

    C=(K*P)%p;

    for(int i=1;i<p;i++){
        if((K*i)%p==1){
            nghichDao=i;
            break;
        }
    }

    if(nghichDao==0){
        cout<<"Khong co nghich dao";
        return 0;
    }

    cout<<"YA = "<<YA<<endl;
    cout<<"YB = "<<YB<<endl;
    cout<<"K = "<<K<<endl;
    cout<<"Ban ma C = "<<C<<endl;

    P=(C*nghichDao)%p;

    cout<<"Giai ma P = "<<P<<endl;

    return 0;
}

