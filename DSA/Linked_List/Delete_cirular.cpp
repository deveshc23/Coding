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

int Delete(struct Node *p,int index){
    struct Node *q;
    int i,x;
    if(index<0 || index>count(p)){
        return -1;
    }
    if(index==1){
        while(p->next!=Head){
            p=p->next;
        }
        x=Head->data;
        if(Head==p){ //When there is only one element in the list
            delete Head;
            Head=NULL;
        }
        else{
            p->next=Head->next;
            delete Head;
            Head=p->next;
        }
    }
}

int main(){
    int A[]={2,3,4,5,6};
    create(A,5);
    Delete(Head,1);
    Display(Head);
    return 0;
}