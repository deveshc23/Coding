#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    set<int> distinctNumbers;
    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        distinctNumbers.insert(x);
    }
    cout << distinctNumbers.size() << endl;
    return 0;
}