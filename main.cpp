#include "defs.h"

struct _node {
    void *data;
    struct _node *next;
    struct _node *prev;
};

typedef struct _node node_t;

typedef struct {
    node_t *head;
    size_t size;
    size_t data_size;
} llist;

typedef struct {
    node_t *src;
    node_t *dst;
    int weight;
} edge_t;

typedef struct {
    std::vector<std::vector<char>> arr;
    std::vector<llist>  nodes;
    std::vector<edge_t> edges;
} graph_t;

llist init_llist(size_t data_size) {
//  llist *list = (llist*)malloc(sizeof(llist));
//  list->head = (node_t*)malloc(sizeof(node_t));
//  list->head->data = NULL;
//  list->head->prev = NULL;
//  list->head->next = NULL;
//  list->size = 0;
//  list->data_size = data_size;

    llist list = {0};
    list.head = new node_t;
    list.head->data = NULL;
    list.head->prev = NULL;
    list.head->next = NULL;
    list.size = 0;
    list.data_size = data_size;

    return list; 
}

int llist_push(llist *list, void *data) {
    node_t *node = list->head;
    node_t *prev_node = NULL;

    if (node->data == NULL) {
        node->data = data;
        list->size++;
        printf("mallocd: %p = %c\n", node->data, *(char*)node->data);
        return 0;
    }

    prev_node = node;
    while (node->next != NULL) {
        prev_node = node;
        node = node->next; 
    }
     
    node->next = new node_t;
    node->next->data = data;
    node->next->prev = node;
    node->next->next = NULL;
    list->size++;
    printf("mallocd: %p = %c\n", node->next, *(char*)node->next->data);

    return 0;
}

int llist_pop(llist *list) {
    if (list->size < 1 || list == NULL) {
        printf("there are no elements in the list\n");
        return -1;
    }

    if (list->size < 2) {
        free(list->head->data);
        list->head->data = NULL;
        list->size--;
        return 0;
    }

    node_t *node = list->head;
    while (node->next != NULL) {
        node = node->next; 
    }

    node->prev->next = NULL;
    free(node);
    list->size--;

    return 0;
}

int llist_insert(llist *list, void *data, int index) {
    if (index < 0 || index > list->size) {
        printf("index %d: out of bounds\n", index);
        return -1;
    }

    node_t *node = list->head;
    for (int i = 0; i < index-1; i++) {
        node = node->next; 
    }

    node_t *new_node = new node_t;
    new_node->data = data;

    new_node->next = node->next;
    node->next = new_node;
    new_node->prev = node;
    list->size++;

    return 0;
}

int llist_delete(llist *list, int index) {  
    if (index < 0 || index >= list->size) {
        printf("index %d: out of bounds\n", index);
        return -1;
    }

    node_t *node = list->head;
    for (int i = 0; i < index-1; i++) {
        node = node->next;
    }
    
    if (index == 0) {
        node->next->prev = NULL;
        list->head = node->next;
        free(node);
        list->size--;
        return 0;
    }
    if (index == list->size-1) {
        free(node->next);
        node->next = NULL;
        list->size--;
        return 0;
    }

    node_t *aux = node->next;
    node->next = node->next->next;
    node->next->prev = node;
    printf("deleting node %d: %p\n", index, node->next);

    list->size--;
    return 0;
}

void *llist_get(llist list, int index) {
    if (index < 0 || index >= list.size) {
        printf("index %d: out of bounds\n", index);
        return NULL;
    }

    node_t *node = list.head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node->data;
}

node_t *llist_get_node(llist list, int index) {
    if (index < 0 || index >= list.size) {
        printf("index %d: out of bounds\n", index);
        return NULL;
    }

    node_t *node = list.head;
    for (int i = 0; i < index; i++) {
        node = node->next;
    }

    return node;
}

void llist_print(llist list) {
    if (list.size < 1) {
        printf("list doesnt have elements\n");
        return;
    }
    node_t *node = list.head;
    for (int i = 0; i < list.size-1; i++) {
        node = node->next;
        if (node->prev != NULL) {
//          printf("[%p] =  -> [%p] =  -> [%p] = \n", node->prev, *(int*)(node->prev->data), 
//                                                          node, *(int*)node->data, 
//                                                          node->next, *(int*)node->next->data);
            printf("[%p] = %d -> [%p] = %d -> [%p] = %d\n", node->prev, *(int*)node->prev->data,
                                                            node, *(int*)node->data,
                                                            node->next, node->next == NULL ? -1 : *(int*)node->next->data);
        }
    }
    printf("\n");
}

//int graph_add_node(graph_t *graph, char src, char new_node, int weight) {
//    if (graph->node_list_size < 1) {
//        printf("graph is empty!\n");
//        return -1;
//    }
//
//    for (int i = 0; i < graph->node_list_size; i++) {
//        if (*(char*)graph->node_list[i].head->data == src) {
//            llist_push(&graph->node_list[i], &new_node);
//            return 0;
//        }
//    }
//
//    printf("node %c: doesnt exist!\n", src);
//    return -1;
//}

graph_t *init_graph() {
    graph_t *graph = new graph_t; 

//    graph->nodes.at(0) = init_llist(sizeof(char)); 
    char *c = new char; 
    *c = 'A';
    printf("%c\n", *c);

    llist list = init_llist(sizeof(char));
    llist_push(&list, c);
    graph->nodes.push_back(list);

    return graph;
}

int graph_add_node(graph_t *graph, char node_id) {
    if (graph->nodes.size() < 1) {
        printf("graph is empty!\n");
        return -1;
    }

    for (int i = 0; i < graph->nodes.size(); i++) {
        if (*(char*)graph->nodes.at(i).head->data == node_id) {
            printf("node %c: already exists!\n", node_id); 
            return -1;
        }
    }

    char *c = new char;
    *c = node_id;
//  graph->nodes = (llist*)realloc(graph->node_list, sizeof(llist) * (graph->node_list_size+1));
//  if (graph->node_list == NULL) {
//      printf("error adding node!\n");
//      exit(1);
//  }
    
    llist list = init_llist(sizeof(char));
    llist_push(&list, c);
    graph->nodes.push_back(list);

    return 0;
}

node_t *graph_get_node(graph_t graph, char target) {
    for (int i = 0; i < graph.nodes.size(); i++) {
        if (*(char*)graph.nodes.at(i).head->data == target) {
            return graph.nodes.at(i).head;
        }
    }
    return NULL;
}

int graph_add_edge(graph_t *graph, char src, char dst, int weight) {
    edge_t edge = {0}; 
    edge.src = graph_get_node(*graph, src);
    if (edge.src == NULL) {
        printf("Source node: '%c' doesnt exist\n", src);
        exit(1);
    }
    edge.dst = graph_get_node(*graph, dst);
    if (edge.dst == NULL) {
        printf("Destination node: '%c' doesnt exist\n", dst);
        exit(1);
    }

    edge.weight = weight;
    printf("src: %c | dst: %c\n", *(char*)edge.src->data, *(char*)edge.dst->data);
    graph->edges.push_back(edge);

    for (int i = 0; i < graph->nodes.size(); i++) {
        printf("cmp: %c == %c\n", *(char*)graph->nodes.at(i).head->data, *(char*)edge.src->data);
        if (*(char*)graph->nodes.at(i).head->data == *(char*)edge.src->data) {
            llist_push(&graph->nodes.at(i), edge.dst->data); 
            break;
        }
    }

    return 0;
}

void graph_delete_node(graph_t *graph, const char node_id) {
    for (int i = 0; i < graph->nodes.size(); i++) {
        if (*(char*)graph->nodes.at(i).head->data == node_id) {
            graph->nodes.erase(graph->nodes.begin()+i); 
            for (int j = 0; j < graph->nodes.size(); j++) {
                node_t *node = graph->nodes.at(j).head;
                int ind = 0;
                while (node != NULL) {
                    if (*(char*)node->data == node_id) {
                        llist_delete(graph->nodes.at(j), ind); 

                    }
                    node = node->next;
                    ind++;
                }
            } 
        }

    }
}

void graph_print_nodes(graph_t graph) {
    if (graph.nodes.size() < 1) {
        printf("graph is empty!");
        return;
    }

    printf("Nodes, size %zu:\n", graph.nodes.size());
    for (int i = 0; i < graph.nodes.size(); i++) {
        node_t *node = graph.nodes.at(i).head;
        printf("[%p] = %c -> ", node, *(char*)node->data);
        node = node->next;
        while (node != NULL) {
            printf("%c, ", *(char*)node->data);
            node = node->next;
        }
        printf("\n");
    } 
}

void print_mat(int **arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    graph_t *graph = init_graph();
    printf("asd\n");
//  llist list = init_llist(sizeof(char));
//  char c = 'a';
//  llist_push(&list, &c);
//  llist_print(list);
//  printf("%c\n", *(char*)graph->node_list[0].head->data);

//  for (int i = 0; i < 10; i++) {
//      int *x = new int;
//      *x = i;
//      llist_push(&list, x);
//  }
//  llist_print(list);

    
    graph_add_node(graph, 'D');

    graph_add_node(graph, 'H');
    graph_add_node(graph, 'T');
    graph_add_node(graph, 'R');

    graph_add_edge(graph, 'A', 'T', 5);
    graph_add_edge(graph, 'A', 'R', 10);
    graph_add_edge(graph, 'R', 'A', 15);
    graph_print_nodes(*graph);

    return 0;
}
