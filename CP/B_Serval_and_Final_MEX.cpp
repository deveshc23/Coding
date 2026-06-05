#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int arr[n];
        for(int i=0;i<n;i++){
            cin>>arr[i];
        }
        vector<vector<int>> ans;
        vector<int> temp;
        int count=0;
        for(int i=0;i<n;i++){
            if(arr[i]!=0){
                temp.push_back(1);
            }
            else{
                if(i<(n-1)){
                    vector<int> temp1;
                    temp1.push_back(temp.size()+1);
                    temp1.push_back(temp.size()+2);
                    i++;
                    ans.push_back(temp1);
                    temp1.clear();
                    temp.push_back(1);
                    count++;
                }
                else{
                    vector<int> temp1;
                    temp.pop_back();
                    temp1.push_back(temp.size()+1);
                    temp1.push_back(temp.size()+2);
                    ans.push_back(temp1);
                    temp1.clear();
                    temp.push_back(1);
                    count++;
                }
            }
        }
        vector<int> temp1;
        temp1.push_back(1);
        temp1.push_back(temp.size());
        ans.push_back(temp1);
        temp1.clear();
        temp.push_back(0);
        count++;
        cout<<count<<endl;
        for(int i=0;i<ans.size();i++){
            cout<<ans[i][0]<<" "<<ans[i][1]<<endl;
        }
    }
    return 0;
}