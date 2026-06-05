#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        string s;
        cin >> s;
        int count_yes = 0;
        int count_no = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == 'Y')
            {
                count_yes++;
            }
            else
            {
                count_no++;
            }
        }
        if (count_yes > count_no)
        {
            cout << "NO\n";
        }
        else
        {
            cout << "YES\n";
        }
    }
}