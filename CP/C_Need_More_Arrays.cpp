#include<bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        vector<long long> a(n);
        long long arrays=0;
        for(long long i = 0; i < n; i++){
            cin>>a[i];
        }
        int i=0;
        int j=0;
        while(j<n){
            while(j<n && (a[j]-a[i])<=1){
                j++;
            }
            if((a[j]-a[i])>1){
                arrays++;
                i = j;
            }
        }
        if(i<n) arrays++;
        cout<<arrays<<endl;
    }
}