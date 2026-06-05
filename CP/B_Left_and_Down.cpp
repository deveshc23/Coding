#include <bits/stdc++.h>
using namespace std;

int gcd(long long a,long long b){
    if(b == 0) {
        return a;
    }
    return gcd(b, a % b);
}
pair<long long,long long> propose(long long a,long long b,long long k){
    long long g=gcd(a,b);
    long long stepa=a/g;
    long long stepb=b/g;
    return {stepa,stepb};
}
int main(){
    long long t;
    cin>>t;
    while(t--){
        long long a,b,k;
        cin>>a>>b>>k;
        long long ans = 0;
        if((a<=k && b<=k)){
            ans=1;
        }
        else{
            long long x;
            long long y;
            pair<long long,long long> steps=propose(a,b,k);
            x=steps.first;
            y=steps.second;
            if(x>=k && y>=k){
                long long c=x/k;
                long long d=y/k;
                long long div=min(c,d);
                x-=div*k;
                y-=div*k;
                ans=1;
            }
            if(x==0 && y==0){
                ans=1;
            }else if(x>=k && y<k){
                if(y==0){
                    ans+=1;
                }
                else{
                    ans+=2;
                }
            }else if(y>=k && x<k){
                if(x==0){
                    ans+=1;
                }
                else{
                    ans+=2;
                }
            }
            else if(x<k && y<k){
                ans+=1;
            }
        }
        cout<<ans<<endl;
    }
    return 0;
}