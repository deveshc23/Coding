#include <bits/stdc++.h>

using namespace std;

void solve()
{
    long long n, x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;
    vector<long long> p(n);
    long long total_p = 0;
    long long min_x = 0;
    long long min_y = 0;

    bool has_zero = false;
    bool has_one = false;

    for (int i = 0; i < n; ++i)
    {
        cin >> p[i];
        total_p += p[i];
        long long req = (p[i] / 2) + 1;

        if (s[i] == '0')
        {
            min_x += req;
            has_zero = true;
        }
        else
        {
            min_y += req;
            has_one = true;
        }
    }

    bool possible = true;
    if (x + y < total_p)
        possible = false;
    if (x < min_x || y < min_y)
        possible = false;
    if (!has_zero && y < x + n)
        possible = false;
    if (!has_one && x < y + n)
        possible = false;

    if (possible)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}