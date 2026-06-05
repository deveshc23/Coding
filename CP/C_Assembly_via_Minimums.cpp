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
        vector<int> a(n * (n - 1) / 2);
        map<int, int> freq;
        for (int i = 0; i < n * (n - 1) / 2; i++)
        {
            cin >> a[i];
            freq[a[i]]++;
        }
        int start = n - 1;
        vector<int> ans;
        for (auto &it : freq)
        {
            int val = it.first;

            while (it.second > 0)
            {
                ans.push_back(val);

                it.second -= start;

                start--;
            }
        }
        int last = ans.back();
        ans.push_back(last);
        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
