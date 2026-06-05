#include <bits/stdc++.h>
using namespace std;

int coincount(int n,int x,vector<int>& coins, vector<int>& dp){
    if(x<0) return INT_MAX;
    if(x==0) return 0;
    int minimum_coins=INT_MAX;
    if(dp[x] != -1) {
        return dp[x];
    }
    for(int i=0;i<n;i++){
        int res = coincount(n,x-coins[i],coins,dp);
        if(res != INT_MAX){
            minimum_coins= min(minimum_coins, res + 1);
        }
    }
    return dp[x]=minimum_coins;
}

int main(){
    int n,x;
    cin >> n >> x;
    vector<int> coins(n);
    vector<int> dp(x + 1, -1);
    for(int i = 0; i < n; i++){
        cin >> coins[i];
    }
    int result = coincount(n, x, coins, dp);
    if(result == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << result << endl;
    }
}