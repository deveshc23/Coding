#include <bits/stdc++.h>
using namespace std;

int main(){
    int n,m;
    cin >> n >> m;
    multiset<int> tickets;
    for(int i = 0; i < n; i++) {
        int price;
        cin >> price;
        tickets.insert(price);
    }
    
    for(int i = 0; i < m; i++) {
        int maxPrice;
        cin >> maxPrice;
        auto it = tickets.upper_bound(maxPrice);
        if(it == tickets.begin()) {
            cout << -1 << "\n";
        } else {
            --it;
            cout << *it << "\n";
            tickets.erase(it);
        }
    }
    return 0;
}