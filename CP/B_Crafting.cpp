#include <bits/stdc++.h>
using namespace std;

bool canCraft(int n, vector<long long>& a, vector<long long>& b, long long ops) {
    long long excess = 0, deficit = 0;

    for (int i = 0; i < n; i++) {
        long long needed = max(0LL, b[i] - a[i]); // Deficit for material i
        long long available = max(0LL, a[i] - b[i]); // Excess for material i
        
        if (needed > ops) return false; // Can't meet the requirement for material i
        deficit += needed; // Total deficit
        excess += available; // Total excess
    }

    return deficit <= excess; // Check if we can redistribute excess to meet deficits
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t; // Number of test cases
    while (t--) {
        int n;
        cin >> n; // Number of materials

        vector<long long> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i]; // Current amounts
        for (int i = 0; i < n; i++) cin >> b[i]; // Required amounts

        long long low = 0, high = 1e9, ans = -1;

        // Binary search over the number of operations
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (canCraft(n, a, b, mid)) {
                ans = mid; // Store the feasible number of operations
                high = mid - 1; // Look for smaller values
            } else {
                low = mid + 1; // Try larger values
            }
        }

        cout << (ans != -1 ? "YES" : "NO") << "\n";
    }

    return 0;
}
