#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;
        vector<char> a(n + 1);
        for (int i = 1; i <= n; i++)
        {
            cin >> a[i];
        }
        vector<int> b(m + 1);
        for (int i = 1; i <= m; i++)
        {
            cin >> b[i];
        }
        int current = 1;
        int black = 1;
        vector<int> blacks;
        for (int i = 0; i <= n; i++)
        {
            if (current == b[black])
            {
                blacks.push_back(current);
                black++;
            }
            if (a[i] == 'A')
            {
                current++;
                blacks.push_back(current);
            }
            else
            {
                while ((current + 1) == b[black])
                {
                    current++;
                    blacks.push_back(black);
                    black++;
                }
                current++;
                blacks.push_back(current);
                current++;
            }
        }
        for (int i = 0; i < blacks.size(); i++)
        {
            cout << blacks[i] << " ";
        }
        cout << "" << endl;
    }
    return 0;
}