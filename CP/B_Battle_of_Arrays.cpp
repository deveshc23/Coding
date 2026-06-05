#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        priority_queue<long long> qa, qb;

        for (int i = 0; i < n; i++)
        {
            long long x;
            cin >> x;
            qa.push(x);
        }

        for (int i = 0; i < m; i++)
        {
            long long x;
            cin >> x;
            qb.push(x);
        }

        while (!qa.empty() && !qb.empty())
        {
            long long a = qa.top();
            long long b = qb.top();
            qb.pop();

            if (b > a)
                qb.push(b - a);

            if (qb.empty())
            {
                cout << "Alice\n";
                break;
            }

            b = qb.top();
            a = qa.top();
            qa.pop();

            if (a > b)
                qa.push(a - b);

            if (qa.empty())
            {
                cout << "Bob\n";
                break;
            }
        }
    }
    return 0;
}
