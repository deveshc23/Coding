#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    map<int, int> frequencyMap;
    for(int i = 0; i < n; i++) {
        int x,y;
        cin >> x >> y;
        frequencyMap[x]++;
        frequencyMap[y]--;
    }
    int currentCustomers = 0;
    int maxCustomers = 0;
    for(auto& entry : frequencyMap) {
        currentCustomers += entry.second;
        maxCustomers = max(maxCustomers, currentCustomers);
    }
    cout << maxCustomers << endl;
    return 0;
}