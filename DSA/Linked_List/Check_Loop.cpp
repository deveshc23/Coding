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
// In a loop if a pointer traverses faster than another pointer and they meet at some point then there is a loop
int isLoop(struct Node *p){
    struct Node *q;
    q=p;
    do{
        p=p->next;
        q=q->next;
        q=q==NULL?NULL:q->next;
    }
    while(p && q && p!=q);
    if(p==q){
        return 1;
    }
    else{
        return 0;
    }
}