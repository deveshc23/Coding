#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int n = s.length();
        int count=0;
        for(int i=0;i<(n-1);i++){
            if(s[i]==s[i+1]){
                count=1;
                break;
            }
        }
        if(count==1){
            cout<<1<<endl;
        }
        else{
            cout<<n<<endl;
        }
    }
}