#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin>>n;
        n=abs(n);
        int min_digit=9;
        while(n){
            int digit=n%10;
            min_digit=min(min_digit,digit);
            n/=10;
        }
        cout<<min_digit<<endl;
    }
}