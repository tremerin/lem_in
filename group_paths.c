#include "lem_in.h"

void    group_paths(t_data *data, unsigned int paths)
{
    data->groups = malloc(sizeof(unsigned short *) * data->valid_paths);
    size_t  i = 0;
    while (i < data->valid_paths)
    {
        data->groups[i] = malloc(sizeof(unsigned short) * data->valid_paths);
        i++;
    }


    unsigned short groups = 1;
    i = 0;
    while (i < groups)
    {
        i++; 
    } 
}