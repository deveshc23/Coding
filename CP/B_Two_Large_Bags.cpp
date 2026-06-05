#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int arr[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        unordered_map<int,int> mp;
        for(int i=0;i<n;i++){
            mp[arr[i]]++;
        }
        //sort the map by key in descending order
        vector<pair<int,int>> v(mp.begin(),mp.end());
        sort(v.begin(),v.end(),greater<pair<int,int>>());
        for(int i=0;i<v.size();i++){
            if(v[i].second%2!=0){
                int flag=1;
                for(int j=i+1;j<v.size();j++){
                    if(v[j].second%2!=0){
                        if(v[j].second>=(2*(v[i].first-v[j].first)+1)){
                            flag=0;
                            break;
                        }
                    }
                }
                if(flag==1){
                    cout<<"No"<<endl;
                }
            }
        }
    }
}