#include <bits/stdc++.h>
using namespace std;

void print1(int n){
    for(int i=0;i<n;i++){
        //space
        for(int j=0;j<n-i-1;j++){
            cout<<" ";
        }
        //stars
        for(int j=0;j<2*i+1;j++){
            cout<<"*";
        }
        cout<<endl;
    }
}
void print2(int n){
    for(int i=1;i<=n;i++){
        for(char ch = 'A'; ch <= ('A' + n-i); ch++){
            cout<<ch;
        }
        cout<<endl;
    }
}
void print3(int n){
    for(int i=1;i<=n;i++){
        for(int j=0;j<(n-i);j++){
            cout<<" ";
        }
        for(char ch='A';ch<='A'+i-1;ch++){
            cout<<ch;
        }
        for(char ch='A'+i-2;ch>='A';ch--){
            cout<<ch;
        }
        cout<<endl;
    }
}
void print4(int n){
    for(int i=0;i<n;i++){
        for(char ch=('A'+n-i-1);ch<=('A'+n-1);ch++){
            cout<<ch;
        }
        cout<<endl;
    }
}
void print5(int n){
    for(int i=0;i<n;i++){
        for(int j=n-i;j>0;j--){
            cout<<"*";
        }
        for(int j=0;j<2*i;j++){
            cout<<" ";
        }
        for(int j=n-i;j>0;j--){
            cout<<"*";
        }
        cout<<endl;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++){
            cout<<"*";
        }
        for(int j=2*(n-i-1);j>0;j--){
            cout<<" ";
        }
        for(int j=0;j<=i;j++){
            cout<<"*";
        }
        cout<<endl;
    }
}
void print6(int n){
    
}
int main(){
    int t;
    cin >> t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        print5(n);
    }
}