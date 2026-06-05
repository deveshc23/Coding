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
            cin>>arr[i];
        }
        int left=0,right=0;
        int answer=0;
        int sum=0;
        while(right<n){
            sum+=arr[right];
            while(sum>k){
                sum-=arr[left];
                left++;
            }
            answer+=right-left+1;
            right++;
        }
        cout<<answer<<endl;
    }
}