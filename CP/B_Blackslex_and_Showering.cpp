#include <bits/stdc++.h>

using namespace std;

int main()
{
    int t;
    if (!(cin >> t))
        return 0;
    while (t--)
    {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        if (n < 2)
        {
            cout << fixed << setprecision(1) << 0 << endl;
            continue;
        }

        long long total_sum = 0;
        for (int i = 0; i < n - 1; ++i)
        {
            total_sum += abs(a[i] - a[i + 1]);
        }

        long long min_sum = total_sum;

        min_sum = min(min_sum, total_sum - abs(a[0] - a[1]));
        min_sum = min(min_sum, total_sum - abs(a[n - 1] - a[n - 2]));

        for (int i = 1; i < n - 1; ++i)
        {
            long long current_sum = total_sum - abs(a[i] - a[i - 1]) - abs(a[i] - a[i + 1]) + abs(a[i - 1] - a[i + 1]);
            min_sum = min(min_sum, current_sum);
        }

        cout << fixed << setprecision(1) << min_sum << endl;
    }
    return 0;
}