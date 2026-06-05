#include<bits/stdc++.h>
using namespace std;

int beauty(vector<int> &a){
    vector<int>ve;
    vector<int>vo;
    for(int i=0;i<a.size();i++){
        if(a[i]%2!=0){
            vo.push_back(a[i]);
        }
        else{
            ve.push_back(a[i]);
        }
    }
    sort(vo.begin(),vo.end());
    sort(ve.begin(),ve.end());
    if(vo.size()==0){
        return ve[ve.size()-1];
    }
    else if(ve.size()==0){
        return vo[vo.size()-1];
    }
    else{
        if(vo[vo.size()-1]>ve[ve.size()-1]){
            
        }
        else{
            return ve[ve.size()-1];
        }
    }
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        vector<int> a(n);
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
    }
}