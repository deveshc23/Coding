// #include <bits/stdc++.h>
// using namespace std;

// int countpaths(int i, int j, int n, vector<vector<int>> &grid, vector<vector<int>> &dp)
// {
//     if (i == 0 && j == 0)
//         return 1;
//     if (i < 0 || j < 0 || grid[i][j] == 0)
//         return 0;
//     if (dp[i][j] != -1)
//         return dp[i][j];
//     return dp[i][j] = countpaths(i - 1, j, n, grid, dp) + countpaths(i, j - 1, n, grid, dp);
// }
// int main()
// {
//     int n;
//     cin >> n;
//     vector<vector<int>> grid(n, vector<int>(n, 0));
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             char c;
//             cin >> c;
//             if (c == '.')
//             {
//                 grid[i][j] = 1;
//             }
//             else
//             {
//                 grid[i][j] = 0;
//             }
//         }
//     }
//     vector<vector<int>> dp(n, vector<int>(n, -1));
//     cout << countpaths(n - 1, n - 1, n, grid, dp) << endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> grid(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            char c;
            cin >> c;
            if (c == '.')
            {
                grid[i][j] = 1;
            }
            else
            {
                grid[i][j] = 0;
            }
        }
    }
    if (grid[0][0] == 0 || grid[n - 1][n - 1] == 0)
    {
        cout << 0 << endl;
        return 0;
    }
    vector<vector<int>> dp(n, vector<int>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == 0)
                continue;
            if (i > 0)
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % 1000000007;
            if (j > 0)
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % 1000000007;
        }
    }
    cout << dp[n - 1][n - 1] << endl;
    return 0;
}