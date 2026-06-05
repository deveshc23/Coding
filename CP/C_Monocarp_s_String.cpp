#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        string s;
        cin >> s;
        long long counta = 0;
        long long countb = 0;
        for (long long i = 0; i < n; i++)
        {
            if (s[i] == 'a')
            {
                counta++;
            }
            else
            {
                countb++;
            }
        }
        long long target = counta - countb;
        if (target == 0)
        {
            cout << 0 << endl;
            continue;
        }
        vector<long long> diff(n + 1, 0);
        for (long long i = 0; i < n; i++)
        {
            if (s[i] == 'a')
            {
                diff[i + 1] = diff[i] + 1;
            }
            else
            {
                diff[i + 1] = diff[i] - 1;
            }
        }
        unordered_map<long long, long long> loc;
        loc[0] = 0;
        long long minlen = n;
        for (long long i = 1; i <= n; i++)
        {
            long long req = diff[i] - target;
            if (loc.find(req) != loc.end())
            {
                minlen = min(minlen, (i - loc[req]));
            }
            loc[diff[i]] = i;
        }
        if (minlen == n)
        {
            cout << -1 << endl;
        }
        else
        {
            cout << minlen << endl;
        }
    }
    return 0;
}