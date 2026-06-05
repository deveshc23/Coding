#include <bits/stdc++.h>
using namespace std;
int main()
{

    int t;
    if (cin >> t)
    {
        while (t--)
        {
            string r;
            cin >> r;

            for (char c : r)
            {
                assert(c == 's' || c == 'u');
            }

            int n = r.length();
            int total_u = 0;
            for (char c : r)
            {
                if (c == 'u')
                    total_u++;
            }

            int kept_u = 0;
            bool last_was_kept = false;

            for (int i = 1; i < n - 1; ++i)
            {
                if (r[i] == 'u')
                {
                    if (!last_was_kept)
                    {
                        kept_u++;
                        last_was_kept = true;
                    }
                    else
                    {
                        last_was_kept = false;
                    }
                }
                else
                {
                    last_was_kept = false;
                }
            }

            cout << (total_u - kept_u) << "\n";
        }
    }
    return 0;
}