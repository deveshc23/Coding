#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        int m,a,b,c,seated_1=0,seated_2=0,left_1=m,left_2=m;
        cin >>m>>a>>b>>c;
        if(a<m){
            seated_1=a;
            left_1=m-a;
        }
        else{
            seated_1=m;
            left_1=0;
        }
        if(b<m){
            seated_2=b;
            left_2=m-b;
        }
        else{
            seated_2=m;
            left_2=0;
        }
        cout<<seated_1+seated_2+(c<left_1+left_2?c:left_1+left_2)<<endl;
    }
}