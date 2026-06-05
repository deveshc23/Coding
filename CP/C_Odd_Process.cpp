#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<int> a(n), odd, even;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
            if (a[i] % 2 == 0)
                even.push_back(a[i]);
            else
                odd.push_back(a[i]);
        }
        if (odd.size() == 0)
        {
            for (int i = 0; i < n; i++)
                cout << 0 << " ";
            cout << endl;
            continue;
        }
        sort(odd.begin(), odd.end(), greater<int>());
        sort(even.begin(), even.end(), greater<int>());
        if (even.size() == 0)
        {
            int x = odd[0]; // largest odd
            for (int i = 0; i < n; i++)
            {
                if (i % 2 == 0)
                    cout << x << " ";
                else
                    cout << 0 << " ";
            }
            cout << endl;
            continue;
        }
        vector<int> ans;
        int sum = odd[0];
        ans.push_back(sum);

        vector<int> seq;
        for (int x : even)
        {
            sum += x;
            seq.push_back(sum);
        }

        int idx = 0;
        while ((int)ans.size() < n)
        {
            ans.push_back(seq[idx % seq.size()]);
            idx++;
        }
        if (odd.size() % 2 == 0)
        {
            ans[n - 1] = 0;
        }
        for (int x : ans)
            cout << x << " ";
        cout << endl;
    }
    return 0;
}
