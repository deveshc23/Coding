// // #include <bits/stdc++.h>
// // using namespace std;

// // int main(){
// //     long long t;
// //     cin>>t;
// //     while(t--){
// //         long long n;
// //         cin>>n;
// //         vector<long long> arr1(n);
// //         vector<long long> arr2(n);
// //         long long min1 = LONG_LONG_MAX;
// //         for(long long i = 0; i < n; i++) {
// //             cin >> arr1[i];
// //             min1 = min(min1, arr1[i]);
// //         }
// //         for(long long i = 0; i < n; i++) {
// //             cin >> arr2[i];
// //         }
// //         if(n == 1){
// //             if(arr1[0] == arr2[0]){
// //                 cout<<"YES"<<endl;
// //             }
// //             else{
// //                 cout<<"NO"<<endl;
// //             }
// //             continue;
// //         }
// //         long long i=0;
// //         long long j=0;
// //         while(i<(n-1) && arr1[i]>=arr1[i+1] && arr1[i]%arr1[i+1]==0){
// //             if(arr1[i] == min1){
// //                 break;
// //             }
// //             i++;
// //         }
// //         for(int j=i;j<(n-1);j++){
// //             if(arr1[j]== arr1[j+1]){
// //                 continue;
// //             }
// //         }
// //         if(arr2[i]== arr1[i]){
// //             for(long long j=0;j<i;j++){
// //                 if(arr2[j] != arr2[j+1]){
// //                     cout<<"NO"<<endl;
// //                     break;
// //                 }
// //             }
// //             for(long long j=i;j<(n-1);j++){
// //                 if(arr2[j]<arr2[j+1] && arr2[j+1]%arr2[j]==0){
// //                     if(j==n-2){
// //                         cout<<"YES"<<endl;
// //                         break;
// //                     }
// //                     else{
// //                         continue;
// //                     }
// //                 }
// //                 cout<<"NO"<<endl;
// //                 break;
// //             }
// //         }
// //         else{
// //             cout<<"NO"<<endl;
// //         }
// //     }
// //     return 0;
// // }

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> p(n);
    vector<long long> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }

    bool possible = true;

    // Condition 1: Prefix GCDs must be a valid chain (p[i] is a multiple of p[i+1])
    for (int i = 0; i < n - 1; ++i) {
        if (p[i] % p[i + 1] != 0) {
            possible = false;
            break;
        }
    }

    // Condition 2: Suffix GCDs must be a valid chain (s[i+1] is a multiple of s[i])
    if (possible) {
        for (int i = 0; i < n - 1; ++i) {
            if (s[i + 1] % s[i] != 0) {
                possible = false;
                break;
            }
        }
    }
    
    // Condition 3: The overall GCD must match (p[n-1] == s[0])
    if (possible) {
        if (p[n - 1] != s[0]) {
            possible = false;
        }
    }

    if (possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}