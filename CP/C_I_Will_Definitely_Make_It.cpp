// #include<bits/stdc++.h>
// using namespace std;

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     long long t;
//     cin>>t;
//     while(t--){
//         long long n,k;
//         cin>>n>>k;
//         vector<long long> a;
//         for(long long i=0;i<n;i++){
//             long long x;
//             cin>>x;
//             a.push_back(x);
//         }
//         long long initial_height=a[k-1];
//         unordered_set<long long> st(a.begin(), a.end());
//         a.assign(st.begin(), st.end());
//         sort(a.begin(), a.end());
//         long long max_height=a[n-1];
//         if(initial_height==max_height){
//             cout<<"YES"<<endl;
//             continue;
//         }
//         int i=0;
//         while(i<n && a[i]<initial_height){
//             i++;
//         }
//         int level=1;
//         int flag=0;
//         while(i<(n-1)){
//             long long diff=a[i+1]-a[i];
//             long long gap=diff-1;
//             if((level+gap)>a[i]){
//                 flag=1;
//                 break;
//             }
//             else{
//                 level+=a[i+1]-a[i];
//                 i++;
//             }
//         }
//         if(flag){
//             cout<<"NO"<<endl;
//         }
//         else{
//             cout<<"YES"<<endl;
//         }
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long t;
    cin >> t;
    while (t--) {
        long long n, k;
        cin >> n >> k;
        vector<long long> a(n);
        for (long long i = 0; i < n; i++)
            cin >> a[i];

        long long initial_height = a[k-1];

        // dedupe & sort
        unordered_set<long long> st(a.begin(), a.end());
        a.assign(st.begin(), st.end());
        sort(a.begin(), a.end());

        // use the new size
        long long m = a.size();
        long long max_height = a[m-1];

        if (initial_height == max_height) {
            cout << "YES\n";
            continue;
        }

        // find first index >= initial_height
        long long i = 0;
        while (i < m && a[i] < initial_height) 
            i++;

        long long level = 1;
        bool fail = false;

        // climb from a[i] up to a[m-1]
        while (i + 1 < m) {
            long long gap = (a[i+1] - a[i]) - 1;
            if (level + gap > a[i]) {
                fail = true;
                break;
            }
            level += (a[i+1] - a[i]);
            i++;
        }

        cout << (fail ? "NO\n" : "YES\n");
    }
    return 0;
}
