// CHỨC NĂNG: Liệt kê các điểm hữu hạn của E: y^2 = x^3 + a*x + b (mod p) và đếm thêm điểm vô cực O.
#include <iostream>
using namespace std;

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main() {
    
    // a, b là hệ số đường cong; p là mô-đun; dem đếm các cặp tọa độ thỏa phương trình.
    int a, b, p;
    // dem bắt đầu bằng 0 và tăng một lần cho mỗi cặp tọa độ hữu hạn tìm thấy.
    int dem = 0;

    cout << "Nhap a= "; cin >> a;
    cout << "Nhap b= "; cin >> b;
    cout << "Nhap p= "; cin >> p;

    // Loại mô-đun quá nhỏ. Điều kiện này chưa đủ kiểm tra p nguyên tố: người nhập cần chọn p nguyên tố và đường cong không suy biến.
    if (p <= 3) {
        cout << "p phai la so nguyen to lon hon 3";
        return 0;
    }

    cout << "Cac diem tren duong cong la:\n";

    // Duyệt mọi cặp (x,y) trong 0..p-1 rồi so sánh hai vế theo modulo p.
    for (int x = 0; x < p; x++) {
        // Với mỗi hoành độ x, thử tất cả tung độ y; hai vòng lặp xét tổng cộng p*p cặp.
        for (int y = 0; y < p; y++) {
            // VT là y^2 mod p; VP là (x^3+a*x+b) mod p.
            // Hai vế bằng nhau nghĩa là (x,y) thuộc đường cong. Biểu thức dùng int nên cần chọn số nhỏ để tránh tràn.
            int VT = (y * y) % p;
            int VP = (x * x * x + a * x + b) % p;

            // Đưa phần dư âm của vế phải về khoảng 0..p-1.
            if (VP < 0) VP += p;

            if (VT == VP) {
                cout << "(" << x << "," << y << ")\n";
                // Chỉ đếm khi hai vế bằng nhau; mỗi cặp (x,y) được duyệt đúng một lần.
                dem++;
            }
        }
    }

    // O không có tọa độ hữu hạn; tổng số điểm của đường cong bằng số vừa đếm cộng 1.
    cout << "So diem huu han: " << dem << endl;
    cout << "Tong so diem (ke ca O): " << dem + 1;

    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. a (hệ số đường cong): nhập 1
2. b (hệ số đường cong): nhập 1
3. p (số nguyên tố > 3, nên dùng số nhỏ): nhập 23

Bộ input mẫu (nhập từng dòng):
1
1
23
*/
