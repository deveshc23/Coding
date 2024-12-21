#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        string n,answer;
        cin >> n;
        answer.resize(n.size());
        for(int i=n.size()-1; i>=0; i--){
            if(n[i]=='p'){
                answer[n.size()-i-1]='q';
            }
            else if(n[i]=='q'){
                answer[n.size()-i-1]='p';
            }
            else{
                answer[n.size()-i-1]=n[i];
            }
        }
        cout<<answer<<endl;
    }
}