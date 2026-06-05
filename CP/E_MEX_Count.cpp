// #include <bits/stdc++.h>
// using namespace std;

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int t;
//     cin >> t;
//     while(t--){
//         int n;
//         cin >> n;
//         vector<int> a(n);
//         vector<int> answer(n+1,1);
//         map<int, int> count;
//         for(int i = 0; i < n; i++){
//             cin >> a[i];
//             count[a[i]]++;
//         }
//         map<int,pair<int,int>> MEX;
//         if(count[0]==0){
//             for(int i=0;i<=n;i++){
//                 cout<<answer[i]<<" ";
//             }
//         }
//         else{
//             MEX[0]={count[0], n};
//             for(int i=1;i<=n;i++){
//                 int max=n;
//                 if(count[i-1]==0){
//                     break;
//                 }
//                 MEX[i]={count[i],max-i};
//             }
//             for(int i=0;i<=n;i++){
//                 for(int j=0;j<=n;j++){
//                     if(MEX[j].second==0){
//                         break;
//                     }
//                     else{
//                         if(MEX[j].first<=i && MEX[j].second>=i){
//                             answer[i]++;
//                         }  
//                     }
//                 }
//                 if(answer[i]>1){
//                     answer[i]--;
//                 }
//                 cout<<answer[i]<<" ";
//             }
//         }
//         cout << "\n";
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> answer(n + 1, 1);
        map<int, int> count;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            count[a[i]]++;
        }
        map<int, pair<int, int>> MEX;
        if (count[0] == 0) {
            for (int i = 0; i <= n; i++) {
                cout << 1 << " ";
            }
        } else {
            MEX[0] = {count[0], n};
            for (int i = 1; i <= n; i++) {
                if (count[i - 1] == 0) {
                    break;
                }
                MEX[i] = {count[i], n - i};
            }

            vector<int> diff(n + 2, 0);
            for (auto const& element : MEX) {
                if (element.second.second == 0) {
                    continue;
                }
                int start = element.second.first;
                int end = element.second.second;
                if (start <= end) {
                    diff[start]++;
                    if (end + 1 < diff.size()) {
                        diff[end + 1]--;
                    }
                }
            }

            int current_count = 0;
            for (int i = 0; i <= n; i++) {
                current_count += diff[i];
                answer[i] += current_count;
            }

            for (int i = 0; i <= n; i++) {
                if (answer[i] > 1) {
                    answer[i]--;
                }
                cout << answer[i] << " ";
            }
        }
        cout << "\n";
    }
    return 0;
}