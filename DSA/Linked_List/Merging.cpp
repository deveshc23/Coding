#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node *next;
}*first=NULL,*second=NULL,*third = NULL;

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

void create2(int A[],int n){
    int i;
    struct Node *t,*last;
    second=new Node;
    second->data=A[0];
    second->next=NULL;
    last=second;
    for(int i=1;i<n;i++){
        t=new Node;
        t->data=A[i];
        t->next=NULL;
        last->next=t;
        last=t;
    }
}

void merge(struct Node *first,struct Node *second){
    struct Node *last;
    if(first->data < second->data){
        third=last=first;
        first=first->next;
        third->next=NULL;   
    }
    else{
        third=last=second;
        second=second->next;
        third->next=NULL;
    }
    while(first!=NULL && second!=NULL){
        if(first->data < second->data){
            last->next=first;
            last=first;
            first=first->next;
            last->next=NULL;
        }
        else{
            last->next=second;
            last=second;
            second=second->next;
            last->next=NULL;
        }
    }
    if(first!=NULL){
        last->next=first;
    }
    if(second!=NULL){
        last->next=second;
    }
}

void Display(struct Node *p){
    while(p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
}

int main(){
    int A[]={2,3,6,8,9};
    int B[]={4,5,7,10,11};
    create(A,5);
    create2(B,5);
    //Display(first);
    //Display(second);
    merge(first,second);
    Display(third);
}