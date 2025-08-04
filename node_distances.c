#include "lem_in.h"

void    init_distances(t_data *data)
{
    size_t i = 0;
    data->dist_start = malloc(sizeof(unsigned int) * data->table_size);
    data->dist_end = malloc(sizeof(unsigned int) * data->table_size);
    while (i < data->table_size)
    {
        data->dist_start[i] = -1;
        data->dist_end[i] = -1;
        i++;
    }
}

void    assign_distance(t_table *table, short int *distances, unsigned short p_init, unsigned short p_end)
{
    distances[p_init] = 0;
    size_t  checks = 0;
    size_t  max_distance = 0;
    size_t  i = 0;
    size_t  j = 0;
    while (checks < table->colums)
    {
        checks = 0;
        i = 0;
        while (i < table->rows)
        {
            if (distances[i] != -1)
            {
                j = 0;
                while (j < table->colums)
                {
                    if (get_value(table, i, j) == 1 && 
                        (distances[i] < distances[j] || distances[j] == -1))
                    {
                        distances[j] = distances[i] + 1;
                        if (distances[j] > (short int)max_distance)
                            max_distance = distances[j];
                    }
                    j++;
                }
                checks++;
            }
            i++;
        }
    }
    distances[p_end] = max_distance;
}

void    print_distances(t_data *data)
{
    size_t i = 0;
    while (i < data->table_size)
    {
        printf("start dis[%ld]:%d\n", i, data->dist_start[i]);
        printf("end   dis[%ld]:%d\n", i, data->dist_end[i]);
        i++;
    }
}

void    weight_table(t_data *data)
{
    data->t_weights = init_table(data->table_size, data->table_size, 0);
    size_t  i = 0;
    size_t  j = 0;
    size_t  forks = 0;
    data->max_forks = 0;
    while (i < data->table_size)
    {
        j = 0;
        forks = 0;
        while (j < data->table_size)
        {
            if (get_value(data->t_adjacency, i, j) == 1)
            {
                if (data->dist_start[i] <= data->dist_start[j] || data->dist_end[i] > data->dist_end[j])
                {
                    set_value(data->t_weights, i, j, 1);
                    forks++;
                }
                //else
                //    set_value(data->t_weights, i, j, 2);
            }
            j++;
        }
        i++;
        if (forks > data->max_forks)
            data->max_forks = forks;
    }
    printf("max forks: %ld\n", data->max_forks);
}

void    print_multipliers(t_data data)
{
    size_t i = 0;
    while (i < data.table_size)
    {
        printf("multiplier[%s]: %d\n", str_pos(data.names, i), data.multiplier[i]);
        i++;
    }
}

void    assing_multiplier(t_data *data) //testing old 
{
    size_t  max_weigth = 0;
    size_t  deep = 1;
    size_t  i = 0;
    size_t  j = 0;
    data->multiplier = malloc(sizeof(size_t) * data->table_size);
    while (i < data->table_size)
    {
        data->multiplier[i] = 0;
        if (data->dist_start[i] > (short int)max_weigth)
            max_weigth = data->dist_start[i];
        i++;
    }
    data->multiplier[data->p_start] = 1;
    while (deep <= max_weigth)
    {
        i = 0;
        while (i < data->table_size)
        {
            if (data->dist_start[i] == (short int)deep -1)
            {
                j = 0;
                while (j < data->table_size) //busca hermanos
                {
                    if (get_value(data->t_weights, i, j) == 2)
                        data->multiplier[i] += 1;
                    j++;
                }
                j = 0;
                while (j < data->table_size) //busca hijos
                {
                    if (get_value(data->t_weights, i, j) == 1)
                        data->multiplier[j] += data->multiplier[i];
                    j++;
                }
            }
            i++;
        }
        deep++;
    }
}
