#include "graph.h"

queuenode* newqueueNode(pnode data, int value);
pnode Remove(queuenode** head);
void Insert(queuenode** head, pnode d, int p);
int isEmpty(queuenode** head);
int peek(queuenode** head);