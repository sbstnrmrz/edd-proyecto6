#include "defs.h"

int graph_add_node(graph_t *graph, char node_id) {
    for (int i = 0; i < graph->ids.size(); i++) {
        if (graph->ids[i] == node_id) {
            printf("node %c: already exists!\n", node_id);
            return -1;
        }
    }
    graph->ids.push_back(node_id);

    std::vector<int> vec;
    for (int i = 0; i < graph->ids.size(); i++) {
        vec.push_back(0);
    }
    graph->mat.push_back(vec); 
    for (int i = 0; i < graph->ids.size()-1; i++) {
        graph->mat[i].resize(graph->ids.size());
    }
    
    return 0;
}

int graph_add_edge(graph_t *graph, char src_node_id, char dst_node_id) {
    if (graph->mat.size() < 1) {
        printf("graph is empty!\n");
        return -1;
    }

    if (!graph_check_node(*graph, src_node_id)) {
        printf("source node %c: doesnt exists!\n", src_node_id);
        return -1;
    }
    if (!graph_check_node(*graph, dst_node_id)) {
        printf("destination node %c: doesnt exists!\n", dst_node_id);
        return -1;
    }
    if (graph_check_edge(graph, src_node_id, dst_node_id)) {
        printf("edge %c -> %c already exists!\n", src_node_id, dst_node_id);
    }

    int src_index = graph_get_node_index(*graph, src_node_id); 
    int dst_index = graph_get_node_index(*graph, dst_node_id); 
    graph->mat[src_index][dst_index] = 1; 
    return 0;
}

int graph_delete_node(graph_t *graph, char node_id) {
    if (graph->mat.size() < 1) {
        printf("graph is empty!\n");
        return -1;
    }

    if (!graph_check_node(*graph, node_id)) {
        printf("node %c doesnt exists!\n", node_id);
        return -1;
    }

    for (int i = 0; i < graph->ids.size(); i++) {
        if (graph->ids[i] == node_id) {
            graph->ids.erase(graph->ids.begin()+i);
            for (int j = 0; j < graph->mat.size(); j++) {
                graph->mat[j].erase(graph->mat[j].begin()+i);
            }
            graph->mat.erase(graph->mat.begin()+i);
            return 0;
        }
    }
    
    return -1; 
}

int graph_delete_edge(graph_t *graph, char src_node_id, char dst_node_id) {
    if (graph->mat.size() < 1) {
        printf("graph is empty!\n");
        return -1;
    }

    if (!graph_check_node(*graph, src_node_id)) {
        printf("source node %c: doesnt exists!\n", src_node_id);
        return -1;
    }
    if (!graph_check_node(*graph, dst_node_id)) {
        printf("destination node %c: doesnt exists!\n", dst_node_id);
        return -1;
    }

    if (graph_check_edge(graph, src_node_id, dst_node_id)) {
        int src_index = graph_get_node_index(*graph, src_node_id); 
        int dst_index = graph_get_node_index(*graph, dst_node_id); 
        graph->mat[src_index][dst_index] = 0;
        return 0;
    }
    
    printf("edge %c -> %c: doesnt exist!\n", src_node_id, dst_node_id);
    return -1; 
}

int graph_get_node_index(graph_t graph, char node_id) {
    if (graph.mat.size() < 1) {
        printf("graph is empty!\n");
        return -1;
    }
    if (!graph_check_node(graph, node_id)) {
        printf("node %c doesnt exists!\n", node_id);
        return -1;
    }

    for (int i = 0; i < graph.ids.size(); i++) {
        if (graph.ids[i] == node_id) {
            return i;
        }
    }
    
    return -1;
}

bool graph_check_node(graph_t graph, char node_id) {
    if (graph.mat.size() < 1) {
        printf("graph is empty!\n");
        return false;
    }

    for (int i = 0; i < graph.ids.size(); i++) {
        if (graph.ids[i] == node_id) {
            return true; 
        }
    }

    return false;
}

bool graph_check_edge(graph_t *graph, char src_node_id, char dst_node_id) {
    if (graph->mat.size() < 1) {
        printf("graph is empty!\n");
        return false;
    }

    int src_index = graph_get_node_index(*graph, src_node_id); 
    int dst_index = graph_get_node_index(*graph, dst_node_id); 
    if (graph->mat[src_index][dst_index] == 1) {
        return true;
    }

    return false;
}

void graph_print_nodes(graph_t graph) {
    if (graph.mat.size() < 1) {
        printf("graph is empty!\n");
        return;
    }

    printf("Nodes info:\n");
    for (int i = 0; i < graph.mat.size(); i++) {
        printf("%c -> ", graph.ids[i]);
        for (int j = 0; j < graph.mat[i].size(); j++) {
            if (graph.mat[i][j] == 1) {
                printf("%c, ", graph.ids[j]);
            } 
        }
        printf("\n");
    }
}

void graph_print_adjacency_mat(graph_t graph) {
    printf("matrix size: %zux%zu\n ", graph.mat.size(), graph.mat[0].size());
    for (int i = 0; i < graph.mat.size(); i++) {
        printf(" %c", graph.ids[i]);
    }
    printf("\n");
    for (int i = 0; i < graph.mat.size(); i++) {
        printf("%c ", graph.ids[i]);
        for (int j = 0; j < graph.mat.at(i).size(); j++) {
            printf("%d ", graph.mat[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    graph_t graph;
    graph_add_node(&graph, 'A');
    graph_add_node(&graph, 'B');
    graph_add_node(&graph, 'C');
    graph_add_edge(&graph, 'A', 'B');
    graph_add_edge(&graph, 'B', 'A');
    graph_add_edge(&graph, 'B', 'B');
    graph_add_edge(&graph, 'B', 'B');
    graph_add_edge(&graph, 'B', 'B');
    graph_add_edge(&graph, 'A', 'B');
    graph_add_edge(&graph, 'A', 'C');

    graph_print_adjacency_mat(graph);
    graph_delete_node(&graph, 'B');
    printf("\n");
    graph_print_adjacency_mat(graph);
    graph_add_node(&graph, 'B');
    graph_print_adjacency_mat(graph);
    graph_print_nodes(graph);

    return 0;
}
