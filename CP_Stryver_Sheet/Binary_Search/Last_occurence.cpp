#include <bits/stdc++.h>
using namespace std;

int last_occ(int arr[],int n,int x){
    int low=0;
    int high=n-1;
    int mid;
    int ans=-1;
    while(low<=high){
        mid=low+(high-low)/2;
        if(arr[mid]==x){
            ans=mid;
            low=mid+1;
        }
        else if(arr[mid]>x){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return ans;
}

int main(){
    int arr[]={1,2,2,2,3,4,5};
    int n=sizeof(arr)/sizeof(arr[0]);
    int x=2;
    cout<<last_occ(arr,n,x);
}