#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while(t--){
        int n,k;
        cin>>n>>k;
        int *b;
        int *c;
        b=new int[k];
        c=new int[k];
        for(int i=0;i<k;i++){
            cin>>b[i]>>c[i];
        }
        int *a;
        a=new int[k];
        for(int i=0;i<k;i++){
            a[i]=0;
        }
        for(int i=0;i<k;i++){
            if(b[i]==(i+1)){
                a[b[i]-1]+=c[i];
            }
        }
        sort(a,a+k);
        int sum=0;
        for(int j=0;j<n;j++){
            sum+=a[n-j-1];
        }
        cout<<sum<<endl;
        delete []b;
        delete []c;
        delete []a;
    }
}