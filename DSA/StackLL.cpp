#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* next;
};

//make a stack using linked list
class StackLL{
    Node *top=NULL;
    int curr_size=0;
    public:
    void push(int x){
        Node *temp=new Node();
        temp->data=x;
        temp->next=NULL;
        curr_size++;
        if(top==NULL){
            top=temp;
        }
        else{
            temp->next=top;
            top=temp;
        }
    }
    void pop(){
        if(top==NULL){
            cout<<"Stack Underflow"<<endl;
            return;
        }
        Node *temp=top;
        top=top->next;
        delete temp;
        curr_size--;
    }
    int size(){
        return curr_size;
    }
    int top(){
        if(top==NULL){
            cout<<"Stack is empty"<<endl;
            return -1;
        }
        return top->data;
    }
    bool isEmpty(){
        if(top==NULL){
            return true;
        }
        else{
            return false;
        }
    }
};