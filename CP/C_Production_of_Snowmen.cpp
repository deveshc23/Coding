#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> a(n), b(n), c(n);
        for (int i = 0; i < n; i++)
            cin >> a[i];
        for (int i = 0; i < n; i++)
            cin >> b[i];
        for (int i = 0; i < n; i++)
            cin >> c[i];

        long long valid_ab = 0;
        for (int s = 0; s < n; s++)
        {
            bool ok = true;
            for (int i = 0; i < n; i++)
            {
                if (a[i] >= b[(i + s) % n])
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
                valid_ab++;
        }

        long long valid_bc = 0;
        for (int s = 0; s < n; s++)
        {
            bool ok = true;
            for (int i = 0; i < n; i++)
            {
                if (b[i] >= c[(i + s) % n])
                {
                    ok = false;
                    break;
                }
            }
            if (ok)
                valid_bc++;
        }

        cout << valid_ab * valid_bc * n << "\n";
    }

    return 0;
}