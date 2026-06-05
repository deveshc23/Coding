#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tests;
    cin >> tests;

    while (tests--)
    {
        int size;
        cin >> size;

        vector<int> arr(size), index(size + 1);
        for (int i = 0; i < size; i++)
        {
            cin >> arr[i];
            index[arr[i]] = i;
        }

        int break_point = -1;
        for (int i = 0; i < size; i++)
        {
            if (arr[i] != size - i)
            {
                break_point = i;
                break;
            }
        }

        if (break_point != -1)
        {
            int needed = size - break_point;
            int where = index[needed];
            reverse(arr.begin() + break_point, arr.begin() + where + 1);
        }

        for (int i = 0; i < size; i++)
        {
            cout << arr[i];
            if (i + 1 < size)
                cout << ' ';
        }
        cout << '\n';
    }
    return 0;
}
