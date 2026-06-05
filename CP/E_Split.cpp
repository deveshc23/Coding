#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long t;
    cin >> t;
    while (t--)
    {
        long long n, k;
        cin >> n >> k;
        vector<long long> a(n);
        unordered_map<long long, long long> freq;
        for (long long i = 0; i < n; i++)
        {
            cin >> a[i];
            freq[a[i]]++;
        }
        bool breach = false;
        for (auto it : freq)
        {
            if (it.second % k != 0)
            {
                breach = true;
                break;
            }
        }
        if (breach)
        {
            cout << 0 << endl;
            continue;
        }
        long long l = 0, r = 0;
        unordered_map<long long, long long> window_freq;
        long long count = 0;
        while (l < n and r < n)
        {
            window_freq[a[r]]++;
            if (window_freq[a[r]] > freq[a[r]] / k)
            {
                while (l < r && window_freq[a[r]] > freq[a[r]] / k)
                {
                    count += (r - l);
                    window_freq[a[l]]--;
                    l++;
                }
            }
            r++;
        }
        while (l < n)
        {
            count += (r - l);
            window_freq[a[l]]--;
            l++;
        }
        cout << count << endl;
    }
    return 0;
}