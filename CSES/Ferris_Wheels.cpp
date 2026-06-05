#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,x;
    cin >> n >> x;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    int count = 0;
    int i = 0, j = n - 1;
    while(i <= j) {
        if(arr[i] + arr[j] <= x) {
            count++;
            i++;
            j--;
        } else {    
            count++;
            j--;
        }
    }
    cout << count << endl;
    return 0;
}