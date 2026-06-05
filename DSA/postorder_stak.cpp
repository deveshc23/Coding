#include <bits/stdc++.h>
using namespace std;
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(): val(0), left(NULL), right(NULL) {}
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

void postorder(TreeNode* root){
    stack<TreeNode*> st1, st2;
    st1.push(root);
    while(!st1.empty()){
        TreeNode* node=st1.top();
        st1.pop();
        st2.push(node);
        if(node->left!=NULL){
            st1.push(node->left);
        }
        if(node->right!=NULL){
            st1.push(node->right);
        }
    }
    while(!st2.empty()){
        TreeNode* node=st2.top();
        st2.pop();
        cout<<node->val<<" ";
    }
}