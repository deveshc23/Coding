#include <bits/stdc++.h>
using namespace std;

int lower(int arr[],int n,int x){
    int low=0;
    int high=n-1;
    int mid;
    while(low<=high){
        mid=(low+high)/2;
        if(arr[mid]>=x){
            high=mid-1;
        }
        else{
            low=mid+1;
        }
    }
    return arr[low];
}

int upper(int arr[],int n,int x){
    int low=0;
    int high=n-1;
    int mid;
    while(low<=high){
        mid=(low+high)/2;
        if(arr[mid]<=x){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
    return arr[high];
}

int main(){
    int arr[]={1,2,3,3,3,3,4,5};
    int n=sizeof(arr)/sizeof(arr[0]);
    int x=3;
    cout<<lower(arr,n,x)<<" "<<upper(arr,n,x);
}

