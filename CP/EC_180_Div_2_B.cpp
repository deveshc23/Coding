#include <bits/stdc++.h>
#include <cmath>
using namespace std;

const long MOD = 1e9 + 7; // Define the modulo constant
int power(int n){
    while(n>0){
        return (power(n-1)*2)%MOD;
    }
}
int main() {
    int n;
    cin >> n;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    vector<int> b;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        b.push_back(x);
    }
    for(int i=0;i<n;i++){
        cout<<power(b[i])<<endl;
    }
    return 0;
}
