#ifndef GRAPH_
#define GRAPH_

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;

typedef struct queueNode {
	pnode nodedata;
	int priority;
	struct queueNode* next;
} queuenode;

typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
    int seq;
} node, *pnode;

void build_graph_cmd(pnode *head);
void insert_node_cmd(pnode *head);
void delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
void deleteGraph_cmd(pnode* head);
void shortest_path_cmd(pnode head);
void permutation(int* cities,int start,int end,int size_of_nodes, int* ans, pnode head);
void TSP_cmd(pnode head);
void dijkstra(int *arr,pnode here);
void swap(int* a, int* b);

#endif
