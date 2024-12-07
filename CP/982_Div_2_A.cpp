#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,a,b;
        cin>>n;
        int max_w=0,max_h=0;
        while(n--){
            cin>>a>>b;
            if(a>max_w){
                max_w=a;
            }
            if(b>max_h){
                max_h=b;
            }
        }
        cout<<2*(max_w+max_h)<<endl;
    }
}