#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        if (m.find(y) == m.end())
        {
            m[y] = x;
        }
        else
        {
            m[y] = max(m[y], x);
        }
    }
    int count = 0;
    int last = 0;
    for (auto it = m.begin(); it != m.end(); it++)
    {
        if (it->second >= last)
        {
            count++;
            last = it->first;
        }
    }
    cout << count << endl;
    return 0;
}