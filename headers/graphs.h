#include "./arrays.h"
#include "./singleLinkedLists.h"

struct graph
{
    list_t *verticies;
    int verticies_count;
    int **adjacent_matrix;
};

typedef struct graph graph_t;

/** CRUD */

graph_t *create_graph(int *verticies, int verticies_count);
void print_graph(graph_t *graph);
void init_graph(graph_t **pgraph);
void destroy_graph(graph_t **pgraph);
void add_relationship(graph_t **pgraph, int fst, int snd);
list_t *find_relationships(graph_t *graph, int vertex);

/** ADVANCED */

list_t *find_path(graph_t *graph, int origin, int dest);
list_t *find_path_proc(graph_t *graph, int origin, int dest, list_t **palready_seen_verticies);


/** ALGEBRA */

bool is_rel_reflexiv(graph_t *graph);
bool is_rel_symetric(graph_t *graph);
bool is_rel_antisymetric(graph_t *graph);
bool is_rel_transitiv(graph_t *graph);


graph_t *get_reflexiv_clojure(graph_t *graph);
graph_t *get_symetric_clojure(graph_t *graph);
graph_t *get_antisymetric_clojure(graph_t *graph);
graph_t *get_transitiv_clojure(graph_t *graph);



graph_t *get_reflexiv_reduction(graph_t *graph);
graph_t *get_symetric_reduction(graph_t *graph);
graph_t *get_antisymetric_reduction(graph_t *graph);
graph_t *get_transitiv_reduction(graph_t *graph);
