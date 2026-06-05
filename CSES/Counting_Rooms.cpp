#include <bits/stdc++.h>
using namespace std;

void dfs(int i, int j, int n, int m, vector<vector<char>> &a, vector<vector<int>> &visited)
{
    if (i < 0 || j < 0 || i >= n || j >= m || a[i][j] == '#' || visited[i][j] == 1)
    {
        return;
    }
    visited[i][j] = 1;
    dfs(i + 1, j, n, m, a, visited);
    dfs(i - 1, j, n, m, a, visited);
    dfs(i, j + 1, n, m, a, visited);
    dfs(i, j - 1, n, m, a, visited);
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> visited(n, vector<int>(m, 0));
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i][j] == '.' && visited[i][j] == 0)
            {
                count++;
                dfs(i, j, n, m, a, visited);
            }
        }
    }
    cout << count << endl;
    return 0;
}