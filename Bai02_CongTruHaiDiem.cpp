
#include <iostream>
using namespace std;

struct Diem {
    int x, y;
};

Diem Tong(Diem P, Diem Q, int p) {
    Diem R;
    int TS, MS, MS1 = 0, L;

    // Hai diem doi nhau
    if (P.x == Q.x && (P.y + Q.y) % p == 0) {
        R.x = -1;
        R.y = -1;
        return R;
    }

    // Hai diem khac nhau
    TS = (Q.y - P.y + p) % p;
    MS = (Q.x - P.x + p) % p;

    // Tim nghich dao modulo
    for (int i = 1; i < p; i++) {
        if ((i * MS) % p == 1) {
            MS1 = i;
            break;
        }
    }

    // Tinh lambda
    L = TS * MS1 % p;

    // Tinh toa do R
    R.x = (L * L - P.x - Q.x) % p;
    R.x = (R.x + p) % p;

    R.y = (L * (P.x - R.x) - P.y) % p;
    R.y = (R.y + p) % p;

    return R;
}

int main() {
    Diem P, Q, R;
    int p;

    cout << "Nhap Xp= "; cin >> P.x;
    cout << "Nhap Yp= "; cin >> P.y;
    cout << "Nhap Xq= "; cin >> Q.x;
    cout << "Nhap Yq= "; cin >> Q.y;
    cout << "Nhap p= "; cin >> p;

    if (p <= 3) {
        cout << "p khong hop le";
        return 0;
    }

    if (P.x == Q.x && P.y == Q.y) {
        cout << "P va Q phai khac nhau";
        return 0;
    }

    R = Tong(P, Q, p);

    if (R.x == -1 && R.y == -1)
        cout << "R la diem O vo cuc";
    else
        cout << "R = (" << R.x << "," << R.y << ")";

    return 0;
}

