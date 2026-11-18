// CHỨC NĂNG: Tìm bậc của điểm P: số nguyên dương nhỏ nhất n sao cho nP=O.
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
    // R=O là tổng ban đầu; n=0 là số lần đã cộng P vào tổng.
    Diem P, R = {-1, -1};
    int n = 0;

    cout << "Nhap p = "; cin >> p;
    cout << "Nhap a = "; cin >> a;
    cout << "Nhap Xp = "; cin >> P.x;
    cout << "Nhap Yp = "; cin >> P.y;

    if (p <= 3 || p > 1000) {
        cout << "p khong hop le";
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

    // Dùng do-while để cộng ít nhất một lần: bậc phải là số dương, không lấy 0P=O làm đáp án.
    do {
        R = Tong(R, P);
        // Tăng số lần cộng; nếu R vừa trở về O thì n hiện tại là bậc nhỏ nhất cần tìm.
        n++;
    // Tiếp tục khi R còn hữu hạn. Khi x=-1 thì R=O, dừng và in n.
    // Với điểm trên đường cong hợp lệ, bậc hữu hạn; code không có giới hạn vòng lặp dự phòng.
    } while (R.x != -1);

    cout << "Bac cua diem P la n = " << n;

    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố trong 5..1000): nhập 23
2. a (hệ số đường cong): nhập 1
3. Xp (hoành độ P): nhập 3
4. Yp (tung độ P): nhập 10

Bộ input mẫu (nhập từng dòng):
23
1
3
10
*/
