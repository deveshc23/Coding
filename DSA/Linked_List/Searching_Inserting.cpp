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

int search(struct Node *p,int key){
    int index=0;
    while(p!=NULL){
        if(p->data==key){
            return index;
        }
        index++;
    }
    return -1;
}

int count(struct Node *p){
    int count=0;
    while(p!=NULL){
        count++;
        p=p->next;
    }
    return count;
}

void insert(struct Node *p,int value,int index){
    struct Node *t;
    if(index < 0 || index > count(p)){
        return;
    }
    t=new Node;
    t->data=value;
    if(index=0){
        t->next=first;
        first=t;
    }
    else{
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
    cout<<search(first,10);
    insert(first,12,3);
    return 0;
}