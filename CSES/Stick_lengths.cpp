#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    vector<long long> a(n);
    long long sum = 0;
    for (long long i = 0; i < n; i++)
    {
        cin >> a[i];
        sum += a[i];
    }
    sort(a.begin(), a.end());
    long long median = a[n / 2];
    long long diff = 0;
    for (long long i = 0; i < n; i++)
    {
        diff += abs(a[i] - median);
    }
    cout << diff << endl;
    return 0;
}