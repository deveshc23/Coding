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

int count(struct Node *p){
    int count=0;
    while(p!=NULL){
        count++;
        p=p->next;
    }
    return count;
}

void Delete(struct Node *p,int index){
    struct Node *q=NULL;
    if(index<0 || index>count(p)){
        return;
    }
    if(index==1){
        q=first;
        first=first->next;
        delete q;
    }
    else{
        for(int i=0;i<index-1;i++){
            q=p;
            p=p->next;
        }
        q->next=p->next;
        delete p;
    }
}
int main(){
    int A[]={3,5,7,10,15};
    create(A,5);
    Delete(first,2);
    return 0;
}