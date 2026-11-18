// CHỨC NĂNG: Minh họa ElGamal bằng khóa chung modulo p: mã hóa một số rồi dùng nghịch đảo để giải mã.
#include<iostream>
#include<string>
using namespace std;

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main(){
    // p: mô-đun nguyên tố; a: phần tử sinh; XA: khóa riêng người nhận; XB: số bí mật của lần mã hóa; P: số bản rõ.
    int p,a,XA,XB,P;
    // YA=a^XA là khóa công khai người nhận; YB=a^XB là thành phần thứ nhất của bản mã.
    // K là khóa dùng che P; C là thành phần bản mã thứ hai; nghichDao=0 đánh dấu chưa tìm được K^(-1).
    int YA=1,YB=1,K=1,C,nghichDao=0;

    cout<<"Nhap p = ";cin>>p;
    cout<<"Nhap a = ";cin>>a;
    cout<<"Nhap XA = ";cin>>XA;
    cout<<"Nhap XB = ";cin>>XB;
    cout<<"Nhap P = ";cin>>P;

    if(p<3 || a<=0 || a>=p || XA<=0 || XB<=0 || P<0 || P>=p){
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

    // Tính K=YB^XA mod p. Bên gửi cũng có thể tính cùng K từ YA^XB mod p.
    // Trong bài minh họa, chương trình biết cả XA,XB để thực hiện hai chiều trong một lần chạy.
    for(int i=1;i<=XA;i++){
        K=(K*YB)%p;
    }

    // Mã hóa bằng phép nhân: C=K*P mod p.
    C=(K*P)%p;

    // Tìm i sao cho K*i đồng dư 1 modulo p để có thể bỏ thừa số K khi giải mã.
    for(int i=1;i<p;i++){
        if((K*i)%p==1){
            nghichDao=i;
            break;
        }
    }

    // Nếu không tìm thấy nghịch đảo thì không thể thực hiện phép chia cho K trong modulo; báo lỗi và dừng.
    if(nghichDao==0){
        cout<<"Khong co nghich dao";
        return 0;
    }

    cout<<"YA = "<<YA<<endl;
    cout<<"YB = "<<YB<<endl;
    cout<<"K = "<<K<<endl;
    cout<<"Ban ma C = "<<C<<endl;

    // Vì C=K*P mod p, nhân C với K^(-1) sẽ cho lại P.
    // Biến P được dùng lại để chứa kết quả giải mã; các phép nhân int có thể tràn nếu số đầu vào lớn.
    P=(C*nghichDao)%p;

    cout<<"Giai ma P = "<<P<<endl;

    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố nhỏ): nhập 23
2. a (phần tử nguyên thủy modulo p): nhập 5
3. XA (khóa riêng người nhận, số nguyên dương): nhập 6
4. XB (số bí mật lần mã hóa, số nguyên dương): nhập 15
5. P (số bản rõ 0..p-1): nhập 9

Bộ input mẫu (nhập từng dòng):
23
5
6
15
9
*/
