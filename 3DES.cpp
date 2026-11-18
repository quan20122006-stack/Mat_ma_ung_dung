#include <bits/stdc++.h>
using namespace std;
char F(char R, char Ki)
{
    return R + Ki;
}
string E(char Ko, string P)
{
    char R[3], L[3], K[3];
    string C = "xx";
    L[0] = P[1];
    R[0] = P[0];
    K[0] = Ko;
    int n = 2;
    for (int i = 1; i <= n; i++)
    {
        K[i] = K[0] << i;
        R[i] = L[i - 1] ^ F(R[i - 1], K[i]);
        L[i] = R[i - 1];
    }
    C[0] = L[n];
    C[1] = R[n];
    return C;
}
string D(char Ko, string C)
{
    char R[3], L[3], K[3];
    string P = "xx";
    int n = 2;
    L[n] = C[0];
    R[n] = C[1];
    K[0] = Ko;
    for (int i = n; i >= 1; i--)
    {
        K[i] = K[0] << i;
        L[i - 1] = R[i] ^ F(L[i], K[i]);
        R[i - 1] = L[i];
    }
    P[0] = R[0];
    P[1] = L[0];
    return P;
}
int main()
{
    string P, C;
    char K1, K2, K3;
    cout << "Nhap khoi plaintext: ";
    getline(cin, P);
    cout << "Nhap K1: ";
    cin >> K1;
    cout << "Nhap K2: ";
    cin >> K2;
    cout << "Nhap K3: ";
    cin >> K3;
    C = E(K1, P);
    C = E(K2, C);
    C = E(K3, C);
    cout << "Ciphertext: " << C << endl;
    P = D(K3, C);
    P = D(K2, P);
    P = D(K1, P);
    cout << "Plaintext: " << P << endl;
}