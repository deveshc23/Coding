#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    for(int i=1;i<=t;i++){
        int n,score=0;
        int *a;
        cin>>n;
        a=new int[n];
        for(int j=0;j<n;j++){
            cin>>a[j];
        }
        sort(a,a+n);
        int temp=a[n-1];
        for(int j=n-1;j>0;j--){
            a[j]=a[j-1];
        }
        a[0]=temp;
        int *b,*c;
        int min=a[0];
        int max=a[0];
        b=new int[n];
        c=new int[n];
        for(int j=0;j<n;j++){
            if(a[j]<min){
                min=a[j];
                b[j]=min;
            }
            else{
                b[j]=min;
            }
            if(a[j]>max){
                max=a[j];
                c[j]=max;
            }
            else{
                c[j]=max;
            }
            score+=c[j]-b[j];
        }
        cout<<score<<endl;
    }
}