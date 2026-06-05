#include <iostream>
#include <vector>

using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int l = 0;
    int r = n - 1;
    int min_val = 1;
    int max_val = n;

    while (l <= r)
    {
        if (a[l] == min_val)
        {
            l++;
            min_val++;
        }
        else if (a[l] == max_val)
        {
            l++;
            max_val--;
        }
        else if (a[r] == min_val)
        {
            r--;
            min_val++;
        }
        else if (a[r] == max_val)
        {
            r--;
            max_val--;
        }
        else
        {
            cout << l + 1 << " " << r + 1 << "\n";
            return;
        }
    }
    cout << -1 << "\n";
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}