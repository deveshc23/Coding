#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;

        for (int i = 0; i < n; i++)
        {
            if (s[i] == '1')
            {
                for (int j = i + 1; j < n && j <= i + k; j++)
                {
                    if (s[j] == '0')
                        s[j] = '2';
                }
            }
        }

        int ans = 0;
        for (char c : s)
        {
            if (c == '0')
                ans++;
        }

        cout << ans << '\n';
    }
    return 0;
}
