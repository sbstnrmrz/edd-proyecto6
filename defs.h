#ifndef DEFS_H
#define DEFS_H

#include <iostream>

#if __WIN32
#define CLEAR system("cls")
#define SLEEP(secs) {                                        \
    char buf[32] = {0};                                      \
    sprintf(buf, "timeout /t %d /nobreak > nul", (int)secs); \
    system(buf);                                             \
}
#define DELETE_FILE(file) {            \
    char str[32] = {0};                \
    snprintf(str, 32, "del %s", file); \
    system(str);                       \
}
#elif __APPLE__ || unix
#define CLEAR system("clear")
#define SLEEP(secs) {                    \
    char str[32] = {0};                  \
    snprintf(str, 32, "sleep %f", secs); \
    system(str);                         \
}
#define DELETE_FILE(file) {           \
    char str[32] = {0};               \
    snprintf(str, 32, "rm %s", file); \
    system(str);                      \
}
#endif

#define WIN_W 1280
#define WIN_H 720

#define CHECK_RANGE(in, r1, r2) (in > r1 && in < r2) ? true : false
#define CHAR2INT(x) x - '0'
#define INT2CHAR(x) x + '0'
#define ARRAY_LEN(x) sizeof(x)/sizeof(x[0])

typedef struct {
    std::vector<std::vector<int> > mat;
    std::vector<char> ids;
} graph_t;

int graph_add_node(graph_t *graph, char node_id);
int graph_add_edge(graph_t *graph, char src_node_id, char dst_node_id);
int graph_delete_node(graph_t *graph, char node_id);
int graph_delete_edge(graph_t *graph, char src_node_id, char dst_node_id);
bool graph_check_node(graph_t graph, char node_id);
bool graph_check_edge(graph_t *graph, char src_node_id, char dst_node_id);
int graph_get_node_index(graph_t graph, char node_id);
void graph_print_adjacency_mat(graph_t graph);
void graph_print_nodes(graph_t graph);

#endif
