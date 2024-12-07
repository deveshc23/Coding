#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> v;
        for(int i=0;i<n;i++){
            int x;
            cin>>x;
            v.push_back(x);
        }
        sort(v.begin(),v.end(),greater<int>());
        while(v.size()>1){
            int x;
            x=(v[v.size()-1]+v[v.size()-2])/2;
            v.pop_back();
            v.pop_back();
            v.push_back(x);
        }
        cout<<v[0]<<endl;
    }
}