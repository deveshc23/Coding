#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        long long x,y,k;
        cin>>x>>y>>k;
        long long move_x=(x+k-1)/k;
        long long move_y=(y+k-1)/k;
        long long ans=2*max(move_x,move_y);
        if(move_x>move_y){
            ans-=1;
        }
        cout<<ans<<endl;
    }
}