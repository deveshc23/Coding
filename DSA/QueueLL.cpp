#include<bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node* next;
};

class Q{
    Node *start=NULL;
    Node *end=NULL;
    int curr_size=0;
    public:
    void push(int x){
        Node *temp=new Node();
        temp->data=x;
        temp->next=NULL;
        curr_size++;
        if(start=NULL){
            start=temp;
            end=temp;
            return;
        }
        end->next=temp;
        end=temp;
    }
    void pop(){
        if(start==NULL){
            cout<<"Queue is empty"<<endl;
            return;
        }
        Node *temp=start;
        start=start->next;
        delete temp;
        curr_size--;
    }
    int top(){
        if(start==NULL){
            cout<<"Queue is empty"<<endl;
            return -1;
        }
        return start->data;
    }
    int size(){
        return curr_size;
    }
    bool isEmpty(){
        if(start==NULL){
            return true;
        }
        else{
            return false;
        }
    }
};