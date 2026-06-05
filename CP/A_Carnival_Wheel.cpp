#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int l, a, b;
        cin >> l >> a >> b;

        vector<bool> visited(l, false);
        int cur = a;
        int ans = a;

        while (!visited[cur])
        {
            visited[cur] = true;
            ans = max(ans, cur);
            cur = (cur + b) % l;
        }

        cout << ans << '\n';
    }
    return 0;
}
