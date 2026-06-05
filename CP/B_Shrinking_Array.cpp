#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> arr(n);
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        int flag=0;
        for(int i=1;i<n;i++){
            if(abs(arr[i]-arr[i-1])<2){
                flag=1;
                break;
            }
        }
        if(flag){
            cout<<0<<endl;
            continue;
        }
        if(a[1]>a[0]){
            
        }
    }
}