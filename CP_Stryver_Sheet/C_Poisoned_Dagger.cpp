#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n,h;
        cin>>n>>h;
        long long a[n];
        for(long long i=0;i<n;i++){
            cin>>a[i];
        }
        vector<long long> v;
        for(long long i=0;i<(n-1);i++){
            v.push_back(a[i+1]-a[i]);
        }
        long long l=0,r=h,ans=-1;
        while(l<=r){
            long long mid=l+(r-l)/2;
            long long left=h-mid;
            long long sum=0;
            for(long long i=0;i<v.size();i++){
                sum+=min(v[i],mid);
            }
            if(sum==left){
                ans=mid;
                r=mid-1;
            }
            else if(sum>left){
                r=mid-1;
            }
            else if(sum<left){
                l=mid+1;
            }
        }
        if(ans!=-1){
            cout<<ans<<endl;
        }
        else{
            cout<<l<<endl;
        }
    }
}