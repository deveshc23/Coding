#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        long long px,py,qx,qy;
        cin>>px>>py>>qx>>qy;
        long long a[n];
        long long sum=0;
        for(long long i=0;i<n;i++){
            cin>>a[i];
            sum+=a[i];
        }
        if(qx==px && qy==py && n==2){
            if(a[0]==a[1]){
                cout<<"Yes"<<endl;
            } else {
                cout<<"No"<<endl;
            }
        }
        else if(qx==px && qy==py && n==1){
            if(a[0]==0){
                cout<<"Yes"<<endl;
            } else {
                cout<<"No"<<endl;
            }
        }
        double dist=sqrt((qx-px)*(qx-px)+(qy-py)*(qy-py));
        if(dist!=0 && dist<=sum){
            cout<<"Yes"<<endl;
        } else if(dist!=0){
            cout<<"No"<<endl;
        }
    }
    return 0;
}