#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,j,k;
        cin>> n >> j >> k;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        int target=a[j-1];
        sort(a.begin(), a.end());
        if(a[n-1]==target){
            cout<<"YES"<<endl;
        }
        else if(k>1){
            cout<<"YES"<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
}