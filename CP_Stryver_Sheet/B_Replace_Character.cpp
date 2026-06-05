#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        map<char,int> mp;
        for(int i=0;i<n;i++){
            mp[s[i]]++;
        }
        int max=0;
        int min=INT_MAX;
        for(auto it:mp){
            if(it.second>max){
                max=it.second;
            }
            if(it.second<min){
                min=it.second;
            }
        }
        // cout<<max<<endl;
        for(auto it:mp){
            if(it.second==max){
                it.second++;
                break;
            }
        }
         for(auto it:mp){
            if(it.second==min){
                it.second--;
                break;
            }
        }
        
        char ans;
        for(auto it:mp){
            if(it.second==max+1){
                ans=it.first;
                break;
            }
        }
        for(int i=0;i<n;i++){
            if(mp[s[i]]>0){
                cout<<ans;
                mp[s[i]]--;
            }
            else{
                cout<<ans;
            }
        }
        cout<<endl;
    }
}