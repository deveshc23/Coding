#include<bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        long long arr[n];
        long long m=LONG_MAX;
        for(long long i=0;i<n;i++){
            cin>>arr[i];
            if(arr[i]<m){
                m=arr[i];
            }
        }
        //cout<<m<<endl;
        vector<long long> ans;
        for(long long i=0;i<n;i++){
            if(arr[i]%m==0){
                ans.push_back(arr[i]);
            }
        }
        sort(ans.begin(),ans.end());
        if(ans.size()==2){
            cout<<"YES"<<endl;
        }
        else if(ans.size()==1){
            cout<<"NO"<<endl;
        }
        

    }
}