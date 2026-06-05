#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Elf
{
    int val;
    int id;
    bool operator<(const Elf &other) const
    {
        return val > other.val;
    }
};

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<Elf> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].val;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end());

    if (2 * m > n)
    {
        cout << -1 << endl;
        return;
    }

    vector<pair<int, int>> ops;

    if (m > 0)
    {
        int victim_idx = 2 * m - 1;
        for (int i = 2 * m; i < n; i++)
        {
            ops.push_back({a[i].id, a[victim_idx].id});
        }
        for (int i = 0; i < m; i++)
        {
            ops.push_back({a[i].id, a[i + m].id});
        }
    }
    else
    {
        int sum = 0;
        for (int i = 1; i < n; i++)
            sum += a[i].val;

        if (sum < a[0].val)
        {
            cout << -1 << endl;
            return;
        }

        if (n == 2)
        {
            cout << -1 << endl;
            return;
        }

        Elf T = a[1];
        Elf S = a[n - 1];

        vector<Elf> candidates;
        for (int i = 2; i < n - 1; i++)
            candidates.push_back(a[i]);

        vector<Elf> C, F;
        int current_dmg = S.val;
        for (auto &e : candidates)
            current_dmg += e.val;

        int idx = 0;
        while (current_dmg >= a[0].val && idx < candidates.size())
        {
            current_dmg -= candidates[idx].val;
            C.push_back(candidates[idx]);
            idx++;
        }
        for (; idx < candidates.size(); idx++)
        {
            F.push_back(candidates[idx]);
        }

        if (!C.empty())
        {
            ops.push_back({C[0].id, S.id});
            int current_used = C[0].id;
            for (size_t k = 1; k < C.size(); k++)
            {
                ops.push_back({C[k].id, current_used});
                current_used = C[k].id;
            }
            ops.push_back({a[0].id, current_used});
        }
        else
        {
            ops.push_back({a[0].id, S.id});
        }

        for (auto &e : F)
        {
            ops.push_back({e.id, a[0].id});
        }

        ops.push_back({T.id, a[0].id});
    }

    cout << ops.size() << endl;
    for (auto &p : ops)
    {
        cout << p.first << " " << p.second << endl;
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
