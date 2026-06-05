#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t>0){
        int c=0;
        t--;
        string a,b;
        cin>>a>>b;
        int len_a=a.length();
        int len_b=b.length();
        int len=min(len_a,len_b);
        for(int i=0;i<len;i++){
            if(a[i]!=b[i]){
                c=1;
                if(i==0){
                    cout<<len_a+len_b<<endl;
                    break;
                }
                else{
                    cout<<len_a+len_b-(i)+1<<endl;
                    break;
                }
            }
        }
        if(c==0){
            cout<<len_a+len_b-len+1<<endl;
        }
    }
}