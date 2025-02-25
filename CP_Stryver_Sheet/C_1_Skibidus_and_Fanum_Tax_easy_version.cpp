#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int b;
        cin >> b;
        if(n==1){
            cout<<"YES"<<endl;
            continue;
        }
        vector<int> c(n);
        c[0] = min(a[0], b-a[0]);
        bool flag=0;
        for (int i = 1; i < n; i++) {
            c[i] = min(a[i], b-a[i]);
            if (c[i] < c[i-1]) {
                c[i] = max(a[i], b-a[i]);
            }

            if(c[i]<c[i-1]){
                cout<<"NO"<<endl;
                flag=1;
                break;
            }
        }
        if(flag==1){
            continue;
        }
        cout<<"YES"<<endl;
        // if(c[n-1]>=c[n-2]){
        //     cout<<"YES"<<endl;
        // }
        // else{
        //     cout<<"NO"<<endl;
        // }
    }

    return 0;
}