#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,m,k;
        cin>>n>>m>>k;
        int a;
        if(k%n==0){
            a=k;
        }
        else{
            a=k+(n-(k%n));
        }
        int b=a/n;
        int low=1;
        int high=m;
        int ans = m;  

        while(low <= high){
            int mid = (low + high) / 2;
            int c = (m / (mid + 1)) * mid + (m % (mid + 1));
            if(c >= b){
                ans = mid;         
                high = mid - 1;
            } else {
                low = mid + 1;     
            }
        }
        cout << ans << endl;
    }
    return 0;
}