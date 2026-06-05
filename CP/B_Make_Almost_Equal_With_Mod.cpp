#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool check(vector<ll> &arr, ll k)
{
    set<ll> s;

    for (int i = 0; i < arr.size(); i++)
    {
        s.insert(arr[i] % k);
    }

    return s.size() == 2;
}

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        int n;
        cin >> n;

        vector<ll> arr(n);

        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        ll g = 0;

        for (int i = 1; i < n; i++)
        {
            g = __gcd(g, abs(arr[i] - arr[0]));
        }

        ll k = 2 * g;

        cout << k << endl;
    }

    return 0;
}