#include<bits/stdc++.h>
using namespace std;

struct Array{
    int *arr;
    int size;
    int length;
};

struct Array * merge(struct Array *arr1, struct Array *arr2){
    int i=0,j=0,k=0;
    struct Array *arr3 = (struct Array *)malloc(sizeof(struct Array));
    //arr3->arr = (int *)malloc((arr1->length + arr2->length)*sizeof(int));
    while(i<arr1->length && j<arr2->length){
        if(arr1->arr[i]<arr2->arr[j]){
            arr3->arr[k++] = arr1->arr[i++];
        }
        else{
            arr3->arr[k++] = arr2->arr[j++];
        }
    }
    for(;i<arr1->length;i++){
        arr3->arr[k++] = arr1->arr[i];
    }
    for(;j<arr2->length;j++){
        arr3->arr[k++] = arr2->arr[j];
    }
    arr3->length = arr1->length + arr2->length;
    arr3->size = 10;
}
int main() {
    // Initialize arr1
    Array arr1;
    arr1.size = 10;
    arr1.length = 5;
    arr1.arr = new int[arr1.length]{2, 6, 10, 15, 25};

    // Initialize arr2
    Array arr2;
    arr2.size = 10;
    arr2.length = 5;
    arr2.arr = new int[arr2.length]{3, 4, 7, 18, 20};

    // Merge the arrays
    Array *arr3 = merge(&arr1, &arr2);

    // Display the merged array
    for (int i = 0; i < arr3->length; i++) {
        cout << arr3->arr[i] << " ";
    }
    cout << endl;

    // Free dynamically allocated memory
    delete[] arr1.arr;
    delete[] arr2.arr;
    delete[] arr3->arr;
    delete arr3;

    return 0;
}
