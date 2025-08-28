#include "lem_in.h"

int     compatible_paths(t_path *path_one, t_path *path_two)
{
    size_t i = 0;
    size_t j = 0;
    while (i < path_one->len)
    {
        j = 0;
        while (j < path_two->len)
        {
            if (path_one->nodes[i] == path_two->nodes[j])
                return (0);
            j++;
        }
        i++;
    }
    return (1);
} 


void    group_paths(t_data *data, unsigned int paths)
{
    (void)paths;
    (void)data;
}