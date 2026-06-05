#include <bits/stdc++.h>
using namespace std;

unsigned long long divide(unsigned long long n) {
    unsigned long long result = 1;
    while (n >= 3) {
        n /= 4; 
        result *= 2;  
    }
    return result * n;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << divide(n) << endl;
    }
    return 0;
}
