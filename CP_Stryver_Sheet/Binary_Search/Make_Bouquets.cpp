#include <bits/stdc++.h>
using namespace std;

bool canMakeBouquets(int arr[], int n, int mid, int m, int k) {
    int bouq = 0, count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] <= mid) {
            count++;
            if (count == k) {
                bouq++;
                count = 0;
            }
        } else {
            count = 0; 
        }
    }
    return bouq >= m;
}

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    int arr[n];
    int maxVal = INT_MIN, minVal = INT_MAX;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        maxVal = max(maxVal, arr[i]);
        minVal = min(minVal, arr[i]);
    }

    int low = minVal, high = maxVal;
    int result = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (canMakeBouquets(arr, n, mid, m, k)) {
            result = mid;  
            high = mid - 1;
        } else {
            low = mid + 1; 
        }
    }

    cout << result << endl;
    return 0;
}
