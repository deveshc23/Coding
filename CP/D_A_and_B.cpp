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
        vector<char> a(n);
        for (long long i = 0; i < n; i++)
            cin >> a[i];
        vector<long long> prefixa(n, 0), suffixa(n, 0);
        long long counta_left = 0;
        if (a[0] == 'a')
            counta_left = 1;
        for (long long i = 1; i < n; i++)
        {
            if (a[i] == 'b')
            {
                prefixa[i] = prefixa[i - 1] + counta_left;
            }
            else
            {
                counta_left++;
                prefixa[i] = prefixa[i - 1];
            }
        }
        long long counta_right = 0;
        if (a[n - 1] == 'a')
            counta_right = 1;
        for (long long i = n - 2; i >= 0; i--)
        {
            if (a[i] == 'b')
            {
                suffixa[i] = suffixa[i + 1] + counta_right;
            }
            else
            {
                counta_right++;
                suffixa[i] = suffixa[i + 1];
            }
        }
        long long min_sum_prefix_suffix = prefixa[0] + suffixa[0];
        for (long long i = 1; i < n; i++)
        {
            min_sum_prefix_suffix = min(min_sum_prefix_suffix, prefixa[i] + suffixa[i]);
        }
        // now same thing for b
        vector<long long> prefixb(n, 0), suffixb(n, 0);
        long long countb_left = 0;
        if (a[0] == 'b')
            countb_left = 1;
        for (long long i = 1; i < n; i++)
        {
            if (a[i] == 'a')
            {
                prefixb[i] = prefixb[i - 1] + countb_left;
            }
            else
            {
                countb_left++;
                prefixb[i] = prefixb[i - 1];
            }
        }
        long long countb_right = 0;
        if (a[n - 1] == 'b')
            countb_right = 1;
        for (long long i = n - 2; i >= 0; i--)
        {
            if (a[i] == 'a')
            {
                suffixb[i] = suffixb[i + 1] + countb_right;
            }
            else
            {
                countb_right++;
                suffixb[i] = suffixb[i + 1];
            }
        }
        long long min_sum_prefix_suffix_b = prefixb[0] + suffixb[0];
        for (long long i = 1; i < n; i++)
        {
            min_sum_prefix_suffix_b = min(min_sum_prefix_suffix_b, prefixb[i] + suffixb[i]);
        }
        cout << min(min_sum_prefix_suffix, min_sum_prefix_suffix_b) << endl;
    }
    return 0;
}