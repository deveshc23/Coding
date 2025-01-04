#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    for(int i=0;i<t;i++){
        int n,x;
        cin>>n>>x;
        if(n==1 || n==2){
            cout<<1<<endl;
        }
        else{
            cout<<ceil((double)(n-2)/x)+1<<endl;
        }
    }
}