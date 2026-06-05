#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n, k;
        cin >> n >> k;
        queue<long long> q;
        unordered_map<long long, int> dist;
        q.push(n);
        dist[n] = 0;
        int ans = -1;
        while (!q.empty())
        {
            long long cur = q.front();
            q.pop();
            if (cur == k)
            {
                ans = dist[cur];
                break;
            }
            if (cur < k || cur == 0)
                continue;

            if (cur % 2 == 0)
            {
                if (!dist.count(cur / 2))
                {
                    dist[cur / 2] = dist[cur] + 1;
                    q.push(cur / 2);
                }
            }
            else
            {
                for (long long nxt : {(cur - 1) / 2, (cur + 1) / 2})
                {
                    if (!dist.count(nxt))
                    {
                        dist[nxt] = dist[cur] + 1;
                        q.push(nxt);
                    }
                }
            }
        }

        cout << ans << endl;
    }
}
