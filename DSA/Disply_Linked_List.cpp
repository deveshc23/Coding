#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    Node *next;
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
        last=t;
    }
}

void Display(struct Node *p){
    while(p!=NULL){
        cout<<p->data<<" ";
        p=p->next;
    }
}
//Deleting a node
int Delete(struct Node *p,int index){
    struct Node *q=NULL;
    int x=-1;
    while(p!=NULL){
        if(index==0){
            q=first;
            x=first->data;
            first=first->next;
        }
        else{
            for(int i=0;i<index-1;i++){
                q=p;
                p=p->next;
            }
            if(p){
                q->next=p->next;
                x=p->data;
                delete p;
            }
        }
    }
}
//How to check if link list is sorted
int isSorted(struct Node *p){
    int x=-65536;
    while(p!=NULL){
        if(p->data<x){
            return 0;
        }
        else{
            x=p->data;
            p=p->next;
        }
    }
}
//How to remove duplicate from a sorted linked list
void removeDuplicate(struct Node *p){
    struct Node *q=p->next;
    while(q!=NULL){
        if(p->data==q->data){
            p->next=q->next;
            free(q);
            q=p->next;
        }
        else{
            p=q;
            q=q->next;
        }
    }
}
//Reversing linked list using sliding pointers
void Reverse(struct Node *p){
    struct Node *q=NULL,*r=NULL;
    while(p!=NULL){
        r=q;
        q=p;
        p=p->next;
        q->next=r;
    }
    first=q;
}
void InsertLast(struct Node *p,int x){
    struct Node *t,*last;
    t=new Node;
    t->data=x;
    t->next=NULL;
    if(first==NULL){
        first=last;
        last=t;
    }
    else{
        last->next=t;
        last=t;
    }
}

//inserting in a sorted linked list
void Insert(struct Node *p,int x){
    struct Node *t,*q=NULL;
    t=new Node;
    t->data=x;
    t->next=NULL;
    if(first==NULL){
        first=t;
    }
    else{
        while(p && p->data<x){
            q=p;
            p=p->next;
        }
        if(p==first){
            t->next=first;
            first=t;
        }
        else{
            t->next=q->next;
            q->next=t;
        }
    }
    }
int count(struct Node *p){
    int l=0;
    while(p){
        l++;
        p=p->next;
    }
    return l;
}

int sum(struct Node *p){
    int s=0;
    while(p){
        s+=p->data;
        p=p->next;
    }
    return s;
}

void Insert(struct Node *p,int index,int x){
    struct Node *t;
    if(index <0 || index > count(p)){
        return;
    }
    t=new Node;
    t->data=x;
    if(index==0){
        t->next=first;
        first=t;
    }else{
        for(int i=0;i<index-1;i++){
            p=p->next;
        }
        t->next=p->next;
        p->next=t;
    }
}
int main(){
    int A[]={3,5,7,10,15};
    create(A,5);
    Insert(first,0,10);
    Display(first);
    return 0;
}