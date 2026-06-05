#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int arr[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        map<int, int> freq_map;
        for (int num : arr) {
            freq_map[num]++;
        }

        // Move map elements to a vector for sorting
        vector<pair<int, int>> freq_vec(freq_map.begin(), freq_map.end());

        
        sort(freq_vec.begin(), freq_vec.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second; 
        });

        for (auto &it : freq_vec) {
            if (k >= it.second) {
                k -= it.second;
                it.second = 0; 
            } else {
                it.second -= k;
                k = 0;  
                break;
            }
        }
        int count = 0;
        for (auto &it : freq_vec) {
            if (it.second > 0) {
                count++;
            }
        }
        cout << (count > 0 ? count : 1) << endl;
    }
    return 0;
}
