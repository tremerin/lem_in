#include "lem_in.h"

void init_data(t_data *data)
{

    data->names = init_multi_str(4000, 5);
    if (!data->names)
    {
        perror("Error: malloc");
        exit(EXIT_FAILURE);
    }
    data->t_adjacency = NULL;
    data->t_weights = NULL;
}

void free_data(t_data *data)
{
    free_multi_str(data->names);
    if (data->t_adjacency != NULL)
        free_table(data->t_adjacency);    
    if (data->t_weights != NULL)
        free_table(data->t_weights);
}

int main(void)
{
    t_data data;
    init_data(&data);
    printf("init ok\n");
    file_parser(&data);
    printf("parser ok\n");
    //print_table(data.t_adjacency);
    init_distances(&data);
    assign_distance(data.t_adjacency, data.dist_start, data.p_start, data.p_end);
    assign_distance(data.t_adjacency, data.dist_end, data.p_end, data.p_start);
    printf("distances ok\n");
    //print_distances(&data);
    weight_table(&data);
    //print_table(data.t_weights);
    assing_multiplier(&data);
    //print_multipliers(data);
    printf("multipliers ok\n");
    number_of_paths(&data);
    printf("paths: %ld\n", data.n_paths);
    path_finding(&data);
    data.paths_index = malloc(sizeof(size_t) * 2);
    data.paths_index[0] = 0;
    data.paths_index[1] = 2;
    size_t *paths_len = malloc(sizeof(size_t) * 2);
    paths_len[0] = 5;
    paths_len[1] = 5;
    printf("\n");
    moving_ants(&data, paths_len, 2);
    free_data(&data);
    return (0);
}