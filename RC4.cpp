#include <bits/stdc++.h>
using namespace std;

string RC4Process(const string& input, const string& key)
{
    if (key.empty())
    {
        throw invalid_argument("Khoa khong duoc de trong.");
    }

    vector<unsigned char> S(256), T(256);
    for (int i = 0; i < 256; i++)
    {
        T[i] = static_cast<unsigned char>(key[i % key.size()]);
        S[i] = static_cast<unsigned char>(i);
    }

    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + T[i]) % 256;
        swap(S[i], S[j]);
    }

    string output;
    output.reserve(input.size());

    int i = 0;
    j = 0;
    for (size_t x = 0; x < input.size(); x++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);

        int t = (S[i] + S[j]) % 256;
        unsigned char result = static_cast<unsigned char>(input[x]) ^ S[t];
        output.push_back(static_cast<char>(result));
    }

    return output;
}

int main()
{
    string P, K;
    cout << "Nhap chuoi plaintext: ";
    getline(cin, P);
    cout << "Nhap chuoi K = ";
    getline(cin, K);

    if (K.empty())
    {
        cout << "Khoa khong duoc de trong." << endl;
        return 0;
    }

    string C = RC4Process(P, K);
    string D = RC4Process(C, K);

    cout << "Chuoi ma hoa: " << C << endl;
    cout << "Chuoi giai ma: " << D << endl;
    return 0;
}