#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node *next;
}*first;

void create(int A[],int n){
    int i;
    struct Node *t,*last;
    first=new Node;
    first->data=A[0];
    first->next=NULL;
    last=first;
    for(int i=1;i<n;i++){
        t=new Node;
        t->data=A[i];
        t->next=NULL;
        last->next=t;
    }
}

void Display(struct Node *p){
    if(p!=NULL){
        cout<<p->data<<" ";
        Display(p->next);
    }
}