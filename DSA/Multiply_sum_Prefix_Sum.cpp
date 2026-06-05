#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007

int main(){
    int n,q;
    cin>>n>>q;
    int a[n],b[n];
    for(int i=0;i<n;i++){
        cin>>a[i];
        b[i]=i*a[i]%mod;
        a[i]+=a[i-1];
    }
}