#include<bits/stdc++.h>
using namespace std;

class stImpl{
    int *array;
    int t;
    int s;
    stImpl(int n){
        s=n;
        array=new int[s];
        t=-1;
    }
    void push(int x){
        if(t==s-1){
            cout<<"Stack Overflow"<<endl;
        }
        t++;
        array[t]=x;
    }
    void pop(){
        if(t==-1){
            cout<<"Stack Underflow"<<endl;
        }
        t--;
    }
    int size(){
        return (t+1);
    }
    int top(){
        if(t  ==-1){
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        return array[t];
    }
    bool isEmpty(){
        if(t==-1){
            return true;
        }
        else{
            return false;
        }
    }
};