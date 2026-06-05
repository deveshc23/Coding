#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    int startx, starty;
    vector<vector<char>> a(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> a[i][j];
            if (a[i][j] == 'A')
            {
                startx = i;
                starty = j;
            }
        }
    }
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    vector<vector<char>> path(n, vector<char>(m));
    queue<pair<int, int>> q;
    q.push({startx, starty});
    dist[startx][starty] = 0;
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        if (a[x][y] == 'B')
        {

            cout << "YES" << endl;
            cout << dist[x][y] << endl;
            string ans = "";
            while (a[x][y] != 'A')
            {
                ans += path[x][y];
                if (path[x][y] == 'D')
                {
                    x--;
                }
                else if (path[x][y] == 'U')
                {
                    x++;
                }
                else if (path[x][y] == 'R')
                {
                    y--;
                }
                else
                {
                    y++;
                }
            }
            reverse(ans.begin(), ans.end());
            cout << ans << endl;
            return 0;
        }
        if (x > 0 && a[x - 1][y] != '#' && dist[x - 1][y] == INT_MAX)
        {
            path[x - 1][y] = 'U';
            dist[x - 1][y] = dist[x][y] + 1;
            q.push({x - 1, y});
        }
        if (x < n - 1 && a[x + 1][y] != '#' && dist[x + 1][y] == INT_MAX)
        {
            path[x + 1][y] = 'D';
            dist[x + 1][y] = dist[x][y] + 1;
            q.push({x + 1, y});
        }
        if (y > 0 && a[x][y - 1] != '#' && dist[x][y - 1] == INT_MAX)
        {
            path[x][y - 1] = 'L';
            dist[x][y - 1] = dist[x][y] + 1;
            q.push({x, y - 1});
        }
        if (y < m - 1 && a[x][y + 1] != '#' && dist[x][y + 1] == INT_MAX)
        {
            path[x][y + 1] = 'R';
            dist[x][y + 1] = dist[x][y] + 1;
            q.push({x, y + 1});
        }
    }
    cout << "NO" << endl;
    return 0;
}
