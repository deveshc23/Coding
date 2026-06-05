#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        vector<long long> a(n);
        long long count_odd = 0;
        for (long long i = 0; i < n; i++)
        {
            cin >> a[i];
            if (a[i] % 2 != 0)
                count_odd++;
        }
        if (count_odd)
        {
            cout << 2 << endl;
            continue;
        }
        else
        {
            vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
            for (long long i = 0; i < primes.size(); i++)
            {
                for (long long j = 0; j < n; j++)
                {
                    if (a[j] % primes[i] != 0)
                    {
                        cout << primes[i] << endl;
                        i = primes.size(); // to break outer loop
                        break;
                    }
                }
            }
            continue;
        }
    }
    return 0;
}