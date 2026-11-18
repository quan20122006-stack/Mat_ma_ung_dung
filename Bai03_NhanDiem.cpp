// CHỨC NĂNG: Tính nP trên đường cong elliptic bằng cách cộng điểm P lặp lại n lần.
#include <iostream>
using namespace std;

// Tính trên E: y^2=x^3+a*x+b (mod p). Công thức cộng chỉ cần p,a; b do điểm đầu vào xác định.
int p, a;

// Chuẩn hóa phần dư về 0..p-1, kể cả khi biểu thức ban đầu âm.
int mod(long long x) {
    // Trong C++, x%p có thể âm. Cộng p rồi %p lần nữa đưa kết quả về 0..p-1.
    return (x % p + p) % p;
}

// Dò nghịch đảo x^(-1) modulo p; trả -1 nếu không tồn tại.
int nghich(int x) {
    for (int i = 1; i < p; i++) {
        if (mod(1LL * x * i) == 1)
            return i;
    }
    // Không tìm được nghịch đảo. Với p nguyên tố, trường hợp không có nghịch đảo chỉ xảy ra khi x=0 modulo p.
    return -1;
}

// Lưu tọa độ điểm; x=-1 biểu diễn điểm vô cực O, phần tử trung hòa của phép cộng.
struct Diem {
    int x, y;
};

// Cộng hai điểm: xử lý O, hai điểm đối nhau, nhân đôi, rồi trường hợp hai điểm khác nhau.
Diem Tong(Diem P, Diem Q) {
    Diem R;
    int tu, mau, k;

    // O là phần tử trung hòa: O+Q=Q. Tương tự, P+O=P.
    if (P.x == -1) return Q;
    if (Q.x == -1) return P;

    // Hai điểm đối nhau cộng thành O; trường hợp nhân đôi điểm có y=0 cũng được xử lý ở đây, tránh chia cho 0.
    if (P.x == Q.x && mod(P.y + Q.y) == 0)
        return {-1, -1};

    // Hai điểm trùng nhau dùng tiếp tuyến để tính 2P; hai điểm khác nhau dùng đường thẳng đi qua P,Q.
    if (P.x == Q.x && P.y == Q.y) {
        
        // Khi P=Q: lambda=(3*xp^2+a)/(2*yp) modulo p.
        tu = mod(3LL * P.x * P.x + a);
        mau = mod(2LL * P.y);
    }
    else {
        
        // Khi P khác Q: lambda=(yq-yp)/(xq-xp) modulo p.
        tu = mod(Q.y - P.y);
        mau = mod(Q.x - P.x);
    }

    // Thay phép chia bằng nhân nghịch đảo; 1LL giúp phép nhân thực hiện bằng long long.
    k = mod(1LL * tu * nghich(mau));

    // Tính xr=lambda^2-xp-xq và yr=lambda*(xp-xr)-yp trong modulo p.
    R.x = mod(1LL * k * k - P.x - Q.x);
    R.y = mod(1LL * k * (P.x - R.x) - P.y);

    return R;
}

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main() {
    // P là điểm gốc; R là tổng tích lũy, ban đầu bằng O. n là số lần cộng điểm P, không phải nhân từng tọa độ với n.
    Diem P, R = {-1, -1};
    int n;

    cout << "Nhap p = "; cin >> p;
    cout << "Nhap a = "; cin >> a;
    cout << "Nhap Xp = "; cin >> P.x;
    cout << "Nhap Yp = "; cin >> P.y;
    cout << "Nhap n = "; cin >> n;

    // Giới hạn p để các phép dò nghịch đảo và kiểm tra nguyên tố chạy nhanh; không nhận hệ số nhân n âm.
    if (p <= 3 || p > 1000 || n < 0) {
        cout << "Du lieu khong hop le";
        return 0;
    }

    for (int i = 2; i * i <= p; i++) {
        if (p % i == 0) {
            cout << "p khong phai so nguyen to";
            return 0;
        }
    }

    // Chuẩn hóa tọa độ đầu vào về 0..p-1 trước khi so sánh và cộng điểm.
    // Không nhập b; có thể suy ra b=yP^2-xP^3-a*xP modulo p từ P. Code chưa kiểm tra đường cong suy biến.
    P.x = mod(P.x);
    P.y = mod(P.y);

    // Mỗi lần cập nhật R=R+P. Sau n vòng thu được nP.
    // Nếu n=0, vòng lặp không chạy và R giữ nguyên O, đúng với định nghĩa 0P=O.
    for (int i = 1; i <= n; i++) {
        R = Tong(R, P);
    }

    if (R.x == -1)
        cout << n << "P = O";
    else
        cout << n << "P = (" << R.x << "," << R.y << ")";

    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố trong 5..1000): nhập 23
2. a (hệ số đường cong): nhập 1
3. Xp (hoành độ P): nhập 3
4. Yp (tung độ P): nhập 10
5. n (số nguyên không âm, nên dùng số nhỏ): nhập 2

Bộ input mẫu (nhập từng dòng):
23
1
3
10
2
*/
