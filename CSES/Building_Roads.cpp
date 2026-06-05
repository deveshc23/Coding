#include <bits/stdc++.h>
using namespace std;

class DisjointSet
{
    vector<int> parent, size;

public:
    DisjointSet(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int findparent(int u)
    {
        if (parent[u] == u)
        {
            return u;
        }
        return parent[u] = findparent(parent[u]);
    }
    void unionbysize(int u, int v)
    {
        int pu = findparent(u);
        int pv = findparent(v);
        if (pu == pv)
        {
            return;
        }
        if (size[pu] < size[pv])
        {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else
        {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};
int main()
{
    // 1. ADD FAST I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    DisjointSet ds(n);
    vector<pair<int, int>> edges(m);

    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].first >> edges[i].second;
        ds.unionbysize(edges[i].first - 1, edges[i].second - 1);
    }

    vector<int> components;
    for (int i = 0; i < n; i++)
    {
        if (ds.findparent(i) == i)
        {
            components.push_back(i);
        }
    }
    cout << components.size() - 1 << "\n";
    for (int i = 1; i < components.size(); i++)
    {
        cout << components[0] + 1 << " " << components[i] + 1 << "\n";
    }

    return 0;
}