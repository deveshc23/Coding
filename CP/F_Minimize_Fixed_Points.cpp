// #include <bits/stdc++.h>
// using namespace std;

// void swap(int &a, int &b) {
//     int temp = a;
//     a = b;
//     b = temp;
// }

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int t;
//     cin >> t;
//     while(t--){
//         int n;
//         cin >> n;
//         vector<int> a(n);
//         for(int i=0;i<n;i++){
//             a[i]=i+1;
//         }
//         for(int i=n-1;i>=1;i--){
//             //largest divisor of i
//             int largest_divisor = 1;
//             for(int j = 2; j * j <= i; j++) {
//                 if(i % j == 0) {
//                     if(j != i) largest_divisor = max(largest_divisor, j);
//                     int paired = i / j;
//                     if(paired != i) largest_divisor = max(largest_divisor, paired);
//                 }
//             }
//             if(largest_divisor != 1) {
//                 swap(a[i], a[largest_divisor]);
//             }
//         }
//         for(int i=0;i<n;i++){
//             cout<<a[i]<<" ";
//         }
//         cout << "\n";
//     }
// }

#include <bits/stdc++.h>
using namespace std;

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i=0; i<n; i++){
            a[i] = i + 1;
        }
        for(int i = n - 1; i >= 1; i--){
            int k = i + 1;
            int largest_divisor = 1;
            for(int j = 2; j * j <= k; j++) {
                if(k % j == 0) {
                    largest_divisor = max(largest_divisor, j);
                    largest_divisor = max(largest_divisor, k / j);
                }
            }
            int d = largest_divisor;
            if(d != 1) {
                swap(a[i], a[d - 1]);
            }
        }

        for(int i=0; i<n; i++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
    return 0;
}