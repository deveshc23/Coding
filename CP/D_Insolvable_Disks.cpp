#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n;
    if (!(cin >> n))
        return;
    vector<long long> x(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> x[i];
    }

    if (n < 2)
    {
        cout << 0 << "\n";
        return;
    }

    long long ans = 0;
    int curr = 0;
    const long long INF = 4e18;
    while (curr < n - 1)
    {
        long long L = 0;
        long long R = INF;
        long long offset = 0;
        int sign = 1;

        int best_len = 0;
        for (int i = curr; i < n - 1; ++i)
        {
            long long g = x[i + 1] - x[i];
            offset = g - offset;
            sign = -sign;
            if (sign == 1)
            {
                L = max(L, -offset);
            }
            else
            {
                R = min(R, offset);
            }
            if (L >= R)
            {
                break;
            }
            bool can_terminate = false;

            if (i == n - 2)
            {
                can_terminate = true;
            }
            else
            {
                long long next_g = x[i + 2] - x[i + 1];
                long long min_r;
                if (sign == 1)
                {
                    min_r = offset + L;
                }
                else
                {
                    min_r = offset - R;
                }

                if (min_r < next_g)
                {
                    can_terminate = true;
                }
            }

            if (can_terminate)
            {
                best_len = (i - curr + 1);
            }
        }

        if (best_len == 0)
        {
            curr++;
        }
        else
        {
            ans += best_len;
            curr += best_len + 1;
        }
    }

    cout << ans << "\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t)
    {
        while (t--)
        {
            solve();
        }
    }
    return 0;
}