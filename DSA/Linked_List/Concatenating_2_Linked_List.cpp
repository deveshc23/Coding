#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node *next;
}*first=NULL;

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
        last=t;
    }
}

void concatenate(struct Node *p,struct Node *q){
    first=p;
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=q;
}

void Display(struct Node *p){
    while(p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
}

int main(){
    int A[]={3,5,7,10,15};
    int B[]={9,8,6,12,20};
    struct Node *temp;
    create(A,5);
    struct Node *p=first;
    create(B,5);
    struct Node *q=first;
    concatenate(p,q);
    Display(p);
    return 0;
}