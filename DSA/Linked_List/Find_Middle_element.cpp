#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
}*first=NULL;

void create(int A[], int n) {
    Node *t, *last;
    first = new Node;
    first->data = A[0];
    first->next = NULL;
    last = first;

    for(int i=1; i<n; i++) {
        t = new Node;
        t->data = A[i];
        t->next = NULL;
        last->next = t;
        last = t;
    }
}

int findMiddle(Node *p){
    Node *q=p;
    while(q!=NULL){
        q=q->next;
        if(q!=NULL){
            q=q->next;
            p=p->next;
        }
    }
    return p->data;
}

int main() {
    int A[] = {1, 2, 3, 4, 5};
    create(A, 5);
    cout<<findMiddle(first);
    return 0;
}