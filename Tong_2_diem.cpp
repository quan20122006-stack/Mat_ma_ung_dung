#include <bits/stdc++.h>
using namespace std;
int main()
{
    /*
    P(xP, yP) và Q(xQ, yQ) là 2 điểm khác nhau
    thuộc Ep(a,b). Lập trình nhập tọa độ 2 điểm
    rồi tính tổng 2 điểm đó, với p nhập từ bàn
    phím
    */
    int p, Xp, Yp, Xq, Yq;
    cout << "Nhap p: ";
    cin >> p;
    cout << "Nhap Xp: ";
    cin >> Xp;
    cout << "Nhap Yp: ";
    cin >> Yp;
    cout << "Nhap Xq: ";
    cin >> Xq;
    cout << "Nhap Yq: ";
    cin >> Yq;
    int L, TS, MS, MS1 = 0, Xr, Yr;
    TS = (Yq - Yp + p) % p;
    MS = (Xq - Xp + p) % p;
    for (int i = 1; i < p; i++)
    {
        if (i * MS % p == 1)
        {
            MS1 = i;
            break;
        }
    }
    L = (TS * MS1) % p;
    Xr = (L * L % p - Xp - Xq + p + p) % p;
    Yr = (L * (Xp - Xr + p) % p - Yp + p) % p;
    cout << "Xr=" << Xr << ", Yr=" << Yr;
}