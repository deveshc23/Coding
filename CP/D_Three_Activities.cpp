#include <bits/stdc++.h>
using namespace std;

int main()
{
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

        auto get_top_3 = [&](vector<int> &v)
        {
            vector<int> idx(n);
            iota(idx.begin(), idx.end(), 0);

            sort(idx.begin(), idx.end(),
                 [&](int i, int j)
                 {
                     return v[i] > v[j];
                 });

            idx.resize(3);
            return idx;
        };

        vector<int> a_top_3 = get_top_3(a);
        vector<int> b_top_3 = get_top_3(b);
        vector<int> c_top_3 = get_top_3(c);

        int max_sum = 0;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int ai = a_top_3[i];
                    int bj = b_top_3[j];
                    int ck = c_top_3[k];

                    if (ai != bj && bj != ck && ai != ck)
                    {
                        int sum = a[ai] + b[bj] + c[ck];
                        max_sum = max(max_sum, sum);
                    }
                }
            }
        }

        cout << max_sum << endl;
    }

    return 0;
}