#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    if(n==1){
        cout<<arr[0]<<endl;
    }
    else if(arr[0]>arr[1]){
        cout<<arr[0]<<endl;
    }
    else if(arr[n-1]>arr[n-2]){
        cout<<arr[n-1]<<endl;
    }
    else{
        int low=1,high=n-2;
        while(low<=high){
            int mid=low+(high-low)/2;
            if(arr[mid]>arr[mid-1] && arr[mid]>arr[mid+1]){
                cout<<arr[mid]<<endl;
                break;
            }
            else if(arr[mid]<arr[mid+1]){
                low=mid+1;
            }
            else{
                high=mid-1;
            }
        }
    }
}