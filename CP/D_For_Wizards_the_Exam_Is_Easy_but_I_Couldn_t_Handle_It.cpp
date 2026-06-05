#include <bits/stdc++.h>
using namespace std;

int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        long long arr[n];
        for(long long i=0;i<n;i++){
            cin>>arr[i];
        }
        long long max=0;
        long long ml=1;
        long long mr=1;
        for(long long l=0;l<n;l++){
            long long count=0;
            for(long long r=l;r<n;r++){
                if(arr[l]<arr[r]){
                    count--;
                }
                else if(arr[l]>arr[r]){
                    count++;
                }
                if(count>max){
                max=count;
                ml=l+1;
                mr=r+1;
            }
            }
        }
        cout<<ml<<" "<<mr<<endl;
    }
    return 0;
}