// CHỨC NĂNG: In bảng các lũy thừa a^i mod p với a=1..p-1 và i=1..p-1.
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main() {
    int p;
    cout << "Nhap p: "; cin >> p;
    if(p<2) return 0;
    
    // Mỗi hàng ứng với một cơ số a.
    for(int a=1;a<p;a++) {
        
        // Ban đầu x=a^0=1; mỗi bước nhân thêm a và lấy modulo để có lũy thừa tiếp theo.
        long long x=1;
        cout << "a = " << a << ": ";
        
        // Các cột lần lượt là số mũ 1,2,...,p-1.
        for(int i=1;i<p;i++) {
            // Giữ kết quả trước là a^(i-1) mod p; nhân thêm a cho a^i mod p.
            // long long giúp phép nhân chứa được giá trị lớn hơn int; không cần tính a^i đầy đủ rồi mới chia dư.
            x=x*a%p;
            cout << x << " ";
        }
        cout << "\n";
    }
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố nhỏ >= 2): nhập 7

Bộ input mẫu (nhập từng dòng):
7
*/
