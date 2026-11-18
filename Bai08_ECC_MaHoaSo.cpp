// CHỨC NĂNG: Ánh xạ số m thành điểm M=(m+1)G, mã hóa C=M+K rồi giải mã trở lại số.
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


// Bảng tọa độ đúng theo slide 78 và 86: A/0 ở vị trí 0, B/1 ở vị trí 1,...
// Không dùng (chỉ số+1)G vì thứ tự bội của G khác thứ tự trong bảng bài giảng.
Diem bangDiem(int i) {
    const int x[26]={0,0,1,1,3,3,4,5,5,6,6,7,7,9,9,11,11,12,12,13,13,17,17,18,18,19};
    const int y[26]={1,22,7,16,10,13,0,4,19,4,19,11,12,7,16,3,20,4,19,7,16,3,20,3,20,5};
    return taoDiem(x[i],y[i]);
}

int main() {
    p=23; a=1; b=1; Diem G=taoDiem(3,10);
    int nA,nB,m;
    cout<<"Nhap nA nB M: ";
    if(!(cin>>nA>>nB>>m) || nA<1 || nA>=28 || nB<1 || nB>=28 || m<0 || m>=23) {
        cout<<"Du lieu khong hop le"; return 0;
    }
    Diem PA=nhan(nA,G),PB=nhan(nB,G),K=nhan(nA,PB);
    if(K.O) { cout<<"Khoa chung O, hay chon lai khoa"; return 0; }
    // Tra bảng slide 86: số 8 ứng với (5,19), không phải 9G.
    Diem M=bangDiem(m),C=cong(M,K),D=tru(C,nhan(nB,PA));
    cout<<"PA = "; in(PA); cout<<"\nPB = "; in(PB);
    cout<<"\nKhoa chung = "; in(K);
    cout<<"\nM duoi dang diem = "; in(M);
    cout<<"\nC = "; in(C); cout<<"\nD = "; in(D);
    int so=-1;
    // Đổi điểm giải mã thành số bằng cách tìm lại vị trí trong cùng bảng ánh xạ.
    for(int i=0;i<23;++i) if(bang(D,bangDiem(i))) { so=i; break; }
    cout<<"\nSo giai ma = "<<so<<"\n"; return 0;
}
/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt nA nB M: hai khóa riêng trong 1..27, số M trong 0..22.
Bộ input mẫu theo slide 87:
8 5 8
*/
