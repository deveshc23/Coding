#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve()
{
    int n;
    ll k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = a.size();

    vector<bool> is_valid(m, false);
    for (int i = 0; i < m; i++)
    {
        ll val = a[i];
        if (k / val > n + 10)
            continue;

        bool ok = true;
        for (ll mul = val; mul <= k; mul += val)
        {
            if (!binary_search(a.begin(), a.end(), mul))
            {
                ok = false;
                break;
            }
        }
        is_valid[i] = ok;
    }

    vector<ll> B;
    vector<bool> has_valid_divisor(m, false);

    for (int i = 0; i < m; i++)
    {
        if (!is_valid[i])
            continue;
        if (has_valid_divisor[i])
            continue;

        B.push_back(a[i]);

        for (ll mul = 2 * a[i]; mul <= a[m - 1]; mul += a[i])
        {
            auto it = lower_bound(a.begin(), a.end(), mul);
            if (it != a.end() && *it == mul)
            {
                has_valid_divisor[it - a.begin()] = true;
            }
        }
    }

    vector<bool> covered(m, false);
    for (ll b : B)
    {
        for (ll mul = b; mul <= a[m - 1]; mul += b)
        {
            auto it = lower_bound(a.begin(), a.end(), mul);
            if (it != a.end() && *it == mul)
            {
                covered[it - a.begin()] = true;
            }
        }
    }

    for (int i = 0; i < m; i++)
    {
        if (!covered[i])
        {
            cout << -1 << "\n";
            return;
        }
    }

    cout << B.size() << "\n";
    for (int i = 0; i < (int)B.size(); i++)
    {
        cout << B[i] << (i + 1 == (int)B.size() ? '\n' : ' ');
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}
