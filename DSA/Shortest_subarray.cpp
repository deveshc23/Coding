#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin >> n;
        int arr[n];
        unordered_map<int, int> freq;
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
            freq[arr[i]]++;
        }
        int k=freq.size();
        int left = 0, right = 0;
        unordered_map<int, int> freq1;
        int ans = n;
        while(right<n){
            freq1[arr[right]]++;
            while(freq1.size()==k){
                ans=min(ans, right-left+1);
                freq1[arr[left]]--;
                if(freq1[arr[left]]==0){
                    freq1.erase(arr[left]);
                }
                left++;
            }
            right++;
        }
        cout<<ans<<endl;
    }
}
