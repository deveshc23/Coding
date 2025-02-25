#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ll n, k;
    cin >> n >> k;
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    ll T = n - 1;
    ll sum_total = (k - 1) * k / 2;
    if (sum_total < T) {
        cout << -1 << endl;
        return 0;
    }
    ll low = 1;
    ll high = min(k - 1, T);
    ll ans = -1;
    while (low <= high) {
        ll mid = (low + high) / 2;
        ll S_min = mid * (mid + 1) / 2;
        ll S_max = mid * (2 * k - mid - 1) / 2;

        if (S_min > T) {
            high = mid - 1;
        } else if (S_max < T) {
            low = mid + 1;
        } else {
            ans = mid;
            high = mid - 1;
        }
    }
    if (ans != -1) {
        cout << ans << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}