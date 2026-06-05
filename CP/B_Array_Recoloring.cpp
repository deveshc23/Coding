#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n,k;
        cin>>n>>k;
        vector<long long> vec;
        for(long long i=0;i<n;i++){
            long long x;
            cin>>x;
            vec.push_back(x);
        }
        long long sum=0;
        if(k==1){
            for(long long i=0;i<n-1;i++){
                sum=max(sum,vec[i]+vec[n-1]);
            }
            for(long long i=1;i<n;i++){
                sum=max(sum,vec[0]+vec[i]);
            }
            cout<<sum<<endl;
        }
        else{
            sort(vec.begin(),vec.end());
            for(int i=0;i<k+1;i++){
                sum+=vec.back();
                vec.pop_back();
            }
            cout<<sum<<endl;
        }
    }
    return 0;
}