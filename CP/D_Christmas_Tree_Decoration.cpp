#include <bits/stdc++.h>
using namespace std;

long long MOD = 998244353;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    const int MAXN = 100;
    static long long fact[MAXN], invFact[MAXN];

    auto power = [&](long long base, long long exp)
    {
        long long res = 1;
        base %= MOD;
        while (exp > 0)
        {
            if (exp & 1)
                res = res * base % MOD;
            base = base * base % MOD;
            exp >>= 1;
        }
        return res;
    };

    auto modInverse = [&](long long x)
    {
        return power(x, MOD - 2);
    };

    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAXN; i++)
    {
        fact[i] = fact[i - 1] * i % MOD;
        invFact[i] = modInverse(fact[i]);
    }

    auto nCr = [&](int n, int r)
    {
        if (r < 0 || r > n)
            return 0LL;
        return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
    };

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<long long> a(n + 1);
        long long sum_decorations = 0;
        for (int i = 0; i <= n; i++)
        {
            cin >> a[i];
            sum_decorations += a[i];
        }

        long long k = sum_decorations / n;
        int r = sum_decorations % n;

        long long a0 = a[0];
        long long base_demand = 0;
        int rich_count = 0, poor_count = 0;

        for (int i = 1; i <= n; i++)
        {
            if (a[i] < k)
            {
                base_demand += (k - a[i]);
                poor_count++;
            }
            else
            {
                if (a[i] == k)
                    poor_count++;
                else
                    rich_count++;
            }
        }

        if (base_demand > a0)
        {
            cout << 0 << '\n';
            continue;
        }

        long long rem_a0 = a0 - base_demand;
        long long valid_combinations = 0;

        int max_poor_in_big = min((long long)r, min((long long)poor_count, rem_a0));
        for (int i = 0; i <= max_poor_in_big; i++)
        {
            int need_rich = r - i;
            long long ways = nCr(poor_count, i) * nCr(rich_count, need_rich) % MOD;
            valid_combinations = (valid_combinations + ways) % MOD;
        }

        long long result = valid_combinations * fact[r] % MOD * fact[n - r] % MOD;
        cout << result << '\n';
    }

    return 0;
}
