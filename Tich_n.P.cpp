#include <bits/stdc++.h>
using namespace std;
struct Diem
{
    int x, y;
};
struct Diem Tong(int Xp, int Yp, int Xq, int Yq, int a, int p)
{
    struct Diem R;
    int L, TS, MS;
    int MS1 = 0; // MS1 la nghich dao cua MS
    if (Xp == Xq && (Yp + Yq) % p == 0)
    { // 2 diem doi nhau
        R.x = -1;
        R.y = -1;
        return R; // Tong la diem O o vo cuc
    }
    else if (Xp == -1 && Yp == -1)
    {
        R.x = Xq;
        R.y = Yq;
        return R; // Tong P+Q la diem Q
    }
    else if (Xq == -1 && Yq == -1)
    {
        R.x = Xp;
        R.y = Yp;
        return R; // Tong P+Q la diem P
    }
    else if (Xp == Xq && Yp == Yq)
    {                               // 2 diem trung nhau
        TS = (3 * Xp * Xp + a) % p; // Tu so
        MS = (2 * Yp) % p;          // Mau so
        for (int i = 0; i < p; i++)
        {
            if (i * MS % p == 1)
            {
                MS1 = i;
                break;
            }
        }
    }
    else
    {
        TS = (Yq - Yp + p) % p;
        MS = (Xq - Xp + p) % p;
        for (int i = 0; i < p; i++)
        {
            if (i * MS % p == 1)
            {
                MS1 = i;
                break;
            }
        }
    }
    L = (TS * MS1) % p;
    R.x = (L * L - Xp - Xq + 2 * p) % p;
    R.y = (L * (Xp - R.x + p) % p - Yp + p) % p;
    return R;
}
int main()
{
    int Xp, Yp, n, a, p;
    cout << "Nhap Xp = ";
    cin >> Xp;
    cout << "Nhap Yp = ";
    cin >> Yp;
    cout << "Nhap n = ";
    cin >> n;
    cout << "Nhap a = ";
    cin >> a;
    cout << "Nhap p = ";
    cin >> p;
    struct Diem R; // neu n = 1 thi n.P = P
    R.x = Xp;
    R.y = Yp;
    int Xq = Xp;
    int Yq = Yp;
    for (int i = 2; i <= n; i++)
    {
        R = Tong(Xp, Yp, Xq, Yq, a, p);
        Xq = R.x;
        Yq = R.y;
    }
    cout << "(Xr, Yr) = (" << R.x << ", " << R.y << ")";
}