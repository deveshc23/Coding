#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        long long num;
        long long sum=0;
        for(int i=0;i<n;i++){
            cin>>num;
            if(i<n-2){
                sum+=num;
            }
            if(i==n-2){
                sum=num-sum;
            }
            if(i==n-1){
                cout<<num-sum<<endl;
            }
        }
    }
}