#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n, m;
    cin >> n >> m;
    long long a[n];
    for (long long i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 2, 0));
    for (long long i = 1; i <= m; i++)
    {
        if (a[0] == 0 || a[0] == i)
        {
            dp[1][i] = 1;
        }
    }
    for (long long i = 2; i <= n; i++)
    {
        for (long long j = 1; j <= m; j++)
        {
            if (a[i - 1] == 0 || a[i - 1] == j)
            {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1]) % 1000000007;
            }
        }
    }
    long long answer = 0;
    for (long long i = 1; i <= m; i++)
    {
        answer = (answer + dp[n][i]) % 1000000007;
    }
    cout << answer << endl;
    return 0;
}