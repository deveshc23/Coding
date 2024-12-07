#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        if(n!=0){
            cout<<1;
            n--;
        }
        while(n--){
            cout<<0;
        }
    }
}