#include <iostream>
#include <string>
using namespace std;

int p, a, b;
struct Diem { int x, y; bool O; };
Diem voCuc() { return {0, 0, true}; }
Diem taoDiem(int x, int y) { return {x, y, false}; }
int mod(long long x) { return (x % p + p) % p; }

int nghich(int x) {
    long long r0 = p, r1 = mod(x), t0 = 0, t1 = 1;
    while (r1 != 0) {
        long long q = r0 / r1;
        long long r = r0 - q * r1;
        long long t = t0 - q * t1;
        r0 = r1; r1 = r; t0 = t1; t1 = t;
    }
    return r0 == 1 ? mod(t0) : -1;
}

bool duongCongDung() {
    if (p <= 3 || p > 1000) return false;
    for (int i = 2; i * i <= p; i++)
        if (p % i == 0) return false;
    a = mod(a); b = mod(b);
    return mod(4LL * a * a * a + 27LL * b * b) != 0;
}

bool hopLe(Diem P) {
    if (P.O) return true;
    return mod(1LL * P.y * P.y) ==
           mod(1LL * P.x * P.x * P.x + 1LL * a * P.x + b);
}

bool bang(Diem P, Diem Q) {
    return P.O == Q.O && (P.O || (P.x == Q.x && P.y == Q.y));
}

Diem cong(Diem P, Diem Q) {
    if (P.O) return Q;
    if (Q.O) return P;
    if (P.x == Q.x && mod(P.y + Q.y) == 0) return voCuc();

    int tu, mau;
    if (bang(P, Q)) {
        tu = mod(3LL * P.x * P.x + a);
        mau = mod(2LL * P.y);
    } else {
        tu = mod(Q.y - P.y);
        mau = mod(Q.x - P.x);
    }
    int dao = nghich(mau);
    if (dao == -1) return voCuc(); // Khong xay ra voi diem hop le va p nguyen to
    int k = mod(1LL * tu * dao);
    int x = mod(1LL * k * k - P.x - Q.x);
    int y = mod(1LL * k * (P.x - x) - P.y);
    return taoDiem(x, y);
}

Diem tru(Diem P, Diem Q) {
    if (!Q.O) Q.y = mod(-Q.y);
    return cong(P, Q);
}

Diem nhan(int n, Diem P) {
    Diem R = voCuc();
    while (n > 0) {
        if (n % 2 == 1) R = cong(R, P);
        P = cong(P, P);
        n /= 2;
    }
    return R;
}

int bac(Diem P) {
    if (P.O) return 1;
    Diem R = voCuc();
    for (int i = 1; i <= 2 * p + 2; i++) {
        R = cong(R, P);
        if (R.O) return i;
    }
    return -1;
}

void in(Diem P) {
    if (P.O) cout << "O";
    else cout << "(" << P.x << "," << P.y << ")";
}

Diem nhapDiem() {
    int x, y;
    cout << "Nhap x, y: "; cin >> x >> y;
    return taoDiem(mod(x), mod(y));
}

int main() {
    cout << "Nhap p, a, b: "; cin >> p >> a >> b;
    if (!duongCongDung()) { cout << "Duong cong khong hop le\n"; return 0; }
    cout << "Diem G: "; Diem G = nhapDiem();
    cout << "Thong diep M: "; Diem M = nhapDiem();
    int nA, nB;
    cout << "Nhap khoa rieng A, B: "; cin >> nA >> nB;
    if (!hopLe(G) || !hopLe(M) || G.O || nA < 1 || nB < 1 || nA > 10000 || nB > 10000) {
        cout << "Du lieu khong hop le\n"; return 0;
    }
    int q = bac(G);
    if (q < 2 || nA % q == 0 || nB % q == 0) {
        cout << "Khoa khong hop le\n"; return 0;
    }
    Diem PA = nhan(nA, G), PB = nhan(nB, G);
    Diem K = nhan(nA, PB);
    Diem C = cong(M, K);
    Diem D = tru(C, nhan(nB, PA));
    cout << "Khoa chung = "; in(K);
    cout << "\nBan ma C = "; in(C);
    cout << "\nGiai ma M = "; in(D);
    cout << "\nGiai ma dung: " << (bang(M, D) ? "Co" : "Khong") << '\n';
    return 0;
}
