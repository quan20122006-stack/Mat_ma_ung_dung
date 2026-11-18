#include <bits/stdc++.h>
using namespace std;
int main()
{
    /*
    Lập trình tính số điểm có trên đường cong
    Ep(a,b), với a, b, p nhập từ bàn phím. Liệt
    kê các điểm của đường cong đó ra màn hình
    */
    int a, b, p, x, y, VT, VP, d = 0;
    cout << "Nhap a: ";
    cin >> a;
    cout << "Nhap b: ";
    cin >> b;
    cout << "Nhap p: ";
    cin >> p;
    for (x = 0; x < p; x++)
    {
        VP = (((x * x) % p * x) % p + (a * x) % p + b) % p;
        for (y = 0; y < p; y++)
        {
            VT = (y * y) % p;
            if (VT == VP)
            {
                d++;
                cout << d << ": (" << x << "," << y << ")" << endl;
            }
        }
    }
    cout << "Tong so diem tren duong cong(chua tinh diem O): " << d;
}