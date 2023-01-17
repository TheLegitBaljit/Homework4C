#include "graph.h"

queuenode* newqueueNode(pnode data, int value);
pnode Remove(queuenode** head);
void Insert(queuenode** head, pnode d, int p);
int isEmpty(queuenode** head);
int peek(queuenode** head);
pedge new_edge(int weight, pedge next, pnode dest);