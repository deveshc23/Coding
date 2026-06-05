#include <bits/stdc++.h>
using namespace std;
void bfs(int start, vector<vector<int>> &adj, vector<int> &team)
{
    queue<int> q;
    q.push(start);
    team[start] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (auto it : adj[u])
        {
            if (team[it] == -1)
            {
                team[it] = 3 - team[u];
                q.push(it);
            }
            else if (team[it] == team[u])
            {
                cout << "IMPOSSIBLE\n";
                exit(0);
            }
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
    vector<int> team(n, -1);
    for (int i = 0; i < n; i++)
    {
        if (team[i] == -1)
        {
            bfs(i, adj, team);
        }
    }
    for (int i = 0; i < n; i++)
    {
        cout << team[i] << " ";
    }
    cout << endl;
    return 0;
}