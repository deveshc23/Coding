#include<bits/stdc++.h>
using namespace std;

int main(){
    long long m;
    cin>>m;
    long long l=0,r=1e18;
    long long ans=-1;
    while(l<=r){
        long long mid=l+(r-l)/2;
        long long low=1,high=mid;
        long long kmax=cbrt(mid);
        long long sum=0;
        for(long long i=2;i<=kmax;i++){
           sum+=floor(mid/(i*i*i)); 
           if (sum > m) break;
        }
        if(sum==m){
            ans=mid;
            r=mid-1;
        }
        else if(sum<m){
            l=mid+1;
        }
        else{
            r=mid-1;
        }
    }
    cout<<ans<<endl;
}