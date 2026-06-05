// #include <bits/stdc++.h>
// using namespace std;

// int score(vector<int>& a){
//     int n = a.size();
//     int score = 0;
//     for (int i = 0; i < n; i++) {
//         score += (n - i) * a[i];
//     }
//     return score;
// }
// int main(){
//     int t;
//     cin>>t;
//     while(t--){
//         int n,m;
//         cin>>n>>m;
//         vector<int> a(m);
//         vector<int> b(n);
//         for(int i=0;i<n;i++){
//             for(int j=0;j<m;j++){
//                 cin>>a[j];
//             }
//             b[i]=score(a);
//         }
//         sort(b.begin(),b.end());
//     }
// }
#include <bits/stdc++.h>
using namespace std;

// Function to calculate score of an array
int score(vector<int>& a) {
    int n = a.size();
    int totalScore = 0;
    for (int i = 0; i < n; i++) {
        totalScore += (n - i) * a[i];
    }
    return totalScore;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> arrays;  // Store all arrays
        for (int i = 0; i < n; i++) {
            vector<int> a(m);
            for (int j = 0; j < m; j++) {
                cin >> a[j];
            }
            arrays.push_back(a);
        }

        // Sort arrays in descending order based on their score
        sort(arrays.begin(), arrays.end(), [](const vector<int>& a, const vector<int>& b) {
            return score(a) > score(b);  // Sort by decreasing score
        });

        // Concatenate arrays in sorted order
        vector<int> concatenated;
        for (auto& arr : arrays) {
            concatenated.insert(concatenated.end(), arr.begin(), arr.end());
        }

        // Compute and print the score of the final concatenated array
        cout << score(concatenated) << endl;
    }
    return 0;
}

