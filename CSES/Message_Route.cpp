#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        edges.push_back({u, v});
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> dist(n + 1, -1);
    vector<int> parent(n + 1, -1);
    queue<int> q;
    dist[1] = 0;
    q.push(1);
    ;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto it : adj[u])
        {
            if (dist[it] == -1)
            {
                dist[it] = dist[u] + 1;
                parent[it] = u;
                q.push(it);
            }
        }
    }
    if (dist[n] == -1)
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        cout << dist[n] + 1 << endl;
        vector<int> path;
        int curr = n;
        while (curr != -1)
        {
            path.push_back(curr);
            curr = parent[curr];
        }
        reverse(path.begin(), path.end());
        for (auto it : path)
        {
            cout << it << " ";
        }
        cout << endl;
    }
    return 0;
}