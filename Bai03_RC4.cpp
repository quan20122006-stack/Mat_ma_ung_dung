// CHỨC NĂNG: Minh họa RC4: sinh dòng khóa, XOR với bản rõ để mã hóa và XOR lại để giải mã.
#include<iostream>
#include<string>
using namespace std;

// Cùng một hàm cho hai chiều: C=P XOR dòng_khóa; P=C XOR dòng_khóa.
string RC4(string P,string K){
    
    // S là hoán vị các giá trị 0..255; T lặp lại các byte của khóa cho đủ 256 vị trí.
    unsigned char T[256],S[256];
    // i,j là hai chỉ số chạy trong S; t là vị trí chọn byte đầu ra; k là byte khóa được sinh ở bước hiện tại.
    int i,j,t,k;
    
    // Khởi tạo 256 phần tử: S ban đầu là dãy 0,1,...,255.
    // T là khóa được lặp tuần hoàn: nếu K ngắn hơn 256 byte thì quay lại ký tự đầu khi đi hết K.
    for(i=0;i<256;i++){
        // i%K.size() luôn chọn một vị trí trong khóa. Vì có phép chia dư cho độ dài khóa nên K không được rỗng.
        // Ép unsigned char để đọc đúng giá trị byte, kể cả khi char của compiler có dấu.
        T[i]=(unsigned char)K[i%K.size()];
        S[i]=i;
    }

    j=0;
    for(i=0;i<256;i++){
        // KSA cập nhật j dựa trên trạng thái S và byte khóa T[i]; %256 giữ j trong 0..255.
        j=(j+S[i]+T[i])%256;
        // Hoán đổi hai phần tử để trộn hoán vị S. Giá trị trong S vẫn đủ 0..255, chỉ thay đổi vị trí.
        swap(S[i],S[j]);
    }

    // Sau khi trộn khóa xong, đặt lại i,j bằng 0 trước khi bắt đầu sinh dòng khóa cho dữ liệu.
    i=0;
    j=0;
    // C tích lũy các byte kết quả. Một byte bản rõ cần đúng một byte khóa sinh ra từ PRGA.
    string C="";
    for(int x=0;x<(int)P.size();x++){
        // Mỗi byte dữ liệu: tăng i theo vòng 0..255, cập nhật j rồi đổi chỗ hai phần tử S[i],S[j].
        i=(i+1)%256;
        j=(j+S[i])%256;
        swap(S[i],S[j]);
        // Sau hoán đổi, cộng S[i] và S[j] lấy modulo 256 để chọn chỉ số t; byte khóa thực tế là S[t].
        t=(S[i]+S[j])%256;
        k=S[t];
        
        // XOR byte bản rõ với byte khóa k; kết quả có thể là byte không in được.
        C+=(char)((unsigned char)P[x]^k);
    }
    return C;
}

// main là nơi chương trình bắt đầu: nhận dữ liệu từ bàn phím, gọi các phép xử lý rồi in kết quả.
int main(){
    string P,K,C;
    cout<<"Nhap khoa K: ";
    getline(cin,K);
    // Chặn khóa rỗng ở main trước khi gọi RC4, tránh phép i%0 trong phần khởi tạo T.
    if(K.size()==0){
        cout<<"Khoa khong duoc rong!";
        return 0;
    }
    cout<<"Nhap plaintext: ";
    // Đọc toàn bộ dòng bản rõ, có thể gồm dấu cách; P.size() là số byte cần mã hóa.
    getline(cin,P);
    C=RC4(P,K);
    // In số thay vì in trực tiếp bản mã vì nhiều byte không thể hiện thành chữ.
    // (unsigned char) loại dấu âm của char, sau đó int làm cout in giá trị số 0..255.
    cout<<"Ciphertext (ma ASCII): ";
    for(int i=0;i<(int)C.size();i++)
        cout<<(int)(unsigned char)C[i]<<" ";
    cout<<endl;
    // Gọi RC4 lần nữa với cùng khóa để tạo lại đúng dòng khóa ban đầu.
    // Vì (P XOR k) XOR k=P, XOR bản mã với dòng khóa đó sẽ lấy lại bản rõ.
    cout<<"Giai ma: "<<RC4(C,K)<<endl;
    return 0;
}

/*
INPUT NHẬP KHI CHƯƠNG TRÌNH CHẠY
Nhập lần lượt theo các lời nhắc; gõ xong mỗi dòng thì nhấn Enter:
1. Khóa K (một dòng không rỗng): nhập Key
2. Bản rõ plaintext (một dòng, có thể có dấu cách): nhập Plaintext

Bộ input mẫu (nhập từng dòng):
Key
Plaintext
*/
