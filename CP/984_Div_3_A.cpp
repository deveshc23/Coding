#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int *a;
        int invalid=0;
        a=new int[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        for(int i=0;i<n-1;i++){
            if(abs(a[i]-a[i+1])!=5 && abs(a[i]-a[i+1])!=7){
                cout<<"NO"<<endl;
                break;
                invalid=1;
            }
        }
        if(invalid==0){
            cout<<"YES"<<endl;
        }
        delete []a;
    }
}