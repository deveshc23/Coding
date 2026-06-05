#include <iostream>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, s, x;
        cin >> n >> s >> x;

        long long current_sum = 0;
        for (int i = 0; i < n; ++i)
        {
            int a;
            cin >> a;
            current_sum += a;
        }

        if (s >= current_sum && (s - current_sum) % x == 0)
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
