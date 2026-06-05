#include <iostream>
#include <algorithm>
using namespace std;

void solve()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, k;
        cin >> n >> k;
        if (k % 2 == 1)
        {
            for (int i = 0; i < k; ++i)
            {
                cout << n << " ";
            }
            cout << "\n";
        }
        else
        {
            int n1 = 0, n2 = 0;
            for (int i = 30; i >= 0; --i)
            {
                if (n & (1 << i))
                {
                    if (n1 <= n2)
                    {
                        n1 |= (1 << i);
                    }
                    else
                    {
                        n2 |= (1 << i);
                    }
                }
            }
            int m = min(n1, n2);
            int c = 0;
            for (int i = 30; i >= 0; --i)
            {
                if ((n & (1 << i)) == 0)
                {
                    if ((c | (1 << i)) <= m)
                    {
                        c |= (1 << i);
                    }
                }
            }
            int a = n1 | c;
            int b = n2 | c;
            if (k == 2)
            {
                cout << a << " " << b << "\n";
            }
            else
            {
                for (int i = 0; i < k - 2; ++i)
                {
                    cout << n << " ";
                }
                cout << a << " " << b << "\n";
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}