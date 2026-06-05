// #include <bits/stdc++.h>
// using namespace std;

// int main()
// {
//     long long t;
//     cin >> t;
//     while (t--)
//     {
//         long long n, k, l, r;
//         cin >> n >> k >> l >> r;
//         vector<long long> a(n);
//         for (long long i = 0; i < n; i++)
//             cin >> a[i];
//         long long count = 0;
//         for (long long length = max(l, k); length <= r; length++)
//         {
//             long long left = 0;
//             long long right = 0;
//             unordered_map<long long, long long> freq;
//             while ((right - left + 1) <= length)
//             {
//                 freq[a[right]]++;
//                 right++;
//             }
//             right--;
//             if (right == (n - 1))
//             {
//                 if (freq.size() == k)
//                     count++;
//             }
//             else
//             {
//                 while (right < n)
//                 {
//                     if (freq.size() == k)
//                         count++;
//                     freq[a[left]]--;
//                     if (freq[a[left]] == 0)
//                         freq.erase(a[left]);
//                     left++;
//                     right++;
//                     if (right < n)
//                         freq[a[right]]++;
//                 }
//             }
//         }
//         cout << count << endl;
//     }
//     return 0;
// }

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long t;
    cin >> t;
    while (t--)
    {
        long long n, k, l, r;
        cin >> n >> k >> l >> r;
        vector<long long> a(n);
        for (long long i = 0; i < n; i++)
        {
            cin >> a[i];
        }

        long long total_count = 0;
        long long left_k = 0;
        long long left_k_minus_1 = 0;
        map<long long, long long> freq_k;         
        map<long long, long long> freq_k_minus_1; 

        for (long long right = 0; right < n; ++right)
        {
            freq_k[a[right]]++;
            freq_k_minus_1[a[right]]++;

            while (freq_k.size() > k)
            {
                freq_k[a[left_k]]--;
                if (freq_k[a[left_k]] == 0)
                {
                    freq_k.erase(a[left_k]);
                }
                left_k++;
            }

            while (freq_k_minus_1.size() > k - 1)
            {
                freq_k_minus_1[a[left_k_minus_1]]--;
                if (freq_k_minus_1[a[left_k_minus_1]] == 0)
                {
                    freq_k_minus_1.erase(a[left_k_minus_1]);
                }
                left_k_minus_1++;
            }

            long long start_k_range = left_k;
            long long end_k_range = left_k_minus_1 - 1;

            long long start_len_range = right - r + 1;
            long long end_len_range = right - l + 1;

            long long final_start = max(start_k_range, start_len_range);
            long long final_end = min(end_k_range, end_len_range);

            if (final_start <= final_end)
            {
                total_count += (final_end - final_start + 1);
            }
        }
        cout << total_count << endl;
    }
    return 0;
}