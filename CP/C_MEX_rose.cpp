#include <bits/stdc++.h>
using namespace std;

int check_mex(vector<int> &a, vector<int> &vis, int n)
{
    for (int i = 0; i <= n; i++)
    {
        if (!vis[i])
        {
            return i;
        }
    }
    return n;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), vis(n + 1);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++)
        {
            if (a[i] <= n)
            {
                vis[a[i]] += 1;
            }
        }
        int mex = check_mex(a, vis, n);
        if (mex >= k)
            cout << vis[k] << endl;
        else
        {
            int count_0 = 0;
            for (int i = 0; i < k; i++)
            {
                if (vis[i] == 0)
                    count_0++;
            }
            cout << max(count_0, vis[k]) << endl;
        }
    }
    return 0;
}