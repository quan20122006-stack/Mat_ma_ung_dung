// CHỨC NĂNG: Trao đổi khóa ECDH: PA=nA*G, PB=nB*G; hai bên tính cùng điểm khóa K=nA*nB*G.
#include <iostream>
#include <string>
using namespace std;

// Tham số chung của E: y^2=x^3+a*x+b (mod p), làm việc trên trường hữu hạn modulo p.
int p, a, b;

// Điểm gồm tọa độ x,y và cờ O: true nghĩa là điểm vô cực, khi đó không dùng x,y.
struct Diem { int x, y; bool O; };

// Tạo điểm vô cực O, phần tử trung hòa: P+O=P.
Diem voCuc() { return {0, 0, true}; }

// Tạo một điểm hữu hạn từ hai tọa độ; chưa tự kiểm tra điểm có thuộc đường cong hay không.
Diem taoDiem(int x, int y) { return {x, y, false}; }

// Đưa số nguyên về phần dư không âm 0..p-1.
int mod(long long x) { return (x % p + p) % p; }

// Euclid mở rộng: tìm x^(-1) modulo p, trả -1 nếu gcd(x,p) khác 1.
int nghich(int x) {
    // Euclid mở rộng bắt đầu với hai số dư p và x mod p.
    // t0,t1 theo dõi hệ số của x trong biểu diễn mỗi số dư; hệ số này trở thành nghịch đảo khi gcd=1.
    long long r0 = p, r1 = mod(x), t0 = 0, t1 = 1;
    while (r1 != 0) {
        // q là thương nguyên của bước Euclid; số dư tiếp theo r=r0-q*r1.
        // Cập nhật hệ số tương ứng bằng t=t0-q*t1 để giữ nguyên quan hệ với x.
        long long q = r0 / r1;
        long long r = r0 - q * r1;
        long long t = t0 - q * t1;
        // Dịch cặp số dư và cặp hệ số sang bước kế tiếp; dừng khi số dư r1 bằng 0.
        r0 = r1; r1 = r; t0 = t1; t1 = t;
    }
    // Kết thúc, r0=gcd(x,p). Nếu bằng 1 thì t0*x đồng dư 1 modulo p; chuẩn hóa t0 rồi trả về.
    // Nếu gcd khác 1, trả -1 để báo x không có nghịch đảo.
    return r0 == 1 ? mod(t0) : -1;
}

// Kiểm tra p nguyên tố trong 5..1000 và biệt thức 4*a^3+27*b^2 khác 0 modulo p.
bool duongCongDung() {
    if (p <= 3 || p > 1000) return false;
    // Chỉ cần thử ước đến căn bậc hai của p. Tìm được một ước thì p không nguyên tố, hàm trả false.
    for (int i = 2; i * i <= p; i++)
        if (p % i == 0) return false;
    // Đưa hai hệ số về 0..p-1. Điều kiện biệt thức khác 0 bảo đảm đường cong không suy biến,
    // để phép cộng điểm dùng trong bài xác định một nhóm.
    a = mod(a); b = mod(b);
    return mod(4LL * a * a * a + 27LL * b * b) != 0;
}

// Kiểm tra điểm thỏa phương trình đường cong; O luôn là điểm hợp lệ.
bool hopLe(Diem P) {
    // O không có tọa độ hữu hạn nhưng vẫn thuộc nhóm điểm; với điểm thường phải kiểm tra phương trình đường cong.
    if (P.O) return true;
    return mod(1LL * P.y * P.y) ==
           mod(1LL * P.x * P.x * P.x + 1LL * a * P.x + b);
}

// Hai điểm bằng nhau nếu cùng là O, hoặc cùng hữu hạn và có cùng tọa độ.
bool bang(Diem P, Diem Q) {
    return P.O == Q.O && (P.O || (P.x == Q.x && P.y == Q.y));
}

// Cộng điểm: O là trung hòa; hai điểm đối nhau cho O; còn lại dùng công thức hệ số góc.
Diem cong(Diem P, Diem Q) {
    // O là phần tử trung hòa: O+Q=Q và P+O=P, không cần tính hệ số góc.
    if (P.O) return Q;
    if (Q.O) return P;
    // P và Q đối nhau thì P+Q=O. Điều kiện này cũng xử lý P=Q có y=0, tránh nghịch đảo của 0.
    if (P.x == Q.x && mod(P.y + Q.y) == 0) return voCuc();

    int tu, mau;
    
    // Nhân đôi dùng lambda=(3*xp^2+a)/(2*yp); hai điểm khác nhau dùng (yq-yp)/(xq-xp).
    if (bang(P, Q)) {
        tu = mod(3LL * P.x * P.x + a);
        mau = mod(2LL * P.y);
    } else {
        tu = mod(Q.y - P.y);
        mau = mod(Q.x - P.x);
    }
    
    // Trong modulo, chia cho mẫu là nhân với nghịch đảo của mẫu.
    int dao = nghich(mau);
    if (dao == -1) return voCuc(); 
    // k chính là lambda. 1LL chuyển phép nhân sang long long trước khi nhân để giảm nguy cơ tràn int.
    int k = mod(1LL * tu * dao);
    
    // Tọa độ tổng: xr=lambda^2-xp-xq; yr=lambda*(xp-xr)-yp.
    int x = mod(1LL * k * k - P.x - Q.x);
    int y = mod(1LL * k * (P.x - x) - P.y);
    return taoDiem(x, y);
}

// P-Q=P+(-Q); điểm đối của (x,y) là (x,-y mod p).
Diem tru(Diem P, Diem Q) {
    // Giữ nguyên x, đổi y thành -y modulo p để tạo -Q; điểm đối của O vẫn là O.
    // Q được truyền theo giá trị nên thay đổi ở đây không làm đổi Q bên ngoài hàm.
    if (!Q.O) Q.y = mod(-Q.y);
    return cong(P, Q);
}

// Tính nP bằng phương pháp nhân đôi và cộng theo các bit của n, nhanh hơn cộng n lần.
Diem nhan(int n, Diem P) {
    // Khởi đầu tổng R=O. Duyệt các bit của n từ thấp lên cao: ví dụ 13P=1P+4P+8P.
    // P lần lượt được nhân đôi thành P,2P,4P,8P,...; chỉ cộng vào R ở những bit bằng 1.
    Diem R = voCuc();
    while (n > 0) {
        
        // Nếu bit hiện tại bằng 1 thì cộng P vào R; nhân đôi P và chia đôi n để xét bit tiếp theo.
        if (n % 2 == 1) R = cong(R, P);
        // Nhân đôi giá trị điểm cho bit kế tiếp; n/=2 bỏ bit vừa xét. Khi n=0 thì đã xét hết các bit.
        // Nếu n ban đầu bằng 0, trả ngay R=O, không đi qua vòng lặp.
        P = cong(P, P);
        n /= 2;
    }
    return R;
}

// Bậc P là số dương nhỏ nhất q sao cho qP=O. Giới hạn 2*p+2 bao trùm số điểm theo chặn Hasse.
int bac(Diem P) {
    if (P.O) return 1;
    Diem R = voCuc();
    // Lần lượt tạo P,2P,3P,...; gặp O lần đầu tại i thì bậc của P bằng i.
    // Giới hạn 2*p+2 đủ bao trùm số điểm của đường cong hợp lệ trong bài.
    for (int i = 1; i <= 2 * p + 2; i++) {
        R = cong(R, P);
        if (R.O) return i;
    }
    // Nếu không trở về O trong giới hạn, trả -1 để main có thể từ chối dữ liệu không thích hợp.
    return -1;
}

// In O cho điểm vô cực, hoặc in cặp tọa độ cho điểm hữu hạn.
void in(Diem P) {
    if (P.O) cout << "O";
    else cout << "(" << P.x << "," << P.y << ")";
}

// Đọc hai tọa độ nguyên rồi chuẩn hóa modulo p; hàm main kiểm tra điểm thuộc đường cong khi dùng.
Diem nhapDiem() {
    int x, y;
    cout << "Nhap x, y: "; cin >> x >> y;
    // Chuẩn hóa tọa độ đọc vào, rồi tạo điểm hữu hạn có cờ O=false.
    // Bàn phím ở bài này không có cú pháp nhập điểm O trực tiếp.
    return taoDiem(mod(x), mod(y));
}

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main() {
    cout << "Nhap p, a, b: "; cin >> p >> a >> b;
    if (!duongCongDung()) { cout << "Duong cong khong hop le\n"; return 0; }
    cout << "Diem G: "; Diem G = nhapDiem();
    int nA, nB;
    cout << "Nhap khoa rieng A, B: "; cin >> nA >> nB;
    if (!hopLe(G) || G.O || nA < 1 || nB < 1 || nA > 10000 || nB > 10000) {
        cout << "Du lieu khong hop le\n"; return 0;
    }
    
    // q là bậc điểm G. Khóa riêng chia hết cho q làm khóa công khai bằng O nên bị từ chối.
    // Kiểm tra này chưa loại mọi trường hợp khóa chung bằng O: hai khóa không là bội q nhưng tích có thể là bội q.
    int q = bac(G);
    if (q < 2 || nA % q == 0 || nB % q == 0) {
        cout << "Khoa khong hop le (boi cua bac G)\n"; return 0;
    }
    
    // Tạo hai khóa công khai: PA=nA*G, PB=nB*G. Các số nA,nB là khóa riêng, phép nhân ở đây là nhân điểm.
    Diem PA = nhan(nA, G), PB = nhan(nB, G);
    // A dùng khóa riêng nA nhân khóa công khai PB; B dùng nB nhân PA.
    // Cả hai đều nhận nA*nB*G, nên hàm bang(KA,KB) phải trả true nếu phép toán đúng.
    Diem KA = nhan(nA, PB), KB = nhan(nB, PA);
    cout << "PA = "; in(PA);
    cout << "\nPB = "; in(PB);
    cout << "\nKhoa A = "; in(KA);
    cout << "\nKhoa B = "; in(KB);
    cout << "\nKhoa trung nhau: " << (bang(KA, KB) ? "Co" : "Khong") << '\n';
    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p a b (p nguyên tố 5..1000, đường cong không suy biến): nhập 23 1 1
2. x y của điểm G (phải thuộc đường cong): nhập 3 10
3. nA nB (khóa riêng 1..10000; với mẫu này dùng 3 và 5): nhập 3 5

Bộ input mẫu (nhập từng dòng):
23 1 1
3 10
3 5
*/
