#include <bits/stdc++.h>
using namespace std;

int isSorted(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}
int main() {
    int t;  
    cin >> t;
    while (t--) {
        long long n;  
        cin >> n;
        long long sum_even = 0; 
        long long sum_odd = 0;  
        if(n%2==1){
            cout<<"NO"<<endl;
        }
        else{
        for(long long i=0;i<n;i++){
            long long num;  
            cin >> num;
            if (i % 2 == 0) {
                sum_even += num;
            } else {
                sum_odd += num;
            }
        }
        if (sum_even == sum_odd) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        }
    }
    return 0;
}
