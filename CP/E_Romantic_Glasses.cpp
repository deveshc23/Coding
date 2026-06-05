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
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        set<long long> s;
        s.insert(0);
        long long prefix = 0;
        bool cfound = 0;
        for (int i = 0; i < n; i++)
        {
            if (i % 2 == 0)
            {
                prefix -= a[i];
            }
            else
            {
                prefix += a[i];
            }
            if (s.count(prefix))
            {
                cfound = true;
                break;
            }
            else
            {
                s.insert(prefix);
            }
        }
        if (cfound)
        {
            cout << "YES\n";
        }
        else
        {
            cout << "NO\n";
        }
    }
    return 0;
}