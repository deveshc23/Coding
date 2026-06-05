#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long MOD = 998244353;
int n, m;
int cnt[65]; // Stores count of reindeer with strength 2^i

// Helper to get bit of X. Returns 0 if idx < 0.
int get_bit(unsigned long long X, int idx)
{
    if (idx < 0)
        return 0;
    if (idx >= 62)
        return 0;
    return (X >> idx) & 1;
}

void solve_query(unsigned long long X)
{
    // dp[j][0] -> tight match (sum matches prefix of X)
    // dp[j][1] -> already greater (sum > prefix of X)
    // We only track valid counts.
    vector<vector<long long>> dp(n + 1, vector<long long>(2, 0));

    // Initial state: 0 reindeer chosen, tight match
    dp[0][0] = 1;

    // Process from strength 60 down to 0
    for (int c = 60; c >= 0; --c)
    {
        int count = cnt[c];

        // Difference arrays for range updates to next_dp
        // d0 for next state tight=0, d1 for next state tight=1
        vector<long long> d0(n + 2, 0);
        vector<long long> d1(n + 2, 0);

        for (int j = 0; j <= n; ++j)
        {
            if (dp[j][0] == 0 && dp[j][1] == 0)
                continue;

            // --- Handle tight=1 (Already Win) ---
            if (dp[j][1] > 0)
            {
                // If we are already greater, any valid choice of k keeps us greater.
                // We can pick k in [0, count], updating j to [j, j+count].
                // We must respect global limit n.
                int limit = min(n - j, count);
                if (limit >= 0)
                {
                    d1[j] = (d1[j] + dp[j][1]) % MOD;
                    d1[j + limit + 1] = (d1[j + limit + 1] - dp[j][1] + MOD) % MOD;
                }
            }

            // --- Handle tight=0 (Tight Match) ---
            if (dp[j][0] > 0)
            {
                // 1. Check Gap Bit (c - j + 1).
                // Logic dictates bit at (c - j + 1) is always 0 in our sum.
                // If X has 1 there, we put 0 < 1, so we lose. Path dies.
                int gap_bit = c - j + 1;
                if (get_bit(X, gap_bit) == 1)
                {
                    continue;
                }

                // 2. Determine L: the length of the run of 1s in X starting at bit (c - j).
                // We are placing 1s starting at c-j downwards.
                int curr = c - j;
                int L = 0;
                while (get_bit(X, curr) == 1)
                {
                    L++;
                    curr--;
                }
                // 'curr' is now the index of the first 0 in X (or negative).

                // We choose k reindeer.
                // This places 1s in range [c - j, c - j - k + 1].

                // If the "winning bit" (the first 0 in X) is at a negative index,
                // we can't actually put a 1 there (negative powers contribute 0).
                // So we can never win in this step, only match.
                if (curr < 0)
                {
                    // All valid k result in match.
                    int limit = min(count, n - j);
                    if (limit >= 0)
                    {
                        d0[j] = (d0[j] + dp[j][0]) % MOD;
                        d0[j + limit + 1] = (d0[j + limit + 1] - dp[j][0] + MOD) % MOD;
                    }
                }
                else
                {
                    // Normal case: X has a 0 at 'curr' >= 0.

                    // Option A: Pick k <= L.
                    // We only cover 1s in X (or stop before). We maintain match.
                    int limit_match = min(count, L);
                    limit_match = min(limit_match, n - j);
                    if (limit_match >= 0)
                    {
                        d0[j] = (d0[j] + dp[j][0]) % MOD;
                        d0[j + limit_match + 1] = (d0[j + limit_match + 1] - dp[j][0] + MOD) % MOD;
                    }

                    // Option B: Pick k > L.
                    // We cover the 0 at 'curr' with a 1. We become greater (Win).
                    if (count > L)
                    {
                        int start_win = L + 1;
                        int end_win = count;
                        if (j + start_win <= n)
                        {
                            end_win = min(end_win, n - j);
                            if (end_win >= start_win)
                            {
                                d1[j + start_win] = (d1[j + start_win] + dp[j][0]) % MOD;
                                d1[j + end_win + 1] = (d1[j + end_win + 1] - dp[j][0] + MOD) % MOD;
                            }
                        }
                    }
                }
            }
        }

        // Apply difference arrays
        vector<vector<long long>> next_dp(n + 1, vector<long long>(2));
        long long curr0 = 0, curr1 = 0;
        for (int j = 0; j <= n; ++j)
        {
            curr0 = (curr0 + d0[j]) % MOD;
            curr1 = (curr1 + d1[j]) % MOD;
            next_dp[j][0] = curr0;
            next_dp[j][1] = curr1;
        }
        dp = next_dp;
    }

    long long ans = 0;
    for (int j = 0; j <= n; ++j)
    {
        ans = (ans + dp[j][0] + dp[j][1]) % MOD;
    }
    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m))
        return 0;

    for (int i = 0; i < n; ++i)
    {
        int c;
        cin >> c;
        cnt[c]++;
    }

    for (int i = 0; i < m; ++i)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int x;
            cin >> x;
            cnt[x]++;
            n++;
        }
        else if (type == 2)
        {
            int x;
            cin >> x;
            cnt[x]--;
            n--;
        }
        else
        {
            unsigned long long x;
            cin >> x;
            solve_query(x);
        }
    }

    return 0;
}