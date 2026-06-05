#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
long long number(int n, vector<long long>& dp){
    if(n < 0){
        return 0;
    }
    else if(n == 0){
        return 1;
    }
    if(dp[n] != -1) {
        return dp[n];
    }
    dp[n] = 0;
    for(int i = 1; i <= 6; i++){
        dp[n] = (dp[n] + number(n - i, dp)) % MOD;
    }
    return dp[n];
}
int main(){
    int n;
    cin >> n;
    vector<long long> dp(n + 1, -1);
    cout << number(n, dp) << endl;
    return 0;
}