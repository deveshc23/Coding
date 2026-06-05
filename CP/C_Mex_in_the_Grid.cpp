#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<vector<int>> arr(n, vector<int>(n));
        int top = 0, bottom = n - 1, left = 0, right = n - 1;
        int num = n * n - 1;

        if (n % 2 == 0) {
            while (top <= bottom && left <= right) {
                for (int i = left; i <= right; i++) arr[bottom][i] = num--;
                bottom--;
                for (int i = bottom; i >= top; i--) arr[i][right] = num--;
                right--;
                for (int i = right; i >= left; i--) arr[top][i] = num--;
                top++;
                for (int i = top; i <= bottom; i++) arr[i][left] = num--;
                left++;
            }
        } else {
            while (top <= bottom && left <= right) {
                for (int i = right; i >= left; i--) arr[top][i] = num--;
                top++;
                for (int i = top; i <= bottom; i++) arr[i][left] = num--;
                left++;
                for (int i = left; i <= right; i++) arr[bottom][i] = num--;
                bottom--;
                for (int i = bottom; i >= top; i--) arr[i][right] = num--;
                right--;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << arr[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
