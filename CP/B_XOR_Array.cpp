#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, l, r;
        cin >> n >> l >> r;
        vector<int> Pre(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            Pre[i] = i;
        }
        Pre[r] = Pre[l - 1];
        vector<int> ans;
        for (int i = 1; i <= n; i++)
        {
            int a = Pre[i] ^ Pre[i - 1];
            ans.push_back(a);
        }
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}