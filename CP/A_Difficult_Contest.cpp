#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n = s.size();
        vector<char> T;
        vector<char> N;
        vector<char> F;
        vector<char> O;
        for(int i = 0; i < n; i++) {
            if(s[i] == 'T') {
                T.push_back(s[i]);
            } else if(s[i] == 'N') {
                N.push_back(s[i]);
            } else if(s[i] == 'F') {
                F.push_back(s[i]);
            } else{
                O.push_back(s[i]);
            }
        }
        string result = "";
        for(char c : T) {
            result += c;
        }
        for(char c : N) {
            result += c;
        }
        for(char c : F) {
            result += c;
        }
        for(char c : O) {
            result += c;
        }
        cout << result << endl;
    }
    return 0;
}