#include <stdio.h>
#include "graph.h"
#include "node.h"
#include <stdlib.h>
#include "edge.h"
#include "queue.h"


queuenode* newqueueNode(pnode data, int value){
	queuenode* p = (queuenode*)malloc(sizeof(queuenode));
    if(p == NULL)
        exit(0);
    p->nodedata = data;
    p->priority = value;
    p->next = NULL;
	return p;
}

pnode Remove(queuenode** head){
	pnode temp = (*head)->nodedata;
	queuenode* temptofree = *head;
	(*head) = (*head)->next;
	free(temptofree);
	return temp;
}

void Insert(queuenode** head, pnode d, int p){
	queuenode* start = (*head);
	queuenode* temp = newqueueNode(d, p);
	if (isEmpty(head)){
		(*head) = temp;
		return;
	}

	if ((*head)->priority > p) {
		temp->next = *head;
		(*head) = temp;
	}
	else {

		while (start->next != NULL &&
			start->next->priority < p) {
			start = start->next;
		}

		temp->next = start->next;
		start->next = temp;
	}
}

// Function to check is list is empty
int isEmpty(queuenode** head){
	return (*head) == NULL;
}
