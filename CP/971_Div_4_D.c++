#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<pair<int,int>> points(n);
        for(int j=0;j<n;j++){
           int x,y;
           cin>>x>>y;
           points.push_back({x,y});
        }
        sort(points.begin(),points.end());
       vector<int> v0,v1;
        for(int i=0;i<n;i++){
            if(points[i].second==0){
              v0.push_back(points[i].first);
            }
            else{
                v1.push_back(points[i].first);
            }
        }
        int ans=0;
    }
}