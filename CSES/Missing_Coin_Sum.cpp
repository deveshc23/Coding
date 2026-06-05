#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    vector<long long> coins(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> coins[i];
    }
    sort(coins.begin(), coins.end());
    long long S = 0;
    for (auto i : coins)
    {
        long long val = i;
        if (val > S + 1)
        {
            cout << S + 1 << endl;
            return 0;
        }
        S += val;
    }
    cout << S + 1 << endl;
}