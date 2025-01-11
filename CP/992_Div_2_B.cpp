#include <bits/stdc++.h>
using namespace std;

int findOutput(int inputValue) {
    int limit = 1;  
    int output = 1; 

    while (inputValue > limit) {
        limit = limit * 2 + 2;
        output++;             
    }
    return output;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        cout<<findOutput(n)<<endl;
    }
}