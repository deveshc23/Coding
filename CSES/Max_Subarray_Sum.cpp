#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    vector<long long> a(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    long long max_sum = a[0];
    for (long long i = 1; i < n; i++)
    {
        if (a[i - 1] > 0)
            a[i] += a[i - 1];
        else
            a[i] = a[i];
        max_sum = max(max_sum, a[i]);
    }
    cout << max_sum << endl;
    return 0;
}