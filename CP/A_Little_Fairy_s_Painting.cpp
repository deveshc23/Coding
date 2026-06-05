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
        vector<long long> a(n);
        for (long long i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        unordered_map<long long, long long> color_freq;
        for (long long i = 0; i < n; i++)
        {
            color_freq[a[i]]++;
        }
        // find the number of unique colors
        long long unique_colors = color_freq.size();
        long long ceil = 1e18;
        for (long long i = 0; i < n; i++)
        {
            if (a[i] >= unique_colors && a[i] < ceil)
            {
                ceil = a[i];
            }
        }
        cout << ceil << endl;
    }
    return 0;
}