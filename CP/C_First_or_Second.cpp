#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main()
{
    int t;
    if (cin >> t)
    {
        while (t--)
        {
            int n;
            cin >> n;
            vector<long long> a(n);
            for (int i = 0; i < n; ++i)
            {
                cin >> a[i];
            }

            vector<long long> suff(n + 1, 0);
            for (int i = n - 1; i >= 0; --i)
            {
                suff[i] = suff[i + 1] - a[i];
            }

            vector<long long> dp(n, 0);
            vector<long long> inner(n, -INF);

            dp[n - 1] = 0;

            for (int i = n - 2; i >= 0; --i)
            {
                inner[i] = max(dp[i + 1], -a[i + 1] + inner[i + 1]);
                dp[i] = max(suff[i + 1], a[i] + inner[i]);
            }

            cout << dp[0] << "\n";
        }
    }
    return 0;
}