// CHỨC NĂNG: Tìm các phần tử nguyên thủy modulo số nguyên tố p.
#include<iostream>
#include<string>
using namespace std;

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main(){
    // p là mô-đun; a là ứng viên; x là giá trị lũy thừa đang tính; dem lưu bậc của a.
    // i dùng cho các vòng lặp; biến j được khai báo nhưng chưa sử dụng.
    int p,a,i,j,x,dem;

    cout<<"Nhap p = ";
    cin>>p;

    if(p<2 || p>10000){
        cout<<"p khong hop le";
        return 0;
    }

    // Thử các ước đến căn bậc hai để kiểm tra p là số nguyên tố.
    for(i=2;i*i<=p;i++){
        if(p%i==0){
            cout<<"p khong phai so nguyen to";
            return 0;
        }
    }

    cout<<"Cac phan tu nguyen thuy la: ";

    // Xét từng ứng viên a trong 1..p-1.
    for(a=1;a<p;a++){
        // Bắt đầu từ a^0=1; đặt dem=0 để đánh dấu chưa gặp lũy thừa dương nào bằng 1.
        x=1;
        dem=0;

        // Tính a^i mod p và dừng ở số mũ dương nhỏ nhất cho kết quả 1; đó là bậc của a.
        for(i=1;i<p;i++){
            // Sau lần lặp i, x=a^i mod p. Không cần tính lại từ đầu cho mỗi i.
            x=(x*a)%p;

            // Lần đầu quay về 1 xác định bậc nhân của a. Lưu số mũ đó vào dem rồi ngừng thử ứng viên hiện tại.
            if(x==1){
                dem=i;
                break;
            }
        }

        // Nếu bậc là p-1 thì các lũy thừa a^1,...,a^(p-1) sinh đủ các số 1..p-1.
        // Vì thế a là phần tử nguyên thủy; các ứng viên quay về 1 sớm hơn không được in.
        if(dem==p-1){
            cout<<a<<" ";
        }
    }

    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố 2..10000, nên dùng số nhỏ): nhập 7

Bộ input mẫu (nhập từng dòng):
7
*/
