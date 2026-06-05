#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        vector<int> present(n + 1, 0);
        for (int x : a)
            present[x] = 1;
        const int INF = 1e9;
        vector<int> dp(n + 1, INF);

        for (int v = 1; v <= n; v++)
        {
            if (present[v])
                dp[v] = 1;
        }
        for (int v = 1; v <= n; v++)
        {
            if (!present[v])
                continue;
            for (int x = 1; x <= n / v; x++)
            {
                if (dp[x] != INF)
                {
                    dp[x * v] = min(dp[x * v], dp[x] + 1);
                }
            }
        }

        for (int i = 1; i <= n; i++)
        {
            if (dp[i] == INF)
                cout << -1;
            else
                cout << dp[i];
            if (i < n)
                cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
