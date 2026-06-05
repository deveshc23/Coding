#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin>>n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int answer[n];
        for(int i = 0; i < n; i++){
            answer[i] = 0;
        }
        answer[0]=1;
        answer[n-1]=1;
        vector<int> prefix(n);
        prefix[0] = a[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = min(prefix[i - 1], a[i]);
        }
        vector<int> suffix(n);
        suffix[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = max(suffix[i + 1], a[i]);
        }
        for(int i = 1; i < n - 1; i++){
            if(a[i]<prefix[i-1] || a[i]>suffix[i+1]){
                answer[i] = 1;
            }
        }
        for(int i=0;i<n;i++){
            cout<<answer[i];
        }
        cout<<endl;
    }
}