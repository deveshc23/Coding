#include <bits/stdc++.h>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    int total = 1 << n;
    vector<int> p;
    vector<bool> used(total, false);

    int curr = total - 1;
    p.push_back(curr);
    used[curr] = true;

    while (curr > 0)
    {
        bool found = false;
        for (int x = 0; x < total; ++x)
        {
            if (!used[x] && (x & curr) == curr)
            {
                p.push_back(x);
                used[x] = true;
                found = true;
                break;
            }
        }
        if (!found)
        {
            for (int i = n - 1; i >= 0; --i)
            {
                if ((curr >> i) & 1)
                {
                    curr ^= (1 << i);
                    break;
                }
            }
        }
    }

    for (int i = 0; i < total; ++i)
    {
        if (!used[i])
        {
            p.push_back(i);
        }
    }

    for (int i = 0; i < total; ++i)
    {
        cout << p[i] << (i == total - 1 ? "" : " ");
    }
    cout << "\n";
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