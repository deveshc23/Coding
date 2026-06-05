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
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        for (int i = 0; i < n; ++i)
            cin >> b[i];
        long long max_k = 0;
        long long min_k = 0;
        for (int i = 0; i < n; ++i)
        {
            long long option1 = max_k - a[i];
            long long option2 = min_k - a[i];
            long long option3 = b[i] - max_k;
            long long option4 = b[i] - min_k;
            long long new_max = max({option1, option2, option3, option4});
            long long new_min = min({option1, option2, option3, option4});
            max_k = new_max;
            min_k = new_min;
        }

        cout << max_k << '\n';
    }
    return 0;
}