#include<iostream>
#include<string>
using namespace std;

string RC4(string P,string K){
    unsigned char T[256],S[256];
    int i,j,t,k;
    // Khoi tao
    for(i=0;i<256;i++){
        T[i]=(unsigned char)K[i%K.size()];
        S[i]=i;
    }
    // Tao hoan vi S
    j=0;
    for(i=0;i<256;i++){
        j=(j+S[i]+T[i])%256;
        swap(S[i],S[j]);
    }
    // Sinh khoa luong va ma hoa
    i=0;
    j=0;
    string C="";
    for(int x=0;x<(int)P.size();x++){
        i=(i+1)%256;
        j=(j+S[i])%256;
        swap(S[i],S[j]);
        t=(S[i]+S[j])%256;
        k=S[t];
        C+=(char)((unsigned char)P[x]^k);
    }
    return C;
}

int main(){
    string P,K,C;
    cout<<"Nhap khoa K: ";
    getline(cin,K);
    if(K.size()==0){
        cout<<"Khoa khong duoc rong!";
        return 0;
    }
    cout<<"Nhap plaintext: ";
    getline(cin,P);
    C=RC4(P,K);
    cout<<"Ciphertext (ma ASCII): ";
    for(int i=0;i<(int)C.size();i++)
        cout<<(int)(unsigned char)C[i]<<" ";
    cout<<endl;
    cout<<"Giai ma: "<<RC4(C,K)<<endl;
    return 0;
}
