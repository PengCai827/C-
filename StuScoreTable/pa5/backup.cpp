// Table.cpp  Table class implementation
// CSCI 455 PA5
// Name:Peng Cai
// Loginid:pengcai

/*
 * Modified 11/22/11 by CMB
 *   changed name of constructor formal parameter to match .h file
 */

#include "Table.h"

#include <iostream>
#include <string>
#include <cassert>

//*************************************************************************
// Node class definition and member functions
//     You don't need to add or change anything in this section

// Note: we define the Node in the implementation file, because it's only
// used by the Table class; not by any Table client code.
int HashFunc();
struct Node {
  string key;
  int value;
  Node *next;

  Node(const string &theKey, int theValue);

  Node(const string &theKey, int theValue, Node *n);
};

Node::Node(const string &theKey, int theValue) {
  key = theKey;
  value = theValue;
  next = NULL;
}

Node::Node(const string &theKey, int theValue, Node *n) {
  key = theKey;
  value = theValue;
  next = n;
}

typedef Node * ListType;

//*************************************************************************
ListType * list;

Node*head=NULL;
Node*tail=NULL;
//Node* loc;
//ListType* chain;
int numBucket;
int maxCount=0;

int numEntry;
int size=0;

void chainNumber();
Table::Table() {
    
    hashSize= HASH_SIZE;
    list=new ListType[HASH_SIZE];
   // chain=list;
    size=hashSize;
}


Table::Table(unsigned int hSize) {
    hashSize=hSize;
    list=new ListType[hSize];
    //chain=list;
    size=hashSize;

}


int * Table::lookup(const string &key) {
    Node* loc;
    bool find=false;
   loc = list[hashCode(key)];//To check whether a key is in the table or not;
        while (loc != NULL) {
                if (loc -> key == key) {
                    find=true;
                    return &(loc -> value);//return the address of the value to the key;
            }
            loc=loc->next;
        }
   if(!find){
    return NULL;
   }
    return NULL;
}

bool Table::remove(const string &key) {
     Node *pre = NULL, *del = NULL;
    if (list[hashCode(key)]==NULL) {//If the key to be removed doesn't even exist, then print out the message;
        cout<<"The name doesn't exist in the score table."<<endl;
        return false;
    }
    if (head->key==key) {//If the key happen to be the first one in the list;
        del=head;//Then make the del poinrter point to head;
        head=del->next;//And make the head pointer point to the next one,i.e make the next one become head after removement;
        delete del;
        numEntry--;
        chainNumber();

        return true;
    }
    pre=head;//If the key to be removed doesn't locate at the head of the list, then make pre pointer starts at the head;
    del=head->next;
    
    while (del != NULL) {
        if (del->key == key) {
            pre->next= del->next;//If the key is found, making the one before the key link to the one after the key;
            if (del == tail) {//If the key at the end of the list, making the one ahead of the key become the end of the list;
                tail = pre;
            }
            delete del;
            break;
        }
        pre = del;//To iterate the whole list;
        del = del->next;
    }
    numEntry--;
    chainNumber();

    return true;
}

bool Table::insert(const string &key, int value) {
    
    Node* newNode=new Node(key,value);
    if(lookup(key)!=NULL){//If the key is already exited in the table, then return false;
        return false;
    }

    if(head==NULL){//If the table is happen to be empty
//        if(list[hashCode(key)]!=NULL){//If there happen to be other key at the same bucket, then make the number of entry added by 1;
//           list[hashCode(key)]=newNode;
//            numEntry++;
//
//        }else{
//            list[hashCode(key)]=newNode;
//            numBucket++;//If the bucket only has this key, then add both bucket and entry number by 1;
//            numEntry++;
//        }
        head=newNode;
        tail=newNode;
        numBucket++;
        numEntry++;
        if(maxCount == 0) {
            maxCount = 1;
        }
        return true;
    }else{//If the table is not empry

        tail->next = newNode;
        newNode->next = NULL;
        tail = newNode;
        if(list[hashCode(key)]!=NULL){//If there happen to be other key at the same bucket, then make the number of entry added by 1;
            list[hashCode(key)]=newNode;
            numEntry++;
            
        }else{
            list[hashCode(key)]=newNode;////If the bucket only has this key, then add both bucket and entry number by 1;
            numBucket++;
            numEntry++;
        }
        chainNumber();

        return true;

    }
    
}

int Table::numEntries() const {
    Node *pre = head;
    int count=0;
    while (pre!=NULL) {//Iterating the whole list to count entries;
        count++;
        
        pre=pre->next;
    }

    return count;
}


void Table::printAll() const {
    Node *pre = head;
    while (pre!=NULL) {
        cout<<pre->key<<":"<<pre->value<<endl;//Iterate the whole list and print out the name and score pair;
        pre=pre->next;
    }
    return;

}

void Table::hashStats(ostream &out) const {
    
    cout<<"number of buckets: "<<size<<endl;
    cout<<"number of entries: "<<numEntries()<<endl;
    cout<<"number of non-empty buckets: "<<numBucket<<endl;
    cout<<"longest chain: "<<maxCount <<endl;
    
    
}
void chainNumber(){//Count the length of the chain;
    int i=0;
    maxCount=0;
    Node* chain;
    if(numEntry==0){
        
    }else{
      while(i<size){
        int numChain=0;
          chain=list[i];

        if(list[i]!=NULL){
            while (chain!=NULL) {
                numChain++;
                chain=chain->next;
            }
            if (numChain>maxCount) {
                maxCount=numChain;
            }

        }
        i++;
    }
   // return maxCount;
    }
    
}

// add definitions for your private methods here
