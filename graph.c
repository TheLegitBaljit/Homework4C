#include <stdio.h>
#include "graph.h"
#include "node.h"
#include <stdlib.h>
#include "edge.h"
#include "queue.h"
#include <limits.h>

void build_graph_cmd(pnode *head){
    int i;
    scanf("%d", &i);
    pnode here = getNode(i, *head);
    pedge prev = NULL;
    while(scanf("%d", &i)==1){
        pnode dest = getNode(i, *head);
        scanf("%d", &i);
        prev = new_edge(i,prev,dest);
    }
    here->edges = prev;
}


void insert_node_cmd(pnode *head){
    int i;
    scanf("%d", &i);
    pnode node = getNode(i, *head);
    if (*head == NULL){
        *head = newnode(i, NULL);
        node = *head;
    }
    else if(node != NULL){
        remove_out_edges(node);
    }
    else{
        node = insert_node(i, head);
    }
    pedge prev = NULL;
    while(scanf("%d", &i)==1){
        pnode dest = getNode(i, *head);
        scanf("%d", &i);
        prev = new_edge(i,prev,dest);
    }
    node->edges = prev;
}


void delete_node_cmd(pnode *head){
    int i=0;
    scanf("%d", &i);
    pnode remove = NULL;
    pnode check = *head;
    if (check->node_num == i){
        *head = check->next;
        remove = check;
    }
    else{
        while(check->next){
            if (check->next->node_num == i){
                remove = check->next;
                check->next = remove->next;
                break;
            }
            check= check->next;
        }
    }
    check = *head;
    while(check!=NULL){
        remove_edge_to(i, check);
        check = check->next;
    }
    remove_out_edges(remove);
    free(remove);
}



void printGraph_cmd(pnode head){
    while(head!=NULL){
        printf("node id: %d\n", head->node_num);
        pedge here = head->edges;
        while(here){
            printf("%d -> %d   w: %d\n", head->node_num, here->endpoint->node_num, here->weight);
            here= here->next;
        }
        head = head->next;
    }
}

void swap(int* a, int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void deleteGraph_cmd(pnode* head){
    pnode node = *head;
    while(node!=NULL){
        remove_out_edges(node);
        pnode delete = node;
        node = node->next;
        free(delete);
    }
}
void dijkstra(int *arr,pnode here){
    queuenode* here_queue = newqueueNode(here, 0);
    while (!isEmpty(&here_queue)){
        here = Remove(&here_queue);
        pedge curr_edge = here->edges;
        while(curr_edge!=NULL){
            if (arr[here->seq] + curr_edge->weight < arr[curr_edge->endpoint->seq]){
                arr[curr_edge->endpoint->seq] = arr[here->seq] + curr_edge->weight;
                Insert(&here_queue, curr_edge->endpoint, arr[curr_edge->endpoint->seq]);
            }
            curr_edge= curr_edge->next;
        }
    }
}

void shortsPath_cmd(pnode head){
    int src=0;
    int dest=0;
    while(scanf("%d", &src)==0);
    while(scanf("%d", &dest)==0);
    int src_id;
    int dest_id;
    pnode here;
    pnode curr = head;
    int index=0;
    while (curr!=NULL){
        curr->seq = index;
        if (curr->node_num == src){
            here = curr;
            src_id = index;
        }
        if (curr->node_num == dest){
            dest_id = index;
        }
        index++;
        curr= curr->next;
    }
    int *arr=(int*)malloc(sizeof(int) * index);
    if(arr == NULL)
        exit(0);
    for (int i=0; i < index; i++){
        arr[i] = INT_MAX;
    }
    arr[src_id] = 0;
    dijkstra(arr, here);
    if (arr[dest_id] < INT_MAX){
        printf("Dijsktra shortest path: %d \n", arr[dest_id]);
    }
    else{
        printf("Dijsktra shortest path: -1 \n");
    }
    free(arr);
}



void TSP_cmd(pnode head){
    int j;
    scanf("%d", &j);
    int *cities=(int*)malloc(sizeof(int)*j);
    if(cities == NULL)
        exit(0);
    for(int i=0; i<j; i++){
        scanf("%d", &cities[i]);
    }
    int max = 0;
    pnode here = head;
    while (here){
        here->seq = max;
        max++;
        here= here->next;
    }
    int ans = INT_MAX;
    permutation(cities, 0, j - 1, max, &ans, head);
    if (ans != INT_MAX){
        printf("TSP shortest path: %d \n", ans);
    }
    else{
        printf("TSP shortest path: -1 \n");
    }
    free(cities);
}


void permutation(int* cities, int start, int end, int size_of_nodes, int* ans, pnode head){
    if (start == end){
        int check =0;
        int *p=(int*)malloc(sizeof(int) * size_of_nodes);
        if(p == NULL)
            exit(0);
        for (int i=0;i<size_of_nodes;i++){
            p[i] =  INT_MAX;
        }
        pnode here = getNode(cities[0], head);
        p[here->seq] = 0;
        for (int i=1;i<=end;i++){
            dijkstra(p, here);
            if (p[getNode(cities[i], head)->seq] == INT_MAX){
                free (p);
                return;
            }
            here = getNode(cities[i], head);
            check = check + p[here->seq];
            for (int j=0;j<size_of_nodes;j++){
                p[j] =  INT_MAX;
            }
            p[here->seq] = 0;
        }
        free (p);
        if (check < *ans && check !=0){
            *ans = check;
        }
        return;
    }
    for (int k=start;k<=end;k++){
        swap(cities + k, cities + start);
        permutation(cities, start + 1, end, size_of_nodes, ans, head);
        swap(cities + k, cities + start);
    }
}


int main(){
    char s;
    int k;
    pnode head = NULL;
    int end_of_file = 0;
    while(end_of_file!=EOF){
        end_of_file = scanf("%c", &s);
        switch(s) {
            case 'A':
                deleteGraph_cmd(&head);
                scanf("%d", &k);
                head = generate(k);
                break;
            case 'n':
                build_graph_cmd(&head);
                break;
            case 'B':
                insert_node_cmd(&head);
                break;
            case 'p':
                printGraph_cmd(head);
                break;
            case 'S':
                shortsPath_cmd(head);
                break;
            case 'D':
                delete_node_cmd(&head);
                break;
            case 'T':
                TSP_cmd(head);
                break;
            default:
                break;
        }
    }
    deleteGraph_cmd(&head);
    return 0;
}
