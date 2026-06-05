#include<bits/stdc++.h>
using namespace std;

struct Element{
    int i;
    int j;
    int x;
};
struct Sparse{
    int m;
    int n;
    int num;
    Element *ele;
};
void create(Sparse *s){
    cin>>s->m>>s->n>>s->num;
    s->ele=new Element[s->num];
    for(int i=0;i<s->num;i++){
        cin>>s->ele[i].i>>s->ele[i].j>>s->ele[i].x;
    }
}
void Display(Sparse s){
    int i,j,k=0;
    for(i=0;i<s.m;i++){
        for(j=0;j<s.n;j++){
            if(i==s.ele[k].i && j==s.ele[k].j){
                cout<<s.ele[k++].x<<" ";
            }
            else{
                cout<<"0 ";
            }
        }
        cout<<endl;
    }
}
//Addition of two sparse matrices
struct Sparse * add(struct Sparse *s1,struct Sparse *s2){
    if(s1->m!=s2->m || s1->m!=s2->m){
        return 0;
    }
    struct Sparse *sum;
    sum=new Sparse;
    sum->m=s1->m;sum->n=s1->n;
    sum->ele=new Element[s1->num+s2->num];

    for(int i=0,j=0,k=0;i<s1->num && j<s2->num;){
        if(s1->ele[i].i<s2->ele[j].i){
            sum->ele[k++]=s1->ele[i++];
        }
        else if(s1->ele[i].i>s2->ele[j].i){
            sum->ele[k++]=s2->ele[j++];
        }
        else{
            if(s1->ele[i].j<s2->ele[j].j){
                sum->ele[k++]=s1->ele[i++];
            }
            else if(s1->ele[i].j>s2->ele[j].j){
                sum->ele[k++]=s2->ele[j++];
            }
            else{
                sum->ele[k]=s1->ele[i];
                sum->ele[k++].x=s1->ele[i++].x+s2->ele[j++].x;
            }
        }
    }
}
int main(){
    Sparse s;
    create(&s);
    Display(s);
    struct Sparse s1,s2,*s3;
    create(&s1);
    create(&s2);
    s3=add(&s1,&s2);
    Display(*s3);
    return 0;
}