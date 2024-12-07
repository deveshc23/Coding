#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    int pairs=0;
    cin>>t;
    while(t--){
        int n;
        int p[n][2];
        for(int i=0;i<n;i++){
            cin>>p[i][0]>>p[i][1];
        }
        for(int i=0;i<n;i++){
            for(int j=(i+1);j<n;j++){
                if(p[i][0]==p[j][0]){
                    if(p[i][1]!=p[j][1]){
                        pairs+=1;
                    }
                }
                else{
                    if(p[i][1]!=p[j][1]){
                        
                    }
                }
            }
        }
        int ans=0;
        ans+=pairs*(n-2);
    }
}