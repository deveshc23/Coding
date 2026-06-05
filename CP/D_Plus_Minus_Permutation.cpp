#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        ll n, x, y;
        cin >> n >> x >> y;

        ll l = (x / __gcd(x, y)) * y;

        // unique multiples
        ll x_in = (n / x) - (n / l);
        ll y_in = (n / y) - (n / l);

        ll ans = 0;

        // largest x_in numbers
        ll cur = n;

        while (x_in--)
        {
            ans += cur;
            cur--;
        }

        // smallest y_in numbers
        cur = 1;

        while (y_in--)
        {
            ans -= cur;
            cur++;
        }

        cout << ans << endl;
    }

    return 0;
}