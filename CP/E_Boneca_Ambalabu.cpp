#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        long long a[n];
        for(long long i=0;i<n;i++){
            cin>>a[i];
        }
        long long cnt[30]={0};
        for(long long j=0;j<30;j++){
            for(long long i=0;i<n;i++){
                if((a[i]>>j)&1){
                    cnt[j]++;
                }
            }
        }
        long long ans=0;
        for(long long i=0;i<n;i++){
            long long k=a[i];
            long long res=0;
            for(long long j=0;j<30;j++){
                if((k>>j)&1){
                    res+=(n-cnt[j])*pow(2,j);
                }
                else{
                    res+=cnt[j]*pow(2,j);
                }
            }
            ans=max(ans,res);
        }
        cout<<ans<<endl;
    }
}