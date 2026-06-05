#include<bits/stdc++.h>
using namespace std;

class St{
    stack<int> s1;
    stack<int> s2;
    public:
    void push(int x){
        if(s1.empty()){
            s1.push(x);
        }
        else{
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
            s1.push(x);
            while(!s2.empty()){
                s1.push(s2.top());
                s2.pop();
            }
        }
    }
    void pop(){
        if(!s1.empty()){
            s1.pop();
        }
        else{
            cout<<"Stack is empty"<<endl;
        }
    }
    int top(){
        if(!s1.empty()){
            return s1.top();
        }
        else{
            cout<<"Stack is empty"<<endl;
            return -1;
        }
    }
    bool isEmpty(){
        return s1.empty();
    }
};