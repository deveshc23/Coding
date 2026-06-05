#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n,k;
        cin>>n>>k;
        long long a[n],b[n];
        long long ans=0;
        vector<long long> v;
        for(long long i=0;i<n;i++){
            cin>>a[i];
        }
        for(long long i=0;i<n;i++){
            cin>>b[i];
        }
        for(long long i=0;i<n;i++){
            if(a[i]>b[i]){
                ans+=a[i];
                v.push_back(b[i]);
            }
            else{
                ans+=b[i];
                v.push_back(a[i]);
            }
        }
        sort(v.begin(),v.end());
        for(long long i=0;i<k;i++){
            if(i==k-1){
                ans+=1;
                break;
            }
            else{
                ans+=v[n-i-1];
            }
        }
        cout<<ans<<endl;
    }
}