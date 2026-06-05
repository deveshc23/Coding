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
            cin >> a[i];
        for (int i = 1; i < n; i++)
        {
            if (a[i] == a[i - 1])
            {
                a.erase(a.begin() + i - 1);
                n--;
                i--;
            }
        }
        if (n <= 2)
        {
            cout << n << endl;
            continue;
        }
        for (int i = 1; i < n - 1; i++)
        {
            if (a[i] > a[i - 1] && a[i] < a[i + 1])
            {
                a.erase(a.begin() + i);
                n--;
                i--;
            }
            else if (a[i] < a[i - 1] && a[i] > a[i + 1])
            {
                a.erase(a.begin() + i);
                n--;
                i--;
            }
        }
        cout << n << endl;
    }
    return 0;
}