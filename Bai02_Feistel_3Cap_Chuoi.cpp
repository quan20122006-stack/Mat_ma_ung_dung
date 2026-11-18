#include<iostream>
#include<string>
using namespace std;

char F(char R,char K){
    return R+K;
}

string E(char K,string P){
    char L[3],R[3],C[3];
    L[0]=P[0];
    R[0]=P[1];
    for(int i=1;i<=2;i++){
        L[i]=R[i-1];
        R[i]=L[i-1]^F(R[i-1],K);
    }
    C[0]=L[2];
    C[1]=R[2];
    return string(C,2);
}

string D(char K,string C){
    char L[3],R[3],P[3];
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

string Efull(string P,char K1,char K2,char K3){
    if(P.size()%2!=0) P+=' ';
    string Cipher="";
    for(int i=0;i<(int)P.size();i+=2){
        string p=P.substr(i,2);
        string C=E(K1,p);
        C=E(K2,C);
        C=E(K3,C);
        Cipher+=C;
    }
    return Cipher;
}

string Dfull(string C,char K1,char K2,char K3){
    string P="";
    for(int i=0;i<(int)C.size();i+=2){
        string p=C.substr(i,2);
        p=D(K3,p);
        p=D(K2,p);
        p=D(K1,p);
        P+=p;
    }
    return P;
}

int main(){
    string P,C;
    char K1,K2,K3;
    cout<<"Nhap K1 K2 K3: ";
    cin>>K1>>K2>>K3;
    cin.ignore();
    cout<<"Nhap plaintext: ";
    getline(cin,P);
    C=Efull(P,K1,K2,K3);
    cout<<"Ciphertext (ma ASCII): ";
    for(int i=0;i<(int)C.size();i++)
        cout<<(int)(unsigned char)C[i]<<" ";
    cout<<endl;
    cout<<"Giai ma: "<<Dfull(C,K1,K2,K3)<<endl;
    return 0;
}
