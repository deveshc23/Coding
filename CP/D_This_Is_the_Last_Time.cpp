#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>> t;
    while(t--){
        int n,k;
        cin>>n>>k;
        map<pair<int,int>,int> mp;
        for(int i=0;i<n;i++){
            int x,y,z;
            cin>>x>>y>>z;
            mp[{x,y}] = max(mp[{x,y}], z);
        }
        int max_value = k;
        for (auto &entry : mp) {
            pair<int, int> key = entry.first;
            int value = entry.second;
            int a = key.first;
            int b = key.second;
            if(a<=k && b>=k){
                max_value = max(max_value, value);
            }
            else{
                k=max_value;
                if(a<=k && b>=k){
                    max_value = max(max_value, value);
                }
                else{
                    continue;
                }
            }
        }
        k=max_value;
        cout<<k<<endl;
    }
}

// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// struct Casino { ll l, r, x; };

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int t;
//     cin >> t;
//     while (t--) {
//         int n;
//         ll k;
//         cin >> n >> k;
//         vector<Casino> a(n);
//         for (int i = 0; i < n; i++)
//             cin >> a[i].l >> a[i].r >> a[i].x;

//         sort(a.begin(), a.end(), [](auto &A, auto &B){ return A.l < B.l; });
//         priority_queue<pair<ll,ll>> pq; 
//         int idx = 0;
//         ll cur = k;

//         while (true) {
//             while (idx < n && a[idx].l <= cur)
//                 pq.emplace(a[idx].x, a[idx].r), idx++;

//             while (!pq.empty() && pq.top().second < cur)
//                 pq.pop();

//             if (pq.empty() || pq.top().first <= cur)
//                 break;

//             cur = pq.top().first;
//             pq.pop();
//         }

//         cout << cur << "\n";
//     }
//     return 0;
// }
