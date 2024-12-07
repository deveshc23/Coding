// #include<bits/stdc++.h>
// using namespace std;

// int main(){
//     int t;
//     cin>>t;
//     while(t--){
//         int n,x,ans;
//         cin>>n>>x;
//         vector<int> v,c;
//         for(int i=0;i<n;i++){
//             int y;
//             cin>>y;
//             v.push_back(y);
//         }
//         sort(v.begin(),v.end());
//         int count=0;
//         for(int i=0;i<v.size();i++){
//             for(int j=0;j<v.size();j++){
//                 if(v[j]==i){
//                     count++;
//                 }
//             }
//             c.push_back(count);
//             count=0;
//         }
//         for(int i=0;i<v.size();i++){
//             if(c[i]==0){
//                 for(int j=0;j<i;j++){
//                     int m;
//                     if(c[j]>1){
//                         m=j;
//                         while(m<i){
//                             m+=x;
//                         }
//                         if(m==i){
//                             c[j]--;
//                             c[i]++;
//                             break;
//                         }
//                     }
//                 }
//                 if(c[i]==0){
//                     ans=i;break;
//                 }
//             }
//         }
//         cout<<ans<<endl;
//     }
// }
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        vector<int> v(n);
        for (int i = 0; i < n; i++) {
            cin >> v[i];
        }
        sort(v.begin(),v.end());
        int mex = 0; 
        int index = 0; 
        
        while (true) {
            while (index < n && v[index] < mex) {
                index++;
            }
            if (index < n && v[index] == mex) {
                mex++;
                index++;
            } else if (x > 0) {
                // Increment mex by adding x to an existing number
                x--;
                mex++;
            } else {
                // If x is 0 and mex is not found, we break
                break;
            }
        }
        cout << mex << endl;
    }
    return 0;
}
