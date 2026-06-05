#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,d;
        cin >> n >> d;
        int arr[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        unordered_map<int,int> freq;
        int min_ans=n;
        for(int i=0;i<d;i++){
            freq[arr[i]]++;
        }
        for(int i=0;i<(n-d);i++){
            min_ans = min(min_ans, static_cast<int>(freq.size()));
            freq[arr[i]]--;
            if(freq[arr[i]]==0){
                freq.erase(arr[i]);
            }
            freq[arr[i+d]]++;
        }
        min_ans = min(min_ans, static_cast<int>(freq.size()));
        cout << min_ans << endl;
    }
}