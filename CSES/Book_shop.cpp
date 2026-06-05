// #include <bits/stdc++.h>
// using namespace std;

// int max_pages(int n, int x, vector<int> &prices, vector<int> &pages)
// {
//     if (n == 0 || x == 0)
//         return 0;
//     int maximum_pages = 0;
//     for (int i = 0; i < n; i++)
//     {
//         if (prices[i] <= x)
//         {
//             maximum_pages = max(pages[i] + max_pages(n - 1, x - prices[i], prices, pages), max_pages(n - 1, x, prices, pages));
//         }
//     }
//     return maximum_pages;
// }
// int main()
// {
//     int n, x;
//     cin >> n >> x;
//     vector<int> prices(n);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> prices[i];
//     }
//     vector<int> pages(n);
//     for (int i = 0; i < n; i++)
//     {
//         cin >> pages[i];
//     }
//     cout << max_pages(n, x, prices, pages) << endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, x;
    cin >> n >> x;
    vector<int> prices(n);
    for (int i = 0; i < n; i++)
    {
        cin >> prices[i];
    }
    vector<int> pages(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }
    vector<int> dp(x + 1, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = x; j >= prices[i]; j--)
        {
            dp[j] = max(dp[j], dp[j - prices[i]] + pages[i]);
        }
    }
    cout << dp[x] << endl;
    return 0;
}