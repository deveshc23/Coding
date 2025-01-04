#include<bits/stdc++.h>
using namespace std;

int main(){
    pair <int,int> p={1,3};
    //cout<<p.first<<" "<<p.second<<endl;
    pair <int,int> array[] = {{1,2},{3,4},{5,6}};
    //cout<<array[0].second<<endl;

    vector<int> v;
    v.push_back(1);
    v.emplace_back(2); //emplace_back is faster than push_back but has the same functionality
    //cout<<v[0]<<" "<<v[1]<<endl;

    vector <int> v1(5); //vector of size 5

    vector <int> v2(5,3); //vector of size 5 with all elements as 3 (3,3,3,3,3)
    vector <int> v3(v); //copy of vector v
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    vector <int>::iterator it=v.begin(); // points to the first element
    cout<<*it<<endl;
    it=it+2;
    cout<<*it<<endl;
    vector<int>::iterator it1=v.end(); //points to the element after the last element not the last element
    // the rend iterator points to the element before the first element
    vector<int>::reverse_iterator it2=v.rend();
    vector<int>::reverse_iterator it3=v.rbegin();
    // these iterators are reverse iterators

    cout<<v.back()<<endl; //returns the last element
    cout<<*it1<<endl;
    v.erase(it); //erases the element at the position of the iterator
    v.erase(it,it+2); //erases the elements from the first iterator to the second iterator
    for(vector<int>::iterator it =v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    }
    v.insert(it,5); //inserts 5 at the position of the iterator

    v.insert(v.begin(),3,7); //inserts 7 three times at the beginning of the vector
    vector<int> copy(2,9);
    v.insert(v.begin() + 5, copy.begin(), copy.end()); //inserts the elements from the first iterator to the second iterator at the position of the iterator

    cout<<v.size()<<endl; //returns the size of the vector
    cout<<v.empty()<<endl; //returns 1 if the vector is empty else 0
    return 0;
}