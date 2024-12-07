#include<bits/stdc++.h>
using namespace std;
struct Array{
    int a[10];
    int size;
    int length;
};
void Display(struct Array arr){
    cout<<"Elements are: ";
    for(int i=0;i<arr.length;i++){
        cout<<arr.a[i]<<" ";
    }
    cout<<endl;
}
void Append(struct Array *arr,int x){
    if(arr->length<arr->size){
        arr->a[arr->length++]=x;
    }
}
void Insert(struct Array *arr,int index,int x){
    if(index>=0 && index<=arr->length){
        for(int i=arr->length;i>index;i--){
            arr->a[i]=arr->a[i-1];
        }
        arr->a[index]=x;
        arr->length++;
    }
}
void Erase(struct Array *arr,int index){
    if(index>=0 && index<arr->length){
        for(int i=index;i<arr->length-1;i++){
            arr[i]=arr[i+1];
        }
        arr->length--;
    }
}
int main(){
    struct Array arr={{2,3,4,5,6},10,5};
    Display(arr);
    Append(&arr,10);
    Insert(&arr,0,11);
    Append(&arr,10);
    Display(arr);
    Erase(&arr,0);
    return 0;
}