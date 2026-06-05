#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    int a[n],b[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
    }
    int l=0,r=INT_MAX;
    while(l<r){
        int mid=l+(r-l)/2;
        long long int powder=0;
        for(int i=0;i<n;i++){
            if(a[i]*mid>b[i]){
                powder+=a[i]*mid-b[i];
            }
        }
        if(powder<=k){
            l=mid+1;
        }
        else{
            r=mid;
        }
    }
    cout<<l-1<<endl;
    return 0;
}