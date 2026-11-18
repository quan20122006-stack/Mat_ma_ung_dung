#include <bits/stdc++.h>
using namespace std;
int main()
{
    /*lap trinh nhap 1 so nguyen p tu ban phim. In ra tat ca ca phan tu nguyen thuy cua p */
    int p;
    cout << "Nhap so p: ";
    cin >> p;
    if (p <= 1)
        return 0;
    bool vis[100000];
    int res[100000];
    int cnt = 0;
    for (int a = 1; a < p; a++)
    {
        for (int k = 0; k < p; k++)
            vis[k] = false;
        int u = 0;
        long long cur = 1;
        for (int i = 1; i < p; i++)
        {
            cur = (cur * a) % p;
            if (!vis[cur])
            {
                vis[cur] = true;
                u++;
            }
        }
        if (u == p - 1)
            res[cnt++] = a;
    }
    for (int i = 0; i < cnt; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
}