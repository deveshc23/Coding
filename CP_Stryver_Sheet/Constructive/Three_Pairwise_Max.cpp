#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int x,y,z;
        cin>>x>>y>>z;
        if(x==y && x!=z && x>z){
            cout<<"YES"<<endl;
            cout<<x<<" "<<z<<" "<<z<<endl;
        }
        else if(x==z && x!=y && x>y){
            cout<<"YES"<<endl;
            cout<<y<<" "<<x<<" "<<y<<endl;
        }
        else if(y==z && y!=x && y>x){
            cout<<"YES"<<endl;
            cout<<x<<" "<<y<<" "<<x<<endl;
        }
        else if(x==y && x==z){
            cout<<"YES"<<endl;
            cout<<x<<" "<<y<<" "<<z<<endl;
        }
        else{
            cout<<"NO"<<endl;
        }
    }
    return 0;
}