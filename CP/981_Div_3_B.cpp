#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        int a[n][n];
        int sum=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin>>a[i][j];
            }
        }
        for(int i=0;i<n;i++){
            int min=0;
            for(int j=0;j<n-i;j++){
                if(a[i++][j++]<min){
                    min=a[i++][j++];
                }
            }
            sum+=abs(min);
        }
        for(int i=0;i<n;i++){
            int min=0;
            for(int j=0;j<n-i;j++){
                if(a[j++][i++]<min){
                    min=a[j++][i++];
                }
            }
            sum+=abs(min);
        }
        cout<<sum<<endl;
    }
    
}