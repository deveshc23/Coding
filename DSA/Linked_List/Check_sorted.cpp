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

int isSorted(struct Node *p){
    while(p!=NULL){
        if(p->data>p->next->data){
            return 0;
        }
    }
    return 1;
}
void removeduplicates(struct Node *p){
    while(p!=NULL){
        struct Node *q=p->next;
        if(p->data==p->next->data){
            p->next=p->next->next;
            delete q;
        }
        else{
            p=p->next;
        }
    }
}

int main(){
    int A[]={3,5,7,10,15};
    create(A,5);
    cout<<isSorted(first);
    return 0;
}