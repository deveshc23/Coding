#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    string s;
    cin >> s;
    ll nb, ns, nc;
    cin >> nb >> ns >> nc;
    ll pb, ps, pc;
    cin >> pb >> ps >> pc;
    ll ruble;
    cin >> ruble;

    ll a = 0, b = 0, c = 0;
    for (auto &ch : s) {
        if (ch == 'B') a++;
        else if (ch == 'S') b++;
        else c++;
    }

    ll low = 0, high = ruble + 300;//for buffer

    while (low <= high) {
        ll mid = low + (high - low) / 2;
        ll z = 0;
        ll r1 = max(mid * a - nb, z);
        ll r2 = max(mid * b - ns, z);
        ll r3 = max(mid * c - nc, z);

        ll price = r1 * pb + r2 * ps + r3 * pc;
        if (price <= ruble) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    cout << high;
    return 0;
}
