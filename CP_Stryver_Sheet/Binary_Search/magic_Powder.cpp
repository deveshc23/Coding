#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,k;
    cin>>n>>k;
    int a[n],b[n];
    int total_grams=0;
    for(int i=0;i<n;i++){
        cin>>a[i];
    }
    for(int i=0;i<n;i++){
        cin>>b[i];
        total_grams+=b[i];
    }
    int low=0;
    int high=total_grams+k+100;
    while(low<high){
        int mid=low+(high-low)/2;
        int powder=0;
        for(int i=0;i<n;i++){
            if(a[i]*mid>b[i]){
                powder+=a[i]*mid-b[i];
            }
        }
        if(powder<=k){
            low=mid+1;
        }
        else{
            high=mid;
        }
    }
    //result is high-1
    cout<<high-1;
}