// CHỨC NĂNG: Minh họa RSA: tạo khóa, mã hóa một số nguyên rồi giải mã lại.
#include<iostream>
#include<string>
using namespace std;

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main(){
    // p,q: hai số nguyên tố khác nhau; n: mô-đun; phi: số phần tử khả nghịch modulo n.
    // e: số mũ công khai; d: số mũ bí mật; P: số bản rõ; C: số bản mã; M: số giải mã.
    // C,M bắt đầu bằng 1 để nhân lặp tính lũy thừa; d=0 đánh dấu chưa tìm được khóa bí mật.
    int p,q,n,phi,e,d=0,P,C=1,M=1;
    cout<<"Nhap p = ";cin>>p;
    cout<<"Nhap q = ";cin>>q;
    // Mọi phép mã hóa/giải mã làm việc modulo n=p*q.
    // phi=(p-1)*(q-1) chỉ đúng với giả thiết p và q là hai số nguyên tố khác nhau; code chưa tự kiểm tra giả thiết này.
    n=p*q;
    phi=(p-1)*(q-1);
    cout<<"n = "<<n<<endl;
    cout<<"phi = "<<phi<<endl;
    cout<<"Nhap e = ";cin>>e;
    // Thử các i từ 1 đến phi-1 để tìm nghịch đảo nhân của e.
    // Nếu (e*i)%phi==1 thì chọn d=i: e*d đồng dư 1 modulo phi; nghịch đảo tồn tại khi gcd(e,phi)=1.
    for(int i=1;i<phi;i++){
        if((e*i)%phi==1){
            // Lưu khóa bí mật đầu tiên thỏa điều kiện rồi break để dừng dò.
            d=i;
            break;
        }
    }
    // Không tìm được nghịch đảo thì chưa tạo được cặp khóa RSA hợp lệ, chương trình báo lỗi và kết thúc.
    if(d==0){
        cout<<"e khong hop le!";
        return 0;
    }
    cout<<"Khoa cong khai: ("<<e<<","<<n<<")"<<endl;
    cout<<"Khoa bi mat: ("<<d<<","<<n<<")"<<endl;

    cout<<"Nhap ban ro P = ";cin>>P;

    // Bản rõ trong bài là một số nguyên đại diện lớp đồng dư, bắt buộc 0<=P<n.
    if(P<0 || P>=n){
        cout<<"P phai nam trong [0,n-1]";
        return 0;
    }
    // Tính C=P^e mod n bằng e lần nhân: sau bước i, C=P^i mod n.
    // Lấy modulo sau mỗi bước để giảm giá trị; tích vẫn có thể tràn int nếu số đầu vào lớn.
    for(int i=1;i<=e;i++){
        C=(C*P)%n;
    }
    cout<<"Ban ma C = "<<C<<endl;
    // Tương tự, tính M=C^d mod n. Với các tham số RSA hợp lệ và không tràn số, M phải bằng P ban đầu.
    for(int i=1;i<=d;i++){
        M=(M*C)%n;
    }
    cout<<"Giai ma M = "<<M<<endl;
    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố nhỏ): nhập 11
2. q (số nguyên tố nhỏ khác p): nhập 13
3. e (1<e<phi, nguyên tố cùng nhau với phi): nhập 7
4. P (số bản rõ, 0<=P<p*q): nhập 9

Bộ input mẫu (nhập từng dòng):
11
13
7
9
*/
