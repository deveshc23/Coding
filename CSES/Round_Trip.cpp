#include <bits/stdc++.h>
using namespace std;
void dfs(int start, vector<vector<int>> &adj, vector<int> &visited, vector<int> &parent)
{
    visited[start] = 1;
    for (auto it : adj[start])
    {
        if (visited[it] == 0)
        {
            parent[it] = start;
            dfs(it, adj, visited, parent);
        }
        else if (parent[start] != it)
        {
            vector<int> path;
            path.push_back(it);
            int curr = start;
            while (curr != it)
            {
                path.push_back(curr);
                curr = parent[curr];
            }
            path.push_back(it);
            cout << path.size() << endl;
            for (auto it : path)
            {
                cout << it + 1 << " ";
            }
            cout << endl;
            exit(0);
        }
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }
    vector<int> visited(n, 0);
    vector<int> parent(n, -1);
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == 0)
        {
            dfs(i, adj, visited, parent);
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}