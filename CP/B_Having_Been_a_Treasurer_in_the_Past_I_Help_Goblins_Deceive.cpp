#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(){
    long long t;
    cin>>t;
    while(t--){
        long long n;
        cin>>n;
        char arr[n];
        long long a=0,b=0;
        for(long long i=0;i<n;i++){
            cin>>arr[i];
            if(arr[i]=='-'){
                a++;
            }
            else{
                b++;
            }
        }
        //cout<<a<<" "<<b<<endl;
        if(a<2 || b<1){
            cout<<0<<endl;
        }
        else if(a%2==0){
            cout<<(a/2)*(a/2)*b<<endl;
        }
        else{
            cout<<((a/2)*(a/2+1))*b<<endl;
        }
    }
    return 0;
}