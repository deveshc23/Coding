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
        bool has2026 = false;
        bool has2025 = false;

        for (int i = 0; i < n - 3; i++)
        {
            if (s.substr(i, 4) == "2026")
            {
                has2026 = true;
            }
            if (s.substr(i, 4) == "2025")
            {
                has2025 = true;
            }
        }

        if (has2026 || !has2025)
        {
            cout << 0 << endl;
        }
        else
        {
            cout << 1 << endl;
        }
    }
}