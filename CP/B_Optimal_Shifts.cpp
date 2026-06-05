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

        string s;
        cin >> s;

        vector<int> a(n);
        for (int i = 0; i < n; i++)
            a[i] = s[i] - '0';

        int i = 0;
        while (i < n && a[i] != 1)
            i++;

        int last_one = i;
        int max_diff = 0;

        for (int j = i + 1; j < n; j++)
        {
            if (a[j] == 1)
            {
                max_diff = max(max_diff, j - last_one - 1);
                last_one = j;
            }
        }

        int start_zeros = i;
        int end_zeros = n - 1 - last_one;

        max_diff = max(max_diff, start_zeros + end_zeros);
        cout << max_diff << endl;
    }
    return 0;
}
