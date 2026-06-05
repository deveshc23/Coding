#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;
        std::vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }
        long long ans = 0;
        for (int k_idx = 2; k_idx < n; k_idx++) {
            long long required_sum_ij;

            if (k_idx < n - 1) {
                required_sum_ij = std::max(a[k_idx], a[n - 1] - a[k_idx]);
            } else {
                required_sum_ij = a[n - 1];
            }

            int left = 0;
            int right = k_idx - 1;
            long long current_k_ways = 0;

            while (left < right) {
                if (a[left] + a[right] > required_sum_ij) {
                    current_k_ways += (right - left);
                    right--;
                } else {
                    left++;
                }
            }
            ans += current_k_ways;
        }
        std::cout << ans << "\n";
    }
    return 0;
}