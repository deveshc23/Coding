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
        vector<string> a(n);
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        string s;
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                s += a[i];
            }
            else
            {
                string temp1 = a[i] + s;
                string temp2 = s + a[i];
                if (temp1 < temp2)
                {
                    s = temp1;
                }
                else
                {
                    s = temp2;
                }
            }
        }
        cout << s << endl;
    }
    return 0;
}