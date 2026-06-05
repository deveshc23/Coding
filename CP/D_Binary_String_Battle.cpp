#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        string s;
        cin>>s;
        int count = 0;
        for(int i = 0; i < n; i++){
            if(s[i] == '1'){
                count++;
            }
        }
        if(n>=2*k && count>k){
            cout<<"Bob"<<endl;
        }
        else{
            cout<<"Alice"<<endl;
        }
    }
}