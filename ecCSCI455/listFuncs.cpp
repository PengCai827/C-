/*  Name:
 *  loginid:
 *  CS 455 Fall 2014
 *
 *  See listFuncs.h for specification of each function.
 */

#include <iostream>

#include <cassert>

#include "listFuncs.h"

 using namespace std;


 int lastIndexOf(ListType list, int val) {
 	int thisLoc=0;
 	int nowLoc=0;
 	bool find=false;
 	if (list == NULL) {//If the list is empty, return -1;
		return -1;
 	}
 	Node *p = list;
 	while (p != NULL) {
 		if(p->data==val){
 			thisLoc=nowLoc;//Get the last index;
 			find=true;//Indicate that the val is found;
 		}
 		nowLoc++;
 		p = p->next;
 	}
 	cout << endl;
 	if(!find){
 		return -1;
 	}
 	return thisLoc;  
 }


 void removeAdjacentEvens(ListType &list) {
 	Node* iterr = list;
 	if (list == NULL) {//If the list is empty, return -1;
		return ;
 	}
 	while (iterr->next!= NULL) {
 		if((iterr->data)%2==0){
 			if((iterr->next->data)%2==0){//If the value of next adjacent node is even, delete that node without moving forward the pointer;
                Node* del=iterr->next;
 				iterr->next=iterr->next->next;
 				delete del;
 				continue;
 			}
 		}	
 		iterr=iterr->next;//If the next one is not even, moving forward the pointer
 	}
 }

 void mirror(ListType & list) {
 	Node* head = NULL;
 	if (list == NULL) {//If the list is empty, return -1;
		return ;
 	}
 	Node* iterr = list;
 	while (iterr != NULL) {
 		Node* temp;
 	temp=(Node*)malloc(sizeof(Node*));   // allocate space for node

 	if(head==NULL){
 		temp->data = iterr->data;
 		temp->next=NULL;
 		head=temp;
 	}else{
 		temp->data = iterr->data;//Reading from the list node by node and create a new linked list which is the reverse order of the list;
 		temp->next=head;
 		head=temp;
 	}
 	iterr = iterr->next;
 }
 	//if want change the original one without creating the new one, use code below:
 	// Node *a = head, *b = head->next;
  //   while(a->next!=NULL)
  //   {
  //       b = a->next;
  //       a->next = a->next->next;
  //       b->next = head;
  //       head = b;
  //   }
 Node *concat ;
 concat = list ;  
 while ( concat -> next != NULL ){
 	concat = concat -> next ;//To locate at the last node;
 }
    concat -> next = head ;  // concatenate the second list after the first
     

}



void rotateLeft(ListType &list, int k) {
	Node* curr=list;
	Node* temp=list;
	int length=0;
	if (list == NULL) {//If the list is empty, return -1;
		return ;
 	}
	while(temp!=NULL){//To get the length of the list;
		length++;
		temp=temp->next;
	}
    
	if(length==0||length==1){
		return;
	}
	else if(k<=0||k>=length){
		return;
	}
	else{
		int count = 1;
		while (count < k && curr != NULL)
		{
			curr = curr->next;//Locate the pointer at the kth position
			count++;
		}

		Node *kthNode = curr;

    // curr will point to last node after this loop
    //To find the last node use: ->next!=NULL in the while loop
		while (curr->next != NULL)
		{
			curr = curr->next;
		}
    // Change next of last node to previous head
		curr->next = list;

    // Change head to (k+1)th node
		list = kthNode->next;

    // change next of kth node to NULL
		kthNode->next = NULL;
	}
	

}

