#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, q;
        cin >> n >> q;
        vector<char> s(n);
        int count_a = 0;
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
            if (s[i] == 'A')
                count_a++;
        }
        if (count_a == n)
        {
            while (q--)
            {
                int num;
                cin >> num;
                cout << num << endl;
            }
            continue;
        }
        while (q--)
        {
            int num;
            int count = 0;
            cin >> num;
            int i = 0;
            while (num != 0)
            {
                count++;
                char c = s[i];
                if (c == 'B')
                {
                    num = num / 2;
                }
                else
                    num = num - 1;
                if (i == (n - 1))
                    i = 0;
                else
                    i++;
            }
            cout << count << endl;
        }
    }
    return 0;
}