#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long t;
    cin >> t;
    while (t--)
    {
        long long n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        long long length = s.length();
        long long top = 0, bottom = 0, both = 0;
        for (long long i = 0; i < length; i++)
        {
            if (s[i] == '0')
            {
                top++;
            }
            else if (s[i] == '1')
            {
                bottom++;
            }
            else
            {
                both++;
            }
        }
        long long maxtop = top + both;
        long long maxbottom = bottom + both;
        // cout << maxtop << " " << maxbottom << endl;
        for (long long i = 1; i <= n; i++)
        {
            if (i <= top || i > (n - bottom) || n == (both + top + bottom))
                cout << "-";
            else if (i <= maxtop || i > (n - maxbottom))
                cout << "?";
            else
                cout << "+";
        }
        cout << endl;
    }
    return 0;
}