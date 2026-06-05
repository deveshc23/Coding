#include <bits/stdc++.h>
using namespace std;

bool check(const vector<int>& a, int target) {
    vector<int> less_nc, greater_nc, less_c, greater_c;

    for (int i = 1; i < a.size(); i++) {
        if (a[i] < target && abs(a[i]) < abs(target)) {
            less_nc.push_back(a[i]);
        }
        else if (a[i] > target && abs(a[i]) < abs(target)) {
            greater_nc.push_back(a[i]);
        }
        else if (a[i] < target && abs(a[i]) > abs(target)) {
            less_c.push_back(a[i]);
        }
        else if (a[i] > target && abs(a[i]) > abs(target)) {
            greater_c.push_back(a[i]);
        }
    }

    int diff = abs((int)greater_nc.size() - (int)less_nc.size());
    int sum = greater_c.size() + less_c.size();
    if(a.size()%2 == 0) {
        sum++;
    }
    return sum >= diff;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int target = a[0];

        // Check for both target and -target
        if (check(a, target) || check(a, -target)) {
            cout << "YES" << endl;
        }
        else {
            cout << "NO" << endl;
        }
    }
}
