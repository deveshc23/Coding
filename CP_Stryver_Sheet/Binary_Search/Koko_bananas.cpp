#include <bits/stdc++.h>
using namespace std;

int count(int mid,int arr[],int n){
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=ceil((double)arr[i]/mid);
    }
    return sum;
}

int main(){
    int n;
    cin>>n;
    int arr[n];
    int max=0;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        if(arr[i]>max){
            max=arr[i];
        }
    }
    int h;
    cin>>h;
    int low=0;
    int high=max;
    int mid=low+(high-low)/2;
    while(low<=high){
        mid=low+(high-low)/2;
        int sum=0;  
        sum=count(mid,arr,n);
        if(sum==h){
            cout<<mid<<endl;
            break;
        }
        else if(sum>h){
            low=mid+1;
        }
        else{
            high=mid-1;
        }
    }
}