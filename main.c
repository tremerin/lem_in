#include "lem_in.h"

void init_data(t_data *data)
{

    data->names = init_multi_str(6000, 5);
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
    for (size_t i = 0; i < data->n_paths; i++)
    {
        if(data->paths[i].nodes != NULL)
            free(data->paths[i].nodes);
    }
    free(data->paths);
    free_multi_str(data->names);
    if (data->t_adjacency != NULL)
        free_table(data->t_adjacency);    
    if (data->t_weights != NULL)
        free_table(data->t_weights);
    if (data->flow != NULL)
        free_table(data->flow);
    if (data->residual != NULL)
        free_table(data->residual);
}

size_t *paths_len(t_data *data)
{
    size_t * lens = malloc(sizeof(size_t) * data->n_paths);
    size_t i = 0;
    while (i < data->n_paths)
    {
        lens[i] = data->paths[i].len;
        i++;
    }
    return (lens);
}

int main(void)
{
    t_data data;
    init_data(&data);
    printf("init ok\n");
    file_parser(&data);
    printf("parser ok\n");
    //print_table(data.t_adjacency);
    find_paths(&data);
    order_paths(&data);
    size_t *lens = paths_len(&data);
    moving_ants(&data, lens, data.n_paths);
    free(lens);
    free_data(&data);
    return (0);
}