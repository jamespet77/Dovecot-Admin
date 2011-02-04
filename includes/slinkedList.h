/*
DoveCot Admin
=======================================================================
$Author: jamespet $
$LastChangedDate: 2008-01-14 14:20:22 -0600 (Mon, 14 Jan 2008) $
$Rev: 476 $
=======================================================================
Copyright (C) 2008 James D. Peterson <James.Peterson@linuxjet.com>

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

// file: slinkedList.h
// author:  Rick
// Updated: James Peterson
// 1-24-2006
// linked LISTCLASS with a search that is adapted to return a pointer to the item
// also, print inserts a newline after each item

#ifndef __SLINKLIST__
#define __SLINKLIST__
#include <iostream>
#include <stdlib.h>
#include <string>
#include <linkedList.h>
#include <iomanip>

using namespace std;

template <class Type>
class slinkedListType : public linkedListType<Type> {
public:
	nodeType<Type>* firstNode();
	nodeType<Type>* lastNode();
    Type* search(const Type &searchItem);
    Type* search(const char *searchItem);
    void print() const;
	void	sort();
private:
	void M_Sort(nodeType<Type> **head);
	nodeType<Type>* Merge(nodeType<Type> **leftHead,nodeType<Type> **rightHead);
	void SplitLinkedList(nodeType<Type> *head,nodeType<Type> **leftHead,nodeType<Type> **rightHead);
};

template<class Type>
nodeType<Type>*	slinkedListType<Type>::firstNode() {
	return this->first;
}

template<class Type>
nodeType<Type>*	slinkedListType<Type>::lastNode() {
	return this->last;
}

template<class Type>
Type*	slinkedListType<Type>::search(const Type &searchItem) {
    nodeType<Type> *current; //pointer to traverse the LISTCLASS
    
	//current = new nodeType<Type>;
	current = this->first; //set current to point to the first 
    //current = linkedListType<Type>::first; //set current to point to the first 
                     //node in the LISTCLASS

   	while (current != NULL) {    //search the LISTCLASS
		if (current->info == searchItem){ //searchItem is found
			return &current->info;
		} else {
			if (current->link != NULL) {
            		current = current->link; //make current point to
			} else {
				return NULL;
			}
			//the next node
		}
	}
    return NULL; 
}

template<class Type>
Type*	slinkedListType<Type>::search(const char * searchItem) {
    nodeType<Type> *current; //pointer to traverse the LISTCLASS
    
	//current = new nodeType<Type>;
	current = this->first; //set current to point to the first 
    //current = linkedListType<Type>::first; //set current to point to the first 
                     //node in the LISTCLASS

   	while (current != NULL) {    //search the LISTCLASS
		if (strcmp(current->info.getName(),searchItem) == 0){ //searchItem is found
			return &current->info;
		} else {
			if (current->link != NULL) {
            		current = current->link; //make current point to
			} else {
				return NULL;
			}
			//the next node
		}
	}
    return NULL; 
}

template<class Type>
void	slinkedListType<Type>::print() const{
	nodeType<Type> *current; //pointer to traverse the LISTCLASS

	current = this->first;  //set current so that it points to 
       			      //the first node
	while (current != NULL) {
	   printf("%s\n",current->info.getName());
	   current = current->link;
	}
}

template<class Type>
void	slinkedListType<Type>::sort() {
	nodeType<Type> *node;
	node = this->first;
	M_Sort(&node);
	
}

template<class Type>
void 	slinkedListType<Type>::M_Sort(nodeType<Type> **head) {
	nodeType<Type> *leftHead = NULL;
	nodeType<Type> *rightHead = NULL;
 
	if(!head) {
//	printf("NULL HEAD\n");
		return;
	}
	if(!*head) {
//	printf("NULL HEAD ptr\n");
		return;
	}
	if(!(*head)->link) {
//	printf("NULL HEAD ptr link\n");
		return;
	}
//	printf("-------------------===============\n");
//	print();
	leftHead = *head;
	rightHead = *head;
	//Keep splitting the list in the middle
	SplitLinkedList(*head,&leftHead,&rightHead);
 
	M_Sort(&leftHead);
	M_Sort(&rightHead);
	//head now points to the merged list 
	*head = Merge(&leftHead,&rightHead);
}

template<class Type>
nodeType<Type>* 	slinkedListType<Type>::Merge(nodeType<Type> **leftHead, nodeType<Type> **rightHead) {
	//We need 2 pointers in both the lists to merge the nodes
	nodeType<Type> *leftFront = NULL;
	nodeType<Type> *leftRear = NULL;
	nodeType<Type> *rightFront = NULL;
	nodeType<Type> *rightRear = NULL;
 
	//Do the Null Pointer Checks
	if(!leftHead) {
		return NULL;
	}
	if(!*leftHead) {
		return NULL;
	}
	if(!rightHead) {
		return *leftHead;
	}
	if(!*rightHead) {
		return *leftHead;
	}
	//Initialize the pointers in left, right Lists
	leftFront = *leftHead;
	leftRear = NULL;
	rightFront = *rightHead;
	rightRear = NULL;
 
	// If there is only one node in both the lists
	// then simply do a check and merge the nodes
	if(leftFront->link == NULL && rightFront->link == NULL) {
		if(leftFront->info < rightFront->info) {
		//printf("1 %s -- %s, %d\n",leftFront->info.getUserName(),rightFront->info.getUserName(),(leftFront->info < rightFront->info));
			leftFront->link = rightFront;
		} else {
		//printf("2 %s -- %s, %d\n",leftFront->info.getUserName(),rightFront->info.getUserName(),(leftFront->info < rightFront->info));
			rightFront->link = leftFront;
			*leftHead = rightFront;
		}
		return *leftHead;
	}
 
	//If either of the list has more than 1 node
	/*The idea here is to have a rightFront pointer as a checkpoint
	  and keep moving the leftFront pointer until you reach a node
	  on the right list  whose value is > leftFront->info.getName(), then merge at that node using
	  the rear pointers */
	while(leftFront != NULL && rightFront != NULL) {
		//keep traversing until you hit a node on the left list
		//such that its value is > the value on right list
		while(leftFront != NULL && leftFront->info < rightFront->info) {
		//printf("3 %s -- %s, %d\n",leftFront->info.getUserName(),rightFront->info.getUserName(),(leftFront->info < rightFront->info));
			leftRear = leftFront;
			leftFront = leftFront->link;
		}
		// check for NULL pointers
		if(leftFront != NULL && rightFront != NULL) {
			//printf("BOTH NOT NULL\n");
			/*If the rear pointer is pointing to NULL it indicates
			  the data on the rightlist to merge is supposed to get 
			  to the beginning of the merged list */
			if(leftRear == NULL) {
				//printf("LR NULL\n");
				rightRear = rightFront;
				rightFront = rightFront->link;
				leftRear = rightRear;
				leftRear->link = leftFront;
				*leftHead = rightRear;
				if(!rightFront) {
					break;
				}
			} else {
			//printf("ELSE\n");
			//Else the node is supposed to merged in between / end of the merged list
				rightRear = rightFront;
				rightFront = rightFront->link;
				leftRear->link = rightRear;
				leftRear = leftRear->link;
				leftRear->link = leftFront;
				if(!rightFront) {
					break;
				}
			}
			if(leftFront->info < rightFront->info) {
			//printf("4 %s -- %s, %d\n",leftFront->info.getUserName(),rightFront->info.getUserName(),(leftFront->info < rightFront->info));
				leftRear = leftFront;
				leftFront = leftFront->link;
			} else {
				//printf("Continue\n");
				continue;
			}
		}
	}// end of while
 
	if(leftFront == NULL && rightFront != NULL) {
		//printf("NULL and not NULL\n");
		leftRear->link = rightFront;
	}
	return *leftHead;
}

template<class Type>
void 	slinkedListType<Type>::SplitLinkedList(nodeType<Type> *head,nodeType<Type> **leftHead,nodeType<Type> **rightHead) {
	nodeType<Type> *leftTemp = NULL;		
	nodeType<Type> *rightTemp = NULL;
	if(!head) {
		return;
	}
	if(!leftHead || !rightHead) {
		return;
	}
	if(!*leftHead || !*rightHead) {
		return;
	}
	leftTemp = head;
	rightTemp = head;
 
	if(!(rightTemp->link)) {
		*rightHead = NULL;
		return;
	}
	while(rightTemp->link != NULL) {
		rightTemp = rightTemp->link;
		if(rightTemp->link != NULL) {
			leftTemp = leftTemp->link;
			rightTemp = rightTemp->link;
		} else {
			*rightHead = leftTemp->link;
			leftTemp->link = NULL;
		}
	}
	if(*rightHead == head) {
		*rightHead = leftTemp->link;
		leftTemp->link = NULL;
	}
	leftTemp = *leftHead;
	rightTemp = *rightHead;
}
#endif
