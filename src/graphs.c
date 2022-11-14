#include "../headers/graphs.h"

graph_t *create_graph(int *verticies, int verticies_count)
{
    assert(verticies != NULL);
    assert(verticies_count > 0);

    graph_t *graph = malloc(sizeof(graph_t));
    assert(graph != NULL);

    // set the length
    graph->verticies_count = verticies_count;

    // set the verticies list
    graph->verticies = arrayToList(verticies, verticies_count);

    // set the adjacent matrix
    graph->adjacent_matrix = malloc(verticies_count * sizeof(int *));
    assert(graph->adjacent_matrix != NULL);

    for (int i = 0; i < verticies_count; ++i)
    {
        graph->adjacent_matrix[i] = malloc(verticies_count * sizeof(int));
        assert(graph->adjacent_matrix[i] != NULL);
    }

    return graph;
}

void print_graph(graph_t *graph)
{
    assert(graph != NULL);

    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return;

    printf("@graph->verticies_count = %i\n\n", graph->verticies_count);
    printf("@graph->verticies : [ \n");
    print_list(graph->verticies);
    printf("]\n \n");

    printf("@graph->adjacent_matrix : { \n\n");
    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; j < graph->verticies_count; ++j)
        {
            printf("\t%i", graph->adjacent_matrix[i][j]);
        }
        printf("\n");
    }

    printf("} \n");
}

void init_graph(graph_t **pgraph)
{
    assert(pgraph != NULL);
    assert(*pgraph != NULL);

    graph_t *graph = *pgraph;

    // init the adjacent matrix

    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; i < graph->verticies_count; ++i)
        {
            graph->adjacent_matrix[i][j] = 0;
        }
    }

    return;
}

void destroy_graph(graph_t **pgraph)
{
    assert(pgraph != NULL);
    assert(*pgraph != NULL);

    graph_t *graph = *pgraph;

    if (graph->verticies == NULL && graph->adjacent_matrix == NULL)
    {
        graph = NULL;
        return;
    }

    // destroy the verticies list
    destroy_list(graph->verticies);

    // destroy the adjacend matrix;

    for (int i = 0; i < graph->verticies_count; ++i)
    {
        // free the nested arrays of the matrix
        free(graph->adjacent_matrix[i]);
        graph->adjacent_matrix[i] = NULL;
    }

    // free the outer array of the matrix
    free(graph->adjacent_matrix);
    graph->adjacent_matrix = NULL;

    // free the graph then set graph to null to avoid miss derefrencing
    free(graph);
    graph = NULL;
    return;
}

bool is_rel_reflexiv(graph_t *graph)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    bool resault = true;

    for (int i = 0; i < graph->verticies_count; ++i)
    {
        if (graph->adjacent_matrix[i][i] != 1)
        {
            resault = false;
            break;
        }
    }
    return resault;
}

bool is_rel_symetric(graph_t *graph)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    bool resault = true;

    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; j < graph->verticies_count; ++j)
        {
            if (graph->adjacent_matrix[i][j] == 1 && graph->adjacent_matrix[j][i] != 1)
            {
                resault = false;
                break;
            }
        }
    }
    return resault;
}

bool is_rel_antisymetric(graph_t *graph)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    bool resault = true;

    // store the verticies in an array for index based access
    int *verticies = listToArray(graph->verticies, graph->verticies_count);

    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; j < graph->verticies_count; ++j)
        {
            if (graph->adjacent_matrix[i][j] == 1 && graph->adjacent_matrix[j][i] == 1)
            {
                // get the elements on the i_th and j_th pos
                int fst = verticies[i];
                int snd = verticies[j];

                // check for anti_symetry
                if (fst != snd)
                {
                    resault = false;
                    break;
                }
            }
        }
    }
    free(verticies);
    verticies = NULL;
    return resault;
}

bool is_rel_transitiv(graph_t *graph)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    bool resault = true;

    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; j < graph->verticies_count; ++j)
        {
            for (int k = 0; k < graph->verticies_count; ++k)
            {
                if (graph->adjacent_matrix[i][j] == 1 && graph->adjacent_matrix[j][k] == 1)
                {
                    if (graph->adjacent_matrix[i][k] != 1)
                    {
                        resault = false;
                        break;
                    }
                }
            }
        }
    }
    return resault;
}

graph_t *get_reflexiv_clojure(graph_t *graph)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    // set the resault lenght and the verticies equal to the initial graph.
    int *verticies = listToArray(graph->verticies, graph->verticies_count);
    assert(verticies != NULL);

    graph_t *resault = create_graph(verticies, graph->verticies_count);
    assert(resault != NULL);

    free(verticies);
    verticies = NULL;

    // copy all the relationships, and make it reflexive
    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; j < graph->verticies_count; ++j)
        {
            if (i == j)
            {
                resault->adjacent_matrix[i][j] = 1;
                continue;
            }
            resault->adjacent_matrix[i][j] = graph->adjacent_matrix[i][j];
        }
    }

    return resault;
}

graph_t *get_symetric_clojure(graph_t *graph)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    // set the resault lenght and the verticies equal to the initial graph.
    int *verticies = listToArray(graph->verticies, graph->verticies_count);
    assert(verticies != NULL);

    graph_t *resault = create_graph(verticies, graph->verticies_count);
    assert(resault != NULL);

    free(verticies);
    verticies = NULL;

    // copy all the relationships, and make it symetric
    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; j < graph->verticies_count; ++j)
        {
            resault->adjacent_matrix[i][j] = graph->adjacent_matrix[i][j];

            if (resault->adjacent_matrix[i][j] == 1)
            {
                resault->adjacent_matrix[j][i] = 1;
            }
        }
    }

    return resault;
}

graph_t *get_transitiv_clojure(graph_t *graph)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    // set the resault lenght and the verticies equal to the initial graph.
    int *verticies = listToArray(graph->verticies, graph->verticies_count);
    assert(verticies != NULL);

    graph_t *resault = create_graph(verticies, graph->verticies_count);
    assert(resault != NULL);

    free(verticies);
    verticies = NULL;

    // copy all the relationships, and make it symetric
    for (int i = 0; i < graph->verticies_count; ++i)
    {
        for (int j = 0; j < graph->verticies_count; ++j)
        {
            resault->adjacent_matrix[i][j] = graph->adjacent_matrix[i][j];

            for (int k = 0; k < graph->verticies_count; ++k)
            {
                if (graph->adjacent_matrix[i][j] == 1 && graph->adjacent_matrix[j][k] == 1)
                {
                    resault->adjacent_matrix[i][k] = 1;
                }
            }
        }
    }

    return resault;
}

graph_t *get_reflexiv_reduction(graph_t *graph);
graph_t *get_symetric_reduction(graph_t *graph);
graph_t *get_antisymetric_reduction(graph_t *graph);
graph_t *get_transitiv_reduction(graph_t *graph);

void add_relationship(graph_t **pgraph, int fst, int snd)
{
    assert(pgraph != NULL);
    assert(*pgraph != NULL);

    graph_t *graph = *pgraph;

    int *verticies = listToArray(graph->verticies, graph->verticies_count);

    int fst_index = binary_search_array(verticies, 0, graph->verticies_count - 1, fst);
    int snd_index = binary_search_array(verticies, 0, graph->verticies_count - 1, snd);

    // make sure the fst and snd are both valid vertiices;
    assert(fst_index != -1);
    assert(snd_index != -1);

    // add relationship via the adjacent matrix;
    graph->adjacent_matrix[fst_index][snd_index] = 1;

    free(verticies);
}

list_t *find_relationships(graph_t *graph, int vertex)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return NULL;

    // make sure that the vertex is on the graph;
    int *verticies = listToArray(graph->verticies, graph->verticies_count);

    int vertex_index = binary_search_array(verticies, 0, graph->verticies_count - 1, vertex);
    assert(vertex_index != -1);

    // setup the resault list of all the verticies with which vertex is in relation;

    // fisrt start with the vertex then remove it at the end
    list_t *resault = create_node_list(vertex);

    for (int j = 0; j < graph->verticies_count; ++j)
    {
        if (graph->adjacent_matrix[vertex_index][j] == 1)
        {
            resault = push_list(resault, verticies[j]);
        }
    }

    free(verticies);
    verticies = NULL;

    // remove the vertex for clean output;
    resault = shift_list(resault);
    return resault;
}

list_t *find_path(graph_t *graph, int origin, int dest)
{
    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return NULL;

    list_t *already_seen_verticies = create_node_list(-1);

    list_t *path = find_path_proc(graph, origin, dest, &already_seen_verticies);

    destroy_list(already_seen_verticies);

    // remove all the occurences;
    list_t *resault = create_node_list(origin);

    int path_length = get_length_list(path);

    int *path_as_array = listToArray(path, path_length);

    for (int i = 1; i < path_length; ++i)
    {
        int resault_length = get_length_list(resault);
        int *resault_as_array = listToArray(resault, resault_length);

        // only push if it is not already on the resault, liniar search way since array is not sorted
        if (liniar_search_array(resault_as_array, resault_length, path_as_array[i]) == -1)
        {
            resault = push_list(resault, path_as_array[i]);
        }

        free(resault_as_array);
    }

    free(path_as_array);
    destroy_list(path);

    return resault;
}

list_t *find_path_proc(graph_t *graph, int origin, int dest, list_t **palready_seen_verticies)
{
    assert(graph != NULL);

    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return NULL;

    list_t *already_seen_verticies = *palready_seen_verticies;

    // base case zero

    if (dest == origin)
    {
        list_t *res = create_node_list(origin);

        return res;
    }

    // get all the relationships of origin
    list_t *current_relations = find_relationships(graph, origin);

    // transforme to array to check if dest is one of them or not
    int relation_list_length = get_length_list(current_relations);

    // base case one:  dest is unreachable
    if (relation_list_length < 1)
    {
        if (current_relations != NULL)
        {
            destroy_list(current_relations);
            current_relations = NULL;
        }

        return NULL;
    }

    int *current_relations_arr = listToArray(current_relations, relation_list_length);
    int index = liniar_search_array(current_relations_arr, relation_list_length, dest); // linair search, can be unsorted

    // base case two; dest is reached
    if (index != -1)
    {
        if (current_relations != NULL)
        {
            destroy_list(current_relations);
            current_relations = NULL;
        }

        if (current_relations_arr != NULL)
        {
            free(current_relations_arr);
            current_relations_arr = NULL;
        }

        // create a list of type [current,dest]
        list_t *res = create_node_list(origin);
        res = push_list(res, dest);

        return res;
    }

    // base case three: origin is already seen
    int already_seen_verticies_list_length = get_length_list(already_seen_verticies);
    int *already_seen_verticies_arr = listToArray(already_seen_verticies, already_seen_verticies_list_length);

    // linair search the array, since it can be unsorted in one of the recursive calls
    if (liniar_search_array(already_seen_verticies_arr, already_seen_verticies_list_length, origin) != -1)
    {

        if (current_relations != NULL)
        {
            destroy_list(current_relations);
            current_relations = NULL;
        }

        if (current_relations_arr != NULL)
        {
            free(current_relations_arr);
            current_relations_arr = NULL;
        }

        if (already_seen_verticies_arr != NULL)
        {
            free(already_seen_verticies_arr);
            already_seen_verticies_arr = NULL;
        }

        return NULL;
    }

    // // recursive case

    // create a resault list
    list_t *path = create_node_list(origin);
    int path_length = get_length_list(path);
    int *path_as_array = listToArray(path, path_length);

    already_seen_verticies = push_list(already_seen_verticies, origin);

    for (int i = 0; i < relation_list_length; ++i)
    {
        if (already_seen_verticies_arr != NULL)
        {
            free(already_seen_verticies_arr);
            already_seen_verticies_arr = NULL;
        }

        if (current_relations != NULL)
        {
            destroy_list(current_relations);
            current_relations = NULL;
        }

        path = concat_list(path, find_path_proc(graph, current_relations_arr[i], dest, palready_seen_verticies));

        // check if path contains the dest;
        path_length = get_length_list(path);

        if (path_as_array != NULL)
        {
            free(path_as_array);
            path_as_array = NULL;
        }

        path_as_array = listToArray(path, path_length);

        // linair search the array, since it can be unsorted.
        if (liniar_search_array(path_as_array, path_length, dest) != -1)
        {
            if (current_relations != NULL)
            {
                destroy_list(current_relations);
                current_relations = NULL;
            }

            if (already_seen_verticies_arr != NULL)
            {
                free(already_seen_verticies_arr);
                already_seen_verticies_arr = NULL;
            }

            if (current_relations_arr != NULL)
            {
                free(current_relations_arr);
                current_relations_arr = NULL;
            }

            if (path_as_array != NULL)
            {
                free(path_as_array);
                path_as_array = NULL;
            }

            break;
        }
    }

    return path;
}

/*

graph_t *get_antisymetric_clojure(graph_t *graph)
{

    assert(graph != NULL);
    if (graph->verticies_count == 0 || graph->adjacent_matrix == NULL || graph->verticies == NULL)
        return false;

    // set the resault lenght and the verticies equal to the initial graph.
    graph_t *resault = create_graph(listToArray(graph->verticies, graph->verticies_count), graph->verticies_count);
    assert(resault != NULL);

    // copy all the relationships, and make it antisymetric
    int *verticies;

    for (int counter = 0; counter < graph->verticies_count; ++counter)
    {
        verticies = listToArray(graph->verticies, graph->verticies_count);
        assert(verticies != NULL);

        for (int i = 0; i < graph->verticies_count; ++i)
        {
            for (int j = 0; j < graph->verticies_count; ++j)
            {
                resault->adjacent_matrix[i][j] = graph->adjacent_matrix[i][j];

                if (graph->adjacent_matrix[i][j] == 1 && graph->adjacent_matrix[j][i] == 1)
                {
                    // find the verticies
                    int fst = verticies[i];
                    int snd = verticies[j];


                    // make them the same , but there is two values !
                    // which one will we overrride ?

                }
            }
        }

        free(verticies);
        verticies = NULL;
    }

    return resault;
}


*/