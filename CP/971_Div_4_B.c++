#include<bits/stdc++.h>
using namespace std;

int main(){
    int t,n;
    char c;
    cin>>t;
    for(int i=1;i<=t;i++){
        cin>>n;
        int a[n];
        for(int j=0;j<n;j++){
            string row;
            cin>>row;
            for(int k=0;k<4;k++){
                if(row[k]=='#'){
                    a[j]=(k+1);
                    break;
                }
            }
        }
        for(int l=n-1;l>=0;l--){
            cout<<a[l]<<' ';
        }
        cout<<endl;
    }
}
