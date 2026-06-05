// #include <bits/stdc++.h>
// using namespace std;

// int steps(int n, vector<int> &dp){
//     if(n==0) return 0;
//     if(dp[n] != -1) return dp[n];
//     int max_digit=0;
//     int temp=n;
//     while(temp > 0){
//         max_digit = max(max_digit, temp % 10);
//         temp /= 10;
//     }
//     return dp[n]=1 + steps(n - max_digit,dp);
// }
// int main(){
//     int n;
//     cin >> n;
//     vector<int> dp(n + 1, -1);
//     cout << steps(n,dp) << endl;
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> dp(n + 1, -1);
    dp[0]=0;
    for(int i=1;i<=n;i++){
        int max_digit=0;
        int temp=i;
        while(temp>0){
            max_digit=max(max_digit,temp%10);
            temp /= 10;
        }
        dp[i]=dp[i-max_digit]+1;
    }
    cout << dp[n] << endl;
    return 0;
}