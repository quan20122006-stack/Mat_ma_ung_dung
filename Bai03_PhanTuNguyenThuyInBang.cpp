// CHỨC NĂNG: In bảng a^i mod p để quan sát và nhận biết phần tử nguyên thủy.
#include<iostream>
using namespace std;
	
	// Tính a^m mod p bằng cách nhân a liên tiếp m lần; p=0 được trả 0 để tránh chia cho 0.
	int mu(int a, int m, int p){
		if(p==0) return 0;
		// b là kết quả tích lũy, ban đầu bằng a^0=1; sau i lần nhân thì b=a^i mod p.
		long long b=1;
		for(int i=1;i<=m;i++)
			// Lấy modulo ở từng bước để tránh tạo số lũy thừa rất lớn; hàm trả kết quả sau m lần nhân.
			b=(b*a)%p;
		return b;
	}

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main(){
	int p;
	cout<<"p = ";cin>>p;
	
	// Duyệt từng cơ số a; in các lũy thừa từ 1 đến p-1 trên một hàng.
	for(int a=1;a<p;a++){
		for(int i=1;i<p;i++) 	
			cout<< mu(a,i,p)<<" ";
			// Xuống dòng sau khi in đủ các số mũ của một cơ số a.
			// Dòng này nằm ngoài vòng for theo i dù cách thụt lề hiện tại dễ gây nhầm.
			cout<<endl;
	}
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. p (số nguyên tố nhỏ >= 2): nhập 7

Bộ input mẫu (nhập từng dòng):
7
*/
