#include "stdio.h"
#include "graph.h"
#include "stdlib.h"

pnode getNode(int data, pnode head){
    while (head){
        if (head->node_num == data){
            return head;
        }
        head = head->next;
    }
    return NULL;
}

pnode newnode(int k, pnode next){
    pnode p = (pnode) malloc(sizeof(node));
    if(p==NULL)
        exit(0);
    p->node_num = k;
    p->next = next;
    p->edges = NULL;
    return p;
}



pnode generate(int k){
    pnode head = NULL;
    for (int i=k-1;i>=0;i--){
        head = newnode(i,head);
    }
    return head;
}

void remove_out_edges(pnode here){
    pedge next = here->edges;
    while(next){
        pedge prev = next;
        next = next->next;
        free(prev);
    }
}

void remove_edge_to(int data, pnode here){
    pedge check_edge = here->edges;
    if(check_edge){
        if (check_edge->endpoint->node_num == data){
            pedge delete = check_edge;
            here->edges = check_edge->next;
            free(delete);
            return;
        }
        while(check_edge->next != NULL){
            if (check_edge->next->endpoint->node_num == data){
                pedge delete = check_edge->next;
                check_edge->next = delete->next;
                free(delete);
                return;
            }
            check_edge = check_edge->next;
        }
    }
}

pnode insert_node(int data, pnode *head){
    pnode *p = head;
    while ((*p)->next)
    {
        if((*p)->node_num< data && (*p)->next->node_num> data){
            pnode new = newnode(data,(*p)->next);
            (*p)->next = new;
            return new;
        }
        p=&((*p)->next);
    }
    pnode new = newnode(data,(*p)->next);
    (*p)->next = new;
    return new;
}