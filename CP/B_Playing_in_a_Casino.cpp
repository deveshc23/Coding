#include <bits/stdc++.h>
using namespace std;
long long func(vector<vector<int>> &a, int n, int m, int col)
{
    vector<int> temp;
    for (int i = 0; i < n; i++)
    {
        temp.push_back(a[i][col]);
    }
    sort(temp.begin(), temp.end());
    long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += 1LL * (2 * i + 1 - n) * temp[i];
    }
    return sum;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> a[i][j];
            }
        }
        long long ans = 0;
        for (int i = 0; i < m; i++)
        {
            ans += func(a, n, m, i);
        }
        cout << ans << endl;
    }
    return 0;
}