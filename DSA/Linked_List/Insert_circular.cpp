#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node *next;
}*Head;

void create(int A[],int n){
    int i;
    struct Node *t,*last;
    Head=new Node;
    Head->data=A[0];
    Head->next=Head;
    last=Head;
    for(int i=1;i<n;i++){
        t=new Node;
        t->data=A[i];
        t->next=last->next;
        last->next=t;
        last=t;
    }
}

void Display(struct Node *h){
    struct Node *p=h;
    do{
        cout<<p->data<<" ";
        p=p->next;
    }while(p!=h);
}

int count(struct Node *p){
    struct Node *q=p;
    int count =0;
    do{
        count++;
        p=p->next;
    }while(q!=p);
    return count;
}

int Insert(struct Node *p,int index,int x){
    struct Node *t;
    if(index<0 || index>count(p)){
        return -1;
    }
    if(index==0){
        t=new Node;
        t->data=x;
        if(Head==NULL){
            Head=t;
            Head->next=Head;
        }
        else{
            while(p->next!=Head){
                p=p->next;
            }
            p->next=t;
            t->next=Head;
            Head=t;
        }
    }
    else{
        for(int i=0;i<index-1;i++){
            p=p->next;
        }
        t=new Node;
        t->data=x;
        t->next=p->next;
        p->next=t;
    }
    return 0;
}