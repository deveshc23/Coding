#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        int *a;
        cin>>n;
        a=new int[n];
        for(int i=0;i<n;i++){
            cin>>a[i];
        }
        for(int i=0,j=n-1;i<j;i++,j--){
            if(a[i]!=a[i+1] && a[j]!=a[j-1]){
                continue;
            }
            else{
                if(i!=0){
                    if(a[j]!=a[i-1] and a[i]!=a[j+1]){
                        int temp;
                        temp=a[i];
                        a[i]=a[j];
                        a[j]=temp;
                    }
                }
                
            }
        }
    }
}