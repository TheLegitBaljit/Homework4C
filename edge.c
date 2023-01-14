#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include "node.h"


pedge new_edge(int weight, pedge next, pnode dest){
    pedge p = (pedge) malloc(sizeof(edge));
    p->endpoint = dest;
    p->next = next;
    p->weight = weight;
    return p;
}