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
    printf("distances\n");
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