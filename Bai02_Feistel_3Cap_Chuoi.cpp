// Feistel theo slide: khối 16 bit, khóa vòng dịch trái, đủ các cách mã hóa 3 cấp.
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// Khóa vòng i là K dịch TRÁI i bit, giữ đúng 8 bit thấp. Đây không phải dịch vòng.
unsigned char khoaVong(unsigned char K, int i) { return (K << i) & 255; }
// F cộng hai byte rồi lấy modulo 256 để kết quả vẫn là một byte.
unsigned char F(unsigned char R, unsigned char Ki) { return (R + Ki) & 255; }

// Một tầng Feistel có đúng hai vòng, chia khối thành hai nửa L,R mỗi nửa 8 bit.
string E(unsigned char K, string P) {
    unsigned char L = (unsigned char)P[0], R = (unsigned char)P[1];
    for (int i=1; i<=2; ++i) {
        unsigned char moiL=R;
        // L mới = R cũ; R mới = L cũ XOR F(R cũ, khóa của vòng i).
        R=L ^ F(R,khoaVong(K,i)); L=moiL;
    }
    string C(2,'\0'); C[0]=(char)L; C[1]=(char)R;
    return C;
}
// Đảo các vòng theo i=2,1; phải dùng đúng khóa vòng tương ứng khi mã hóa.
string D(unsigned char K, string C) {
    unsigned char L=(unsigned char)C[0], R=(unsigned char)C[1];
    for (int i=2; i>=1; --i) {
        unsigned char cuR=L;
        // R cũ = L mới; L cũ = R mới XOR F(L mới, Ki).
        L=R ^ F(L,khoaVong(K,i)); R=cuR;
    }
    string P(2,'\0'); P[0]=(char)L; P[1]=(char)R;
    return P;
}
// Kiểu 1: E-E-E; kiểu 2: E-D-E ba khóa; kiểu 3: E-D-E hai khóa (K3=K1).
// Kiểu 4 giữ phép Feistel một tầng để kiểm tra riêng công thức slide 44–48.
string maHoa(string P,int kieu,char K1,char K2,char K3) {
    P=E((unsigned char)K1,P);
    if(kieu==4) return P;
    P=(kieu==1 ? E((unsigned char)K2,P) : D((unsigned char)K2,P));
    return E((unsigned char)K3,P);
}
string giaiMa(string C,int kieu,char K1,char K2,char K3) {
    if(kieu==4) return D((unsigned char)K1,C);
    // Đảo thứ tự các tầng; E phải đảo bằng D, D phải đảo bằng E.
    C=D((unsigned char)K3,C);
    C=(kieu==1 ? D((unsigned char)K2,C) : E((unsigned char)K2,C));
    return D((unsigned char)K1,C);
}

int main() {
    string P,C,ketQua; int kieu; char K1=0,K2=0,K3=0;
    cout << "Nhap plaintext: "; getline(cin,P);
    cout << "1: EEE 3 khoa; 2: EDE 3 khoa; 3: EDE 2 khoa; 4: Feistel 1 tang\nChon: ";
    if(!(cin>>kieu) || kieu<1 || kieu>4) { cout<<"Lua chon khong hop le"; return 0; }
    cout << "Nhap khoa (moi khoa 1 ky tu): ";
    if(!(cin>>K1)) return 0;
    if(kieu!=4 && !(cin>>K2)) return 0;
    if((kieu==1 || kieu==2) && !(cin>>K3)) return 0;
    if(kieu==3) K3=K1;
    // Đệm cho đủ khối nhưng lưu độ dài ban đầu để không xóa nhầm dấu cách thật.
    size_t doDai=P.size();
    if(P.size()%2) P+=' ';
    for(size_t i=0;i<P.size();i+=2) C+=maHoa(P.substr(i,2),kieu,K1,K2,K3);
    cout<<"Ciphertext (gia tri byte): ";
    for(unsigned char c:C) cout<<(int)c<<" ";
    // Giải mã chính bản mã vừa tạo, không tính lại bản mã từ bản rõ.
    for(size_t i=0;i<C.size();i+=2) ketQua+=giaiMa(C.substr(i,2),kieu,K1,K2,K3);
    ketQua.resize(doDai);
    cout<<"\nGiai ma: "<<ketQua<<"\n";
    return 0;
}
/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
1. Bản rõ không dấu: nhập HELLO
2. Kiểu: 1=EEE ba khóa, 2=EDE ba khóa, 3=EDE hai khóa, 4=một tầng Feistel.
3. Nếu chọn 1 hoặc 2: nhập A B C. Chọn 3: nhập A B. Chọn 4: nhập K.
Bộ input mẫu (nhập từng dòng):
HELLO
1
A B C
*/
