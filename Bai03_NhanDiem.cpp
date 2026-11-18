
#include <iostream>
using namespace std;

int p, a;

int mod(long long x) {
    return (x % p + p) % p;
}

int nghich(int x) {
    for (int i = 1; i < p; i++) {
        if (mod(1LL * x * i) == 1)
            return i;
    }
    return -1;
}

struct Diem {
    int x, y;
};

Diem Tong(Diem P, Diem Q) {
    Diem R;
    int tu, mau, k;

    // Neu P la diem O
    if (P.x == -1) return Q;
    if (Q.x == -1) return P;

    // Hai diem doi nhau
    if (P.x == Q.x && mod(P.y + Q.y) == 0)
        return {-1, -1};

    // Hai diem trung nhau
    if (P.x == Q.x && P.y == Q.y) {
        tu = mod(3LL * P.x * P.x + a);
        mau = mod(2LL * P.y);
    }
    else {
        tu = mod(Q.y - P.y);
        mau = mod(Q.x - P.x);
    }

    k = mod(1LL * tu * nghich(mau));

    R.x = mod(1LL * k * k - P.x - Q.x);
    R.y = mod(1LL * k * (P.x - R.x) - P.y);

    return R;
}

int main() {
    Diem P, R = {-1, -1};
    int n;

    cout << "Nhap p = "; cin >> p;
    cout << "Nhap a = "; cin >> a;
    cout << "Nhap Xp = "; cin >> P.x;
    cout << "Nhap Yp = "; cin >> P.y;
    cout << "Nhap n = "; cin >> n;

    if (p <= 3 || p > 1000 || n < 0) {
        cout << "Du lieu khong hop le";
        return 0;
    }

    // Kiem tra p nguyen to
    for (int i = 2; i * i <= p; i++) {
        if (p % i == 0) {
            cout << "p khong phai so nguyen to";
            return 0;
        }
    }

    P.x = mod(P.x);
    P.y = mod(P.y);

    // Tinh n.P bang phep cong lap
    for (int i = 1; i <= n; i++) {
        R = Tong(R, P);
    }

    if (R.x == -1)
        cout << n << "P = O";
    else
        cout << n << "P = (" << R.x << "," << R.y << ")";

    return 0;
}

