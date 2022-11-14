#include "../headers/main.h"

int main(void)
{
    int verticies[] = {1, 7, 5, 3};
    int verticies_count = 4;

    // sort the verticies
    binary_insertion_sort_array(verticies, verticies_count);

    graph_t *graph = create_graph(verticies, verticies_count);
    init_graph(&graph);

    print_graph(graph);

    printf("is_rel_reflexiv ? %s\n", is_rel_reflexiv(graph) ? "yes" : "no");
    printf("is_rel_symetric ? %s\n", is_rel_symetric(graph) ? "yes" : "no");
    printf("is_rel_antisymetric ? %s\n", is_rel_antisymetric(graph) ? "yes" : "no");
    printf("is_rel_transitiv ? %s\n", is_rel_transitiv(graph) ? "yes" : "no");

    printf("------------------------\n\n");
    add_relationship(&graph, 1, 1);
    add_relationship(&graph, 3, 3);
    add_relationship(&graph, 3, 5);
    add_relationship(&graph, 1, 5);
    add_relationship(&graph, 7, 7);
    add_relationship(&graph, 1, 7);
    add_relationship(&graph, 7, 1);
    add_relationship(&graph, 7, 3);

    printf("is_rel_reflexiv ? %s\n", is_rel_reflexiv(graph) ? "yes" : "no");
    printf("is_rel_symetric ? %s\n", is_rel_symetric(graph) ? "yes" : "no");
    printf("is_rel_antisymetric ? %s\n", is_rel_antisymetric(graph) ? "yes" : "no");
    printf("is_rel_transitiv ? %s\n", is_rel_transitiv(graph) ? "yes" : "no");

    printf("------------------------\n\n");
    print_graph(graph);
    printf("------------------------\n\n");

    /* all the getter for the clojures allocates space, so do not forget to free  */

    // graph_t * new_graph = get_reflexiv_clojure(graph);

    // graph_t *new_graph = get_symetric_clojure(graph);

    // graph_t *new_graph = get_transitiv_clojure(graph);

    // print_graph(new_graph);

    // printf("is_rel_reflexiv ? %s\n", is_rel_reflexiv(new_graph) ? "yes" : "no");
    // printf("is_rel_symetric ? %s\n", is_rel_symetric(new_graph) ? "yes" : "no");
    // printf("is_rel_antisymetric ? %s\n", is_rel_antisymetric(new_graph) ? "yes" : "no");
    // printf("is_rel_transitiv ? %s\n", is_rel_transitiv(new_graph) ? "yes" : "no");

    // destroy_graph(&new_graph);

    // // // Relationship finding
    // list_t* relations = find_relationships(graph, 1);
    // print_list(relations);
    // destroy_list(relations);

    // path finding

    list_t *path = find_path(graph, 1, 3);
    print_list(path);
    destroy_list(path);

    printf("------------------------\n\n");

    path = find_path(graph, 1, 1);
    print_list(path);
    destroy_list(path);

    printf("------------------------\n\n");

    path = find_path(graph, 1, 5);
    print_list(path);
    destroy_list(path);

    printf("------------------------\n\n");

    path = find_path(graph, 5, 1);
    print_list(path);
    destroy_list(path);

    printf("------------------------\n\n");

    path = find_path(graph, 7, 3);
    print_list(path);
    destroy_list(path);

    printf("------------------------\n\n");

    destroy_graph(&graph);

    return 0;
}