#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007

int sumcount(int n,int x,vector<int>& coins,vector<int>& dp){
    if(x < 0) return 0;
    if(x == 0) return 1;
    if(dp[x] != -1) {
        return dp[x];
    }
    int ways=0;
    for(int i = 0; i < n; i++){
        if(coins[i] > x) continue;
        int res = sumcount(n, x - coins[i], coins,dp);
        if(res > 0) {
            ways=(ways+res) % MOD;
        }
    }
    return dp[x] = ways;
}
int main(){
    int n,x;
    cin >> n >> x;
    vector<int> coins(n);
    vector<int> dp(x + 1, -1);
    for(int i = 0; i < n; i++){
        cin >> coins[i];
    }
    int number=sumcount(n,x,coins,dp);
    cout << number << endl;
}