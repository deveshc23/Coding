#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int sum_diff = 0;
    vector<int> diff(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        diff[i] = abs(12 - a[i]) % 12;
        sum_diff += diff[i];
    }
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++)
    {
        pair<int, int> p;
        cin >> p.first >> p.second;
        adj[p.first].push_back(p.second);
        adj[p.second].push_back(p.first);
    }
    vector<int> length_adj(n + 1, 0);
    int sum_length = 0;
    for (int i = 1; i <= n; i++)
    {
        length_adj[i] = adj[i].size();
        sum_length += length_adj[i];
    }
    if (sum_length == (sum_diff + 1))
    {
        cout << 1 << endl;
    }
    else
    {
        cout << 0 << endl;
    }
    return 0;
}