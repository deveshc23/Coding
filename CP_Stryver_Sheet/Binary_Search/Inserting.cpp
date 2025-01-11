#include <bits/stdc++.h>
using namespace std;

int insert(int arr[],int n,int x){
    int low=0;
    int high=n-1;
    int mid;
    int ans=n;
    while(low<=high){
        mid = low + (high - low) / 2;
        //inserting x so that it remains sorted
        if(arr[mid]>=x){
            ans=mid;
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return ans;
}

int main(){
    int arr[]={1,2,3,5};
    int n=sizeof(arr)/sizeof(arr[0]);
    int x=4;
    cout<<insert(arr,n,x);
}