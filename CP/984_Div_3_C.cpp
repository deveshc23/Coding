#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        string s;
        cin>>s;
        int n=s.length();
        int q;
        cin>>q;
        for(int i=0;i<q;i++){
            int a,b;
            cin>>a>>b;
            if(n<4){
                cout<<"NO"<<endl;
            }
            else{
                string substring = "1100";
                s[a-1]='0'+b;
                if(s.find(substring)!= string::npos){
                    cout<<"YES"<<endl;
                }
                else{
                    cout<<"NO"<<endl;
                }
            }
        }
    }
}