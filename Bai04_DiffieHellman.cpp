// CHỨC NĂNG: Mô phỏng trao đổi khóa Diffie-Hellman giữa A và B trong modulo p.
#include<iostream>
#include<string>
using namespace std;

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main(){
    // p: số nguyên tố; a: phần tử sinh; XA,XB: khóa riêng của hai bên.
    // YA,YB: khóa công khai; KA,KB: khóa chung tính riêng ở A và B; các tích lũy bắt đầu bằng 1.
    int p,a,XA,XB,YA=1,YB=1,KA=1,KB=1;

    cout<<"Nhap p = ";cin>>p;
    cout<<"Nhap a = ";cin>>a;
    cout<<"Nhap XA = ";cin>>XA;
    cout<<"Nhap XB = ";cin>>XB;

    // Chỉ kiểm tra khoảng giá trị và khóa dương. p nguyên tố và a là phần tử nguyên thủy do người nhập bảo đảm.
    if(p<3 || a<=0 || a>=p || XA<=0 || XB<=0){
        cout<<"Du lieu khong hop le";
        return 0;
    }

    // YA bắt đầu bằng 1. Sau XA lần nhân với a và lấy %p, thu được khóa công khai YA=a^XA mod p.
    for(int i=1;i<=XA;i++){
        YA=(YA*a)%p;
    }

    // Tương tự, YB=a^XB mod p. Số mũ XB giữ riêng, còn giá trị YB có thể công khai.
    for(int i=1;i<=XB;i++){
        YB=(YB*a)%p;
    }

    cout<<"YA = "<<YA<<endl;
    cout<<"YB = "<<YB<<endl;

    // A nhận YB, dùng XA để tính KA=YB^XA mod p=a^(XB*XA) mod p.
    for(int i=1;i<=XA;i++){
        KA=(KA*YB)%p;
    }

    // B nhận YA, dùng XB để tính KB=YA^XB mod p=a^(XA*XB) mod p.
    // Hai biểu thức có cùng tích số mũ nên hai khóa phải bằng nhau; phép nhân int có thể tràn khi dữ liệu lớn.
    for(int i=1;i<=XB;i++){
        KB=(KB*YA)%p;
    }

    cout<<"Khoa chung cua A = "<<KA<<endl;
    cout<<"Khoa chung cua B = "<<KB<<endl;

    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố nhỏ): nhập 23
2. a (phần tử nguyên thủy modulo p): nhập 5
3. XA (khóa riêng A, số nguyên dương): nhập 6
4. XB (khóa riêng B, số nguyên dương): nhập 15

Bộ input mẫu (nhập từng dòng):
23
5
6
15
*/
