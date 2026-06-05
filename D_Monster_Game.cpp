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
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < n; i++)
            cin >> b[i];
        sort(a.begin(), a.end(), greater<long long>());
        vector<long long> pref(n);
        pref[0] = b[0];
        for (int i = 1; i < n; i++)
            pref[i] = pref[i - 1] + b[i];
        long long ans = 0;
        for (int k = 1; k <= n; k++)
        {
            long long x = a[k - 1];
            long long hits = k;

            int levels = upper_bound(pref.begin(), pref.end(), hits) - pref.begin();
            ans = max(ans, x * levels);
        }

        cout << ans << "\n";
    }
    return 0;
}
