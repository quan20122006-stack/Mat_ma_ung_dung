
#include <iostream>
using namespace std;

int main() {
    int a, b, p;
    int dem = 0;

    cout << "Nhap a= "; cin >> a;
    cout << "Nhap b= "; cin >> b;
    cout << "Nhap p= "; cin >> p;

    if (p <= 3) {
        cout << "p phai la so nguyen to lon hon 3";
        return 0;
    }

    cout << "Cac diem tren duong cong la:\n";

    for (int x = 0; x < p; x++) {
        for (int y = 0; y < p; y++) {
            int VT = (y * y) % p;
            int VP = (x * x * x + a * x + b) % p;

            if (VP < 0) VP += p;

            if (VT == VP) {
                cout << "(" << x << "," << y << ")\n";
                dem++;
            }
        }
    }

    cout << "So diem huu han: " << dem << endl;
    cout << "Tong so diem (ke ca O): " << dem + 1;

    return 0;
}

