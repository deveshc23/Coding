#include <bits/stdc++.h>
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
        //sort(arr,arr+n);
        int count[n];
        for(int i=0;i<n;i++){
            count[i]=0;
        }
        for(int i=0;i<n;i++){
            count[arr[i]-1]++;
        }
        int ans=0;
        int count_1=0;
        int rest_count=0;
        for(int i=0;i<=n;i++){
            if(count[i]==0){
                continue;
            }
            else if(count[i]==1){
                count_1++;
            }
            else{
                rest_count++;
            }
        }
        cout<<((count_1+1)/2)*2+rest_count-1<<endl;
    }
}