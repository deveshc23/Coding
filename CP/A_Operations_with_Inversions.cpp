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
        vector<int> a(n), sup(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        sup[0] = a[0];
        for (int i = 1; i < n; i++)
        {
            sup[i] = max(sup[i - 1], a[i]);
        }
        int count = 0;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != sup[i])
            {
                count++;
            }
        }
        cout << count << endl;
    }
}