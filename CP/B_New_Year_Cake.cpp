#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll even_sum(ll n)
{
    ll k = (n + 1) / 2;
    ll p = 1;
    for (ll i = 0; i < k; i++)
        p *= 4;
    return (p - 1) / 3;
}

ll odd_sum(ll n)
{
    ll k = n / 2;
    ll p = 1;
    for (ll i = 0; i < k; i++)
        p *= 4;
    return 2 * (p - 1) / 3;
}

bool ok(ll n, ll a, ll b)
{
    ll e = even_sum(n);
    ll o = odd_sum(n);
    return (e <= a && o <= b) || (e <= b && o <= a);
}

int main()
{
    ll t;
    cin >> t;
    while (t--)
    {
        ll a, b;
        cin >> a >> b;

        ll lo = 1, hi = 60, ans = 0;
        while (lo <= hi)
        {
            ll mid = (lo + hi) / 2;
            if (ok(mid, a, b))
            {
                ans = mid;
                lo = mid + 1;
            }
            else
            {
                hi = mid - 1;
            }
        }
        cout << ans << '\n';
    }
}
