// #include<bits/stdc++.h>
// using namespace std;
// long long isprime(long long n){
//     if(n<=1) return 0;
//     for(long long i=2;i*i<=n;i++){
//         if(n%i==0) return 0;
//     }
//     return 1;
// }
// int main(){
//     long long t;
//     cin>>t;
//     while(t--){
//         long long n;
//         cin>>n;
//         long long answer=0;
//         vector<long long> primes;
//         for(long long i=1;i<=n;i++){
//             if(isprime(i)){
//                 primes.push_back(i);
//             }
//         }
//         answer+= primes.size();
//         for(long long i=0;i<primes.size();i++){
//             answer+= (n/primes[i]-1);
//         }
//         cout<<answer<<endl;
//     }
//     return 0;
// }

#include <bits/stdc++.h>
using namespace std;
int main() {
    long long t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        if (n <= 1) {
            cout << 0 << endl;
            continue;
        }
        vector<bool> is_prime(n + 1, true);
        is_prime[0] = is_prime[1] = false;
        vector<long long> primes;
        for (long long p = 2; p * p <= n; p++) {
            if (is_prime[p]) {
                for (long long i = p * p; i <= n; i += p)
                    is_prime[i] = false;
            }
        }
        for (long long p = 2; p <= n; p++) {
            if (is_prime[p]) {
                primes.push_back(p);
            }
        }
        long long answer = primes.size();
        for(long long i=0;i<primes.size();i++){
            answer+= (n/primes[i]-1);
        }
        cout << answer << endl;
    }
    return 0;
}