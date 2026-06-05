// #include<bits/stdc++.h>
// using namespace std;

// int main(){
//     int n,k,q;
//     cin>>n>>k>>q;
//     int arr[n];
//     for(int i=0;i<n;i++){
//         arr[i]=0;
//     }
//     for(int i=0;i<q;i++){
//         int l,r;
//         cin>>l>>r;
//         arr[l]++;
//         if(r+1<n){
//             arr[r+1]--;
//         }
//     }
//     for(int i=1;i<n;i++){
//         arr[i]+=arr[i-1];
//     }
//     for(int i=0;i<n;i++){
//         arr[i]=(arr[i]>=k)?1:0;
//     }
//     int count=0;
//     int prefix_sum[n+1];
//     prefix_sum[0]=0;
//     for(int i=1;i<=n;i++){
//         prefix_sum[i]=prefix_sum[i-1]+arr[i-1];
//     }
//     for(int i=0;i<q;i++){
//         int l,r;
//         cin>>l>>r;
//         count=prefix_sum[r]-prefix_sum[l-1];
//         cout<<count<<endl;
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
const int N = 1000005;
signed main()
{
    int n,k,q;
    cin>>n>>k>>q;
    int arr[N];
    for(int i=0;i<N;i++)
        arr[i] = 0;
    for(int i=1;i<=n;i++){
        int l,r;
        cin>>l>>r;
        arr[l]++;
        arr[r+1]--;
    }
    for(int i=1;i<N;i++)
        arr[i]+=arr[i-1];
    for(int i=1;i<N;i++)
        arr[i] = (arr[i]>=k);
    int prefixSum[N];
    prefixSum[0] = 0;
    for(int i=1;i<N;i++){
        prefixSum[i] = prefixSum[i-1]+arr[i];
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        int ans = prefixSum[r]-prefixSum[l-1];
        cout<<ans<<"\n";
    }
}