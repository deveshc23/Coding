#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            if (i % 2 == 0)
            {
                dp[i] = dp[i / 2] + 1;
            }
            else
            {
                dp[i] = dp[i - 1] + 1;
            }
        }
        int count = 0;
        for (int i = 1; i <= n; i++)
        {
            if (dp[i] > k)
                count++;
        }
        cout << count << endl;
    }
    return 0;
}