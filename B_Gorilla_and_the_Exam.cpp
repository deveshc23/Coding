#include <bits/stdc++.h>
using namespace std;

int uniques(vector<int> a){
    int n=a.size();
    sort(a.begin(),a.end());
    int count=1;
    for(int i=0;i<n-1;i++){
        if(a[i]!=a[i+1]){
            count++;
        }
    }
    return count;
}

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        vector<int> a(n);
        for(vector<int>::iterator it =a.begin();it!=a.end();it++){
            cin>>*it;
        }
        sort(a.begin(),a.end());
        int i=n-1;
        vector<int> b=a;
        int temp=k;
        while(k-- && i>=0){
            b[i--]=a[0];
        }
        vector<int> c=a;
        int j=0;
        while(temp-- && j<n){
            c[j++]=a[n-1];
        }
        cout<<min(uniques(b),uniques(c))<<endl;
    }
}