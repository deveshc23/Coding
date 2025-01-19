#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
    ll t;
    cin >> t; 
    while (t--) {
        ll n, m, k;
        cin >> n >> m >> k;
        
        vector<ll> vec(m);
        for (ll i = 0; i < m; i++) {
            cin >> vec[i];
        }
        ll sum_known=0;
        vector<ll> arr1(k);
        for (ll i = 0; i < k; i++) {
            cin >> arr1[i];
            sum_known+=arr1[i];
        }
        
        // If n - k >= 2, prll all zeros for this test case
        if (n - k >= 2) {
            for (ll i = 0; i < m; i++) {
                cout << 0;
            }
            cout << endl;
            continue;
        }
        else if(n-k==0){
            for (ll i = 0; i < m; i++) {
                cout << 1;
            }
            cout << endl;
            continue;
        }
        else{
            ll sum=n*(n+1)/2;
            ll unknown=sum-sum_known;
            for(ll i=0;i<m;i++){
                if(vec[i]==unknown){
                    cout<<1;
                }
                else{
                    cout<<0;
                }
            }
        }
        cout << endl;
    }
    
    return 0;
}
