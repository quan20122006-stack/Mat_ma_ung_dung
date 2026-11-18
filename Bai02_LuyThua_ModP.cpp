#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main() {
    int p;
    cout << "Nhap p: "; cin >> p;
    if(p<2) return 0;
    for(int a=1;a<p;a++) {
        long long x=1;
        cout << "a = " << a << ": ";
        for(int i=1;i<p;i++) {
            x=x*a%p;
            cout << x << " ";
        }
        cout << "\n";
    }
}
