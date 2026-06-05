#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        int arr[n][m];
        unordered_map<int,int> mp;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int x;
                cin>>x;
                arr[i][j]=x;
                if(mp.find(x)==mp.end()){
                    mp[x]=1;
                }
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(mp[arr[i][j]]<2){
                    if((i-1)>=0){
                        if(arr[i-1][j]==arr[i][j]){
                            mp[arr[i][j]]++;
                            continue;
                        }
                    }
                    if((i+1)<n){
                        if(arr[i+1][j]==arr[i][j]){
                            mp[arr[i][j]]++;
                            continue;
                        }
                    }
                    if((j-1)>=0){
                        if(arr[i][j-1]==arr[i][j]){
                            mp[arr[i][j]]++;
                            continue;
                        }
                    }
                    if((j+1)<m){
                        if(arr[i][j+1]==arr[i][j]){
                            mp[arr[i][j]]++;
                            continue;
                        }
                    }
                }
            }
        }
        int max_val=0;
        int total=0;
        for(auto it:mp){
            if(it.second>max_val){
                max_val=it.second;
            }
            total+=it.second;
        }
        cout<<total-max_val<<endl;
    }
}