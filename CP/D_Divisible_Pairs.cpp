#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long t;
    cin >> t;
    while (t--)
    {
        long long n, x, y;
        cin >> n >> x >> y;
        vector<long long> a(n);
        for (long long i = 0; i < n; i++)
            cin >> a[i];
        map<pair<long long, long long>, long long> mp;
        long long beautiful_pairs = 0;
        for (long long i = 0; i < n; i++)
        {
            long long rem_x = a[i] % x;
            long long rem_y = a[i] % y;
            long long target_x = (x - rem_x) % x;
            long long target_y = rem_y;
            beautiful_pairs += mp[{target_x, target_y}];
            mp[{rem_x, rem_y}]++;
        }
        cout << beautiful_pairs << endl;
    }
}