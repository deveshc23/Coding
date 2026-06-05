#include <bits/stdc++.h>
using namespace std;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--) {
        int n, k;
        cin >> n >> k;
        vector<int> arr(n);
        for(int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        unordered_map<int, int> freq;
        int left = 0;
        long long ans = 0;

        for (int right = 0; right < n; right++) {
            freq[arr[right]]++;
            while (freq.size() > k) {
                freq[arr[left]]--;
                if (freq[arr[left]] == 0)
                    freq.erase(arr[left]);
                left++;
            }
            ans += (right - left + 1);
        }

        cout << ans << endl;
    }
}
