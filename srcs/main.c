#include "../include/lem_in.h"

void init_data(t_data *data)
{

    data->names = init_multi_str(6000, 5);
    if (!data->names)
    {
        perror("Error: malloc");
        exit(EXIT_FAILURE);
    }
    data->t_adjacency = NULL;
    data->flags.print_map = 0;
    data->flags.print_paths = 0;
}

void free_data(t_data *data)
{
    for (size_t i = 0; i < data->paths.num_paths; i++)
    {
        if(data->paths.paths[i].nodes != NULL)
            free(data->paths.paths[i].nodes);
    }
    free(data->paths.paths);
    if (data->n_algo == 1)
    {
        for (size_t i = 0; i < data->ff_paths.n_paths; i++)
        {
            if(data->ff_paths.paths[i].nodes != NULL)
                free(data->ff_paths.paths[i].nodes);
        }
        free(data->ff_paths.paths);
        if (data->ff_flow != NULL)
             free_table(data->ff_flow);
        if (data->ff_residual != NULL)
            free_table(data->ff_residual);
    }
    free_multi_str(data->names);
    if (data->t_adjacency != NULL)
        free_table(data->t_adjacency);    
    if (data->residual != NULL)
        free_table(data->residual);
}

size_t *paths_len(t_data *data)
{
    size_t * lens = malloc(sizeof(size_t) * data->paths.num_paths);
    size_t i = 0;
    while (i < data->paths.num_paths)
    {
        lens[i] = data->paths.paths[i].len;
        i++;
    }
    return (lens);
}


size_t *ff_paths_len(t_data *data)
{
    size_t * lens = malloc(sizeof(size_t) * data->ff_paths.n_paths);
    size_t i = 0;
    while (i < data->ff_paths.n_paths)
    {
        lens[i] = data->ff_paths.paths[i].len;
        i++;
    }
    return (lens);
}


void flags(t_data *data, int argc, char **argv)
{
    int i = 1;
    while (i < argc)
    {
        if (ft_strlen(argv[i]) == 2 && ft_strncmp(argv[i], "-m", 2) == 0)
        {
            data->flags.print_map = 1;
        }
        else if (ft_strlen(argv[i]) == 2 && ft_strncmp(argv[i], "-p", 2) == 0)
        {
            data->flags.print_paths = 1;
        }
        else if (ft_strlen(argv[i]) == 2 && ft_strncmp(argv[i], "-h", 2) == 0)
        {
            printf("Usage: %s [-p] [-m] < input_file\n", argv[0]);
            printf("  -p    Show paths used\n");
            printf("  -m    Don't print map\n");
            exit(0);
        }
        else
        {
            printf("Flag %s is invalid. Run -h to know how to run this program\n", argv[i]);
            exit(0);
        }
        i++;
    }
}


int main(int argc, char **argv)
{
    t_data data;
    init_data(&data);
    if (argc > 1)
    {
        flags(&data, argc, argv);
    }
    file_parser(&data);
    find_paths(&data);
    order_paths(data.paths.num_paths, data.paths.paths);
    size_t *lens = paths_len(&data);
    size_t lines = num_lines(data.ants, lens, data.paths.num_paths);
    if (data.table_size < 1500)
    {
        order_paths(data.ff_paths.n_paths, data.ff_paths.paths);
        size_t *ff_lens = ff_paths_len(&data);
        size_t ff_lines = num_lines(data.ants, ff_lens, data.ff_paths.n_paths);
        if (lines < ff_lines)
        {
            data.n_algo = 0;
            moving_ants(&data, lens, data.paths.num_paths, lines);
        }
        else
        {
            data.n_algo = 1;
            moving_ants(&data, ff_lens, data.ff_paths.n_paths, ff_lines);
        }
        free(ff_lens);
    }
    else
    {
        data.n_algo = 0;
        moving_ants(&data, lens, data.paths.num_paths, lines);
    }
    free(lens);
    free_data(&data);
    return (0);
}