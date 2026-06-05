#include <bits/stdc++.h>
using namespace std;

void first_run()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> adj(n + 1);
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> dist(n + 1, -1);
        queue<int> q;
        dist[1] = 0;
        q.push(1);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (int v : adj[u])
            {
                if (dist[v] == -1)
                {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }

        string colors = "rgb";
        string ans(n, ' ');
        for (int i = 1; i <= n; i++)
        {
            ans[i - 1] = colors[dist[i] % 3];
        }
        cout << ans << "\n";
    }
}

void second_run()
{
    int t;
    cin >> t;
    while (t--)
    {
        int q;
        cin >> q;
        while (q--)
        {
            int d;
            cin >> d;
            string s;
            cin >> s;
            set<char> present(s.begin(), s.end());
            if (present.size() == 1)
            {
                cout << "1\n";
            }
            else
            {
                set<char> all = {'r', 'g', 'b'};
                char missing;
                for (char c : all)
                {
                    if (!present.count(c))
                    {
                        missing = c;
                        break;
                    }
                }
                char target;
                if (missing == 'r')
                    target = 'b';
                else if (missing == 'g')
                    target = 'r';
                else
                    target = 'g';

                for (int i = 0; i < d; i++)
                {
                    if (s[i] == target)
                    {
                        cout << i + 1 << "\n";
                        break;
                    }
                }
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string first_line;
    cin >> first_line;
    if (first_line == "first")
    {
        first_run();
    }
    else
    {
        second_run();
    }
    return 0;
}