#include<bits/stdc++.h>
using namespace std;

class Q{
    static const int s = 10;
    int q[s];
    int curr_size=0;
    int start=-1;
    int end=-1;
    void push(int n){
        if(curr_size==s){
            cout<<"Queue is full"<<endl;
            return;
        }
        if(start==-1){
            start++;
        }
        end=(end+1)%s;
        q[end]=n;
        curr_size++;
    }
    void pop(){
        if(curr_size==0){
            cout<<"Queue is empty"<<endl;
            return;
        }
        else if(curr_size==1){
            start=-1;
            end=-1;
            curr_size=0;
            return;
        }
        start=start+1;
        curr_size--;
    }
    int top(){
        if(curr_size==0){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        return q[start];
    }
    int size(){
        return curr_size;
    }
    bool isEmpty(){
        if(curr_size==0){
            return true;
        }
        else{
            return false;
        }
    }
};