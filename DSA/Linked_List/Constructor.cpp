#include <iostream>
using namespace std;
class Node{
    public:
        int value;
        Node* next;

        Node(int value){
            this->value=value;
            this->next=nullptr;
        }
        // the word "this" is used to refer to the current object
        // this->value refers to the value of the current object
        // value refers to the value of the parameter
        // this->value is used to distinguish between the two
};

class LinkedList{
    private:
        Node* head;
        Node* tail;
        int length;
    public:
        LinkedList(int value){
            Node* newNode=new Node(value);
            head=newNode;
            tail=newNode;
            length=1;
        }

        void printList(){
            Node* temp=head;
            while(temp!=nullptr){
                cout<<temp->value<<" ";
                temp=temp->next;
            }
        }

        void getHead(){
            cout<<"Head: "<<head->value<<endl;
        }

        void getTail(){
            cout<<"Tail: "<<tail->value<<endl;
        }

        void getLength(){
            cout<<"Length: "<<length<<endl;
        }

        ~LinkedList(){
            Node* temp=head;
            while(temp!=nullptr){
                Node* nextNode=temp->next;
                delete temp;
                temp=nextNode;
            }
        }

        void append(int value){
            Node* newNode=new Node(value);
            if(length==0){
                head=newNode;
                tail=newNode;
            }
            else{
                tail->next=newNode;
                tail=newNode;
            }
            length++;
        }

        void deletelast(){
            if(length==0){
                cout<<"List is empty"<<endl;
                return;
            }
            if(length==1){
                delete head;
                head=nullptr;
                tail=nullptr;
            }
            else{
                Node* temp=head;
                while(temp->next->next){
                    temp=temp->next;
                }
                delete temp->next;
                temp->next=nullptr;
                tail=temp;
            }
            length--;
        }

        void prepend(int value){
            Node* newNode = new Node(value);
            if(length==0){
                head=newNode;
                tail=newNode;
            }
            else{
                newNode->next=head;
                head=newNode;
            }
            length++;
        }

        void deletefirst(){
            if(length==0){
                cout<<"List is empty"<<endl;
                return;
            }
            else if(length==1){
                Node* temp=head;
                delete temp;
                head=nullptr;
                tail=nullptr;
            }
            else{
                Node* temp=head;
                head=head->next;
                delete temp;
            }
            length--;
        }

        Node* get(int index){
            if(index<0 || index>=length){
                cout<<"Index out of bounds"<<endl;
                return nullptr;
            }
            Node* temp=head;
            for(int i=0;i<index;i++){
                temp=temp->next;
            }
            return temp;
        }

        bool set(int index, int value){
            Node* temp=get(index);
            if(temp){
                temp->value=value;
                return true;
            }
            return false;
        }

        void insert(int value, int index){
            if(index<0 || index>length){
                cout<<"Index out of bounds"<<endl;
                return;
            }
            if(index==0){
                prepend(value);
                return;
            }
            if(index==length){
                append(value);
                return;
            }
            Node* newNode=new Node(value);
            Node* temp=get(index-1);
            newNode->next=temp->next;
            temp->next=newNode;
            length++;
        }

};

int main(){
    LinkedList* myLinkedList=new LinkedList(10);
    myLinkedList->printList();
    cout<<endl;
    myLinkedList->getHead();
    myLinkedList->getTail();
    myLinkedList->getLength();
}
