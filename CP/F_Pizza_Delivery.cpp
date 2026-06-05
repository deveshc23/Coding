#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1000000007;

ll absll(ll x) { return x < 0 ? -x : x; }

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        ll n, Ax, Ay, Bx, By;
        cin >> n >> Ax >> Ay >> Bx >> By;
        vector<ll> xs(n), ys(n);
        for (int i = 0; i < n; ++i)
            cin >> xs[i];
        for (int i = 0; i < n; ++i)
            cin >> ys[i];
        vector<pair<ll, ll> > houses(n);
        for (int i = 0; i < n; ++i)
            houses[i] = {xs[i], ys[i]};
        sort(houses.begin(), houses.end());
        vector<pair<ll, ll> > stations; // (L, R) for each distinct x
        int i = 0;
        while (i < n)
        {
            ll x = houses[i].first;
            ll min_y = houses[i].second, max_y = houses[i].second;
            i++;
            while (i < n && houses[i].first == x)
            {
                min_y = min(min_y, houses[i].second);
                max_y = max(max_y, houses[i].second);
                i++;
            }
            stations.push_back({min_y, max_y});
        }
        if (stations.empty())
        {
            ll ans = (Bx - Ax) + absll(Ay - By);
            cout << ans % MOD << "\n";
            continue;
        }
        int m = stations.size();
        // first station
        ll L = stations[0].first, R = stations[0].second;
        ll d = R - L;
        ll dpL = min(absll(Ay - L) + 2 * d, absll(Ay - R) + d);
        ll dpR = min(absll(Ay - L) + d, absll(Ay - R) + 2 * d);
        ll prevL = L, prevR = R;
        // remaining stations
        for (int idx = 1; idx < m; ++idx)
        {
            L = stations[idx].first;
            R = stations[idx].second;
            d = R - L;
            ll new_dpL = min(
                dpL + min(absll(prevL - L) + 2 * d, absll(prevL - R) + d),
                dpR + min(absll(prevR - L) + 2 * d, absll(prevR - R) + d));
            ll new_dpR = min(
                dpL + min(absll(prevL - L) + d, absll(prevL - R) + 2 * d),
                dpR + min(absll(prevR - L) + d, absll(prevR - R) + 2 * d));
            dpL = new_dpL;
            dpR = new_dpR;
            prevL = L;
            prevR = R;
        }
        ll vertical = min(dpL + absll(prevL - By), dpR + absll(prevR - By));
        ll horizontal = Bx - Ax;
        ll ans = horizontal + vertical;
        cout << ans % MOD << "\n";
    }
    return 0;
}