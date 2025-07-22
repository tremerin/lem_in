#include "lem_in.h"

void init_distances(t_data *data)
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