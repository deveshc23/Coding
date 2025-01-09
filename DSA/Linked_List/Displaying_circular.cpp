#include <bits/stdc++.h>
using namespace std;

struct Node{
    int data;
    struct Node *next;
}*Head=NULL;

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

int Length(struct Node *p){
    struct Node *q=p;
    int count =0;
    do{
        count++;
        p=p->next;
    }while(q!=p);
    return count;
}

int main(){
    int A[]={2,3,4,5,6};
    create(A,5);
    Display(Head);
    cout<<endl;
    cout<<Length(Head);
    return 0;
}