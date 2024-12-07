#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int *b;
        b=new int[n];
        int c_0=0;
        int c_1=0;
        for(int i=0;i<n;i++){
            cin>>b[i];
            if(b[i]==0){
                c_0++;
            }
            else{
                c_1++;
            }
        }
        if(c_0>c_1){
            cout<<"NO"<<endl;
        }
        else{
            cout<<"YES"<<endl;
        }
        delete []b;
    }
}