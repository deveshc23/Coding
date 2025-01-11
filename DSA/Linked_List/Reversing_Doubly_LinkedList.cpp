#include <bits/stdc++.h>
using namespace std;

struct Node{
    struct Node *prev;
    int data;
    struct Node *next;
}*first=NULL;

void create(int A[],int n){
    struct Node *t,*last;
    first=new Node;
    first->data=A[0];
    first->prev=first->next=NULL;
    last=first;
    for(int i=1;i<n;i++){
        t=new Node;
        t->data=A[i];
        t->prev=last;
        t->next=last->next;
        last->next=t;
        last=t;
    }
}

void Display(struct Node *p){
    while(p){
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}

int Length(struct Node *p){
    int len=0;
    while(p){
        len++;
        p=p->next;
    }
    return len;
}

void Reverse(struct Node *p){
    struct Node *temp;
    while(p){
        temp=p->next;
        p->next=p->prev;
        p->prev=temp;
        p=p->prev;
        if(p!=NULL && p->next==NULL){
            first=p;
        }
    }
}

int main(){
    int A[]={10,20,30,40,50};
    create(A,5);
    Display(first);
    Reverse(first);
    Display(first);
    return 0;
}