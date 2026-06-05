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
        int min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            if (a[i] < min)
            {
                min = a[i];
            }
        }
        int second_last_min = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (a[i] > min && a[i] < second_last_min)
            {
                second_last_min = a[i];
            }
        }
        int ans = max(min, (second_last_min - min));
        cout << ans << endl;
    }
    return 0;
}