#include<bits/stdc++.h>
using namespace std;

class{
    queue<int> q;
    public:
    void push(int x){
        int s=q.size();
        q.push(x);
        for(int i=0;i<s;i++){
            q.push(q.front());
            q.pop();
        }
    }
    void pop(){
        if(q.empty()){
            cout<<"Stack is empty"<<endl;
            return;
        }
        q.pop();
    }
    int top(){  
        if(q.empty()){
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        return q.front();
    }
    bool isEmpty(){
        return q.empty();
    }
};