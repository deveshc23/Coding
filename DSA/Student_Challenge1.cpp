#include<bits/stdc++.h>
using namespace std;
template <class T>
class Array{
    private:
    T *A;
    int size;  
    int length;
    public:
    Array(){
        size=10;
        A=new T[size];
        length=0;
    }
    Array(int sz){
        size=sz;
        A=new T[size];
        length=0;
    }
    ~Array(){
        delete []A;
    }
    void Display();
    void Input();
    T Sum();
    T Missing();
};

template <class T>
void Array<T>::Input(){
    cout<<"Enter the number of elements: ";
    cin>>length;
    cout<<"Enter the elements: "<<endl;
    for(int i=0;i<length;i++){
        cin>>A[i];
    }
}

template <class T>
void Array<T>::Display(){
    cout<<"Elements are: ";
    for(int i=0;i<length;i++){
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

template <class T>
T Array<T>::Missing(){
    int diff=A[0];
    for(int i=0;i<length-1;i++){
        if((A[i]-i)!=diff){
            while(diff<A[i]-i){
                cout<<i+diff++<<" ";
            }
        }
    }
}

int main(){
    Array<int> arr(10);
    arr.Input();
    cout<<"Missing Number is: "<<arr.Missing()<<endl;
    return 0;
}
