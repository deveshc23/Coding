#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ll t;
    cin >> t;
    
    while (t--) {
        ll n, m;
        cin >> n >> m;
        vector<ll> a(n);
        for (ll i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<ll> b(m);
        for (ll i = 0; i < m; i++) {
            cin >> b[i];
        }
        sort(b.begin(), b.end());
        a[0] = min(a[0], b[0]-a[0]);
        for(ll i=1; i<n; i++){
        // a[i]+a[i-1] se leke 2*a[i]
        // if(a[i]>=a[i-1]){
            ll x = lower_bound(b.begin(), b.end(), a[i]+a[i-1]) - b.begin();
            if(x==m){
                continue;
            }
            // if(b[x]<=2*a[i]){
            //     a[i] = b[x]-a[i];
            // }
            // else{
            //     a[i] = 2*a[i];
            // }
            if(min(a[i],b[x]-a[i])>=a[i-1]){
                a[i] = min(a[i],b[x]-a[i]);
            }
            else{
                a[i] = max(a[i],b[x]-a[i]);
            }
        }
        //check if sorted
        bool flag=0;
        for(ll i=1; i<n; i++){
            if(a[i]<a[i-1]){
                cout<<"NO"<<endl;
                flag=1;
                break;
            }
        }
        if(flag==1){
            continue;
        }
        cout<<"YES"<<endl;
    }

    return 0;
}