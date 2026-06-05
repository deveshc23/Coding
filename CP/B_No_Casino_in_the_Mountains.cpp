#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        int a[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        int i=0;
        while(a[i]==1 && i<n){
            i++;
        }
        if(i==n){
            cout<<0<<endl;
            continue;
        }
        int left=i;
        int right=left-1;
        int count=0;
        int answer=0;
        while(right<(n-1)){
            if(a[right+1]==0){
                right++;
                count++;
            }
            else{
                left=right+2;
                right=left-1;
                count=0;
                while(left<n && a[left]==1){
                    left++;
                }
                continue;
            }
            if(count==k){
                answer++;
                count=0;
                left=right+2;
                right=left-1;
                if(left>(n-1)){
                    break;
                }
                while(left<n && a[left]==1){
                    left++;
                }
            }
        }
        cout<<answer<<endl;
    }
    return 0;
}