// #include <bits/stdc++.h>
// using namespace std;

// int main(){
//     int t;
//     cin >> t;
//     for(int i=0; i<t; i++){
//         int k,l1,r1,l2,r2;
//         int count=0,a=0,b=0;
//         for(int i=l1;i<=r1;i++){
//             int num1=l1;
//             while(num1!=0){
//                 num1/=k;
//                 a+=1;
//             }
//             int num2=r1;
//             while(num2!=0){
//                 num2/=k;
//                 b+=1;
//             }
//             count+=(b-a);
//         }
//         cout << count << endl;
//     }
// }
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long k, l1, r1, l2, r2;
        cin >> k >> l1 >> r1 >> l2 >> r2;

        long long count = 0;

        // Iterate over all x in range [l1, r1]
        for (long long x = l1; x <= r1; x++) {
            long long y = x;

            // Check y = x * k^n within range [l2, r2]
            while (y <= r2) {
                if (y >= l2) {
                    count++;
                }
                // Multiply by k for next power
                if (y > r2 / k) break; // Prevent overflow
                y *= k;
            }
        }

        cout << count << endl;
    }

    return 0;
}
