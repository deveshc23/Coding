#include <bits/stdc++.h>
using namespace std;

int pizza(int n)
{
    if (n <= 2)
        return 0;
    int m1 = n / 3;
    int m2 = n / 3;
    int m3 = n - m1 - m2;
    return pizza(m3) + m1;
}
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        cout << pizza(n) << endl;
    }
    return 0;
}