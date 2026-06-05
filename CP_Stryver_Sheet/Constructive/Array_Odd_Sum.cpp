#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int a[n];
        int odd_count=0;
        int even_count=0;
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(a[i]%2==0){
                even_count++;
            }
            else{
                odd_count++;
            }
        }
        if(odd_count==0){
            cout<<"NO"<<endl;
        }
        else{
            if(even_count==0 && odd_count%2==0){
                cout<<"NO"<<endl;
            }
            else{
                cout<<"YES"<<endl;
            }
        }
    }
}