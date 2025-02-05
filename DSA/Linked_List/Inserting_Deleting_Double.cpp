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

void Insert(struct Node *p,int index,int x){
    struct Node *t;
    if(index<0 || index>Length(p)){
        return;
    }
    if(index==0){
        t=new Node;
        t->data=x;
        t->prev=NULL;
        t->next=first;
        first->prev=t;
        first=t;
    }
    else{
        for(int i=0;i<index-1;i++){
            p=p->next;
        }
        t=new Node;
        t->prev=p;
        t->next=p->next;
        if(p->next){
            p->next->prev=t;
        }
        p->next=t;
    }
}

int Delete(struct Node *p,int index){
    int x=-1;
    if(index<0 || index>Length(p)){
        return -1;
    }
    if(index==1){
        first=first->next;
        if(first){
            first->prev=NULL;
        }
        x=p->data;
        delete p;
    }
    else{
        for(int i=0;i<index-1;i++){
            p=p->next;
        }
        p->prev->next=p->next;
        x=p->data;
        if(p->next){
            p->next->prev=p->prev;
        }
        delete p;
    }
    return x;
}

int main(){
    int A[]={10,20,30,40,50};
    create(A,5);
    Display(first);
    Insert(first,0,5);
    Display(first);
    cout<<Delete(first,1)<<endl;
    Display(first);
    return 0;
}