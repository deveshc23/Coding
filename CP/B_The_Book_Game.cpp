#include <iostream>
#include <vector>
#include <algorithm> // For std::max

#define MOD 1000000007
#define ll long long

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    ll N_unused, K; 
    std::cin >> N_unused >> K;

    std::vector<ll> digits(K); 
    for (ll i = 0; i < K; ++i) {
        ll x;
        std::cin >> x;
        digits[i] = x % 10;
    }

    ll current_max_score = 0; 

    for (ll i = 0; i < K; ++i) {
        ll d = digits[i];
        ll score_if_add = (current_max_score + d) % MOD;
        ll score_if_mult = (current_max_score * d) % MOD;
        current_max_score = std::max(score_if_add, score_if_mult);
    }

    std::cout << current_max_score << "\n";

    return 0;
}