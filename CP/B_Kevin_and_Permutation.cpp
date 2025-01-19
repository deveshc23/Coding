#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        int arr[n];
        for(int i=0;i<n;i++){
            arr[i]=0;
        }
        int index=1;
        for(int i=k-1;i<n;i=i+k){
            arr[i]=index;
            index++;
        }
        for(int i=0;i<n;i++){
            if(arr[i]==0){
                arr[i]=index;
                index++;
            }
        }
        for(int i=0;i<n;i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
}