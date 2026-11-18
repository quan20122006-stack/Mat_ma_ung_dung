#include <bits/stdc++.h>
using namespace std;
int main()
{
    /* Nhap so nguyen p. Voi moi a thuoc [1, p-1], in ra a, a^2, ..., a^(p-1) trong modul p */
    int p;
    cout << "Nhap so p: ";
    cin >> p;
    if (p <= 1)
        return 0;
    cout << "\nBang luy thua cua a trong module " << p << ":\n";
    for (int a = 1; a < p; a++)
    {
        cout << "a = " << a << ": ";
        long long cur = 1;
        for (int i = 1; i < p; i++)
        {
            cur = (cur * a) % p; // cur = a^i mod p
            cout << cur << " ";
        }
        cout << endl;
    }
}