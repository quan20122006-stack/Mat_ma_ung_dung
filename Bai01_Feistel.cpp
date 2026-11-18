#include<iostream>
#include<string>
using namespace std;

char F(char R, char K){
    return R+K;
}

string E(char K, string P){
    char L[3], R[3], C[3];
    L[0]=P[0];
    R[0]=P[1];
    int n=2;
    for(int i=1;i<=n;i++){
        L[i]=R[i-1];
        R[i]=L[i-1]^F(R[i-1],K);
    }
    C[0]=L[n];
    C[1]=R[n];
    return string(C,2);
}

string D(char K, string C){
    char L[3], R[3], P[3];
    L[2]=C[0];
    R[2]=C[1];
    for(int i=2;i>=1;i--){
        R[i-1]=L[i];
        L[i-1]=R[i]^F(L[i],K);
    }
    P[0]=L[0];
    P[1]=R[0];
    return string(P,2);
}

int main(){
    string P,C;
    char K;
    cout<<"Nhap 2 ky tu plaintext: ";
    getline(cin,P);
    cout<<"Nhap khoa K (1 ky tu): ";
    cin>>K;
    if(P.size()!=2){
        cout<<"Phai nhap dung 2 ky tu!";
        return 0;
    }
    C=E(K,P);
    cout<<"Ciphertext (ma ASCII): ";
    for(int i=0;i<2;i++) cout<<(int)(unsigned char)C[i]<<" ";
    cout<<endl;
    cout<<"Giai ma: "<<D(K,C)<<endl;
    return 0;
}
