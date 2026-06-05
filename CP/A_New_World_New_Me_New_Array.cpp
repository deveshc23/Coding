#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k,p;
        cin>>n>>k>>p;
        int range_p=n*p;
        int range_n=n*(-1*p);
        if(range_n<=k && k<=range_p){
            int ans=ceil(abs((float)k/(float)p));
            cout<<ans<<endl;
        }
        else{
            cout<<-1<<endl;
        }
    }
}