#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

Node* maketree(){
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->left->right->left = new Node(6);
    root->right->left = new Node(7);
    root->left->left->left = new Node(8);
    root->right->right = new Node(11);  // add this
    root->right->right->left = new Node(9);
    root->right->right->right = new Node(10);
    return root;
}

void preorder(Node* node){
    if(node == NULL) return;
    cout << node->data << " ";
    preorder(node->left);
    preorder(node->right);
}

int main(){
    Node* treeroot = maketree();
    preorder(treeroot);
    return 0;
}
