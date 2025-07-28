#include "lem_in.h"


unsigned int *next_node(t_data * data, int pos, size_t path)
{
    unsigned int    i = 0;
    unsigned int    len = 0;
    unsigned int    *nodes = NULL;

    while (i < data->table_size)
    {
        if (get_value(data->t_weights, pos, i) > 0 &&
            !contain_pos(data->paths[path].nodes, i, data->paths[path].len))
            len++;
        i++;
    }
    nodes = malloc(sizeof(unsigned int) * (len +1));
    if (!nodes)
        return (NULL);
    nodes[0] = len;
    i = 0;
    len = 0;
    while (i < data->table_size)
    {
        if (get_value(data->t_weights, pos, i) > 0 &&
            !contain_pos(data->paths[path].nodes, i, data->paths[path].len))
        {
            len++;
            nodes[len] = i;
            //printf("node:%s\n", data->names[i]);
        }
        i++;
    }
    return (nodes);
}


int contain_pos(unsigned short *positions, unsigned int pos, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        if (positions[i] == pos)
            return (1);
        i++;
    }
    return (0);
}

void    number_of_paths(t_data *data)
{
    unsigned int paths = 1;
    unsigned int checks;
    size_t      i = 0;
    while (i < data->table_size)
    {
        size_t  j = 0;
        checks = 0;
        while (j < data->table_size)
        {
            if (get_value(data->t_weights, i, j) == 1)
                checks++;
            j++;
        }
        if (checks > 1)
            paths += (checks * data->multiplier[i]);
        i++;
    }
    data->n_paths = paths;
    data->paths = malloc(sizeof(t_path) * data->n_paths);
    //calculate max path len
    i = 0;
    while (i < data->n_paths)
    {
        data->paths[i].len = 0;
        data->paths[i].nodes = malloc(sizeof(unsigned int) * data->table_size);
        i++;
    }
}

void    path_validation(t_data *data, unsigned int paths)
{
    size_t  i = 0;
    data->valid_paths = 0;
    while (i < paths)
    {
        if (data->paths[i].nodes[data->paths[i].len - 1] == data->p_end)
        {
            data->paths[i].valid = 1;
            data->valid_paths++;
        }
        else
            data->paths[i].valid = 0;
        i++;
    }
}

void    print_paths(t_data *data, unsigned int paths)
{
    size_t i = 0;
    while (i < paths)
    {
        size_t j = 0;
        if (data->paths[i].valid == 1)
        {
            printf("Path[%lu] ", i);
            while (j < data->paths[i].len)
            {
                printf("%s ", str_pos(data->names, data->paths[i].nodes[j]));
                j++;
            }
            printf("\n");
        }
        i++;
    }
}

void path_finding(t_data *data)
{
    //init paths
    data->paths[0].nodes[0] = data->p_start;
    data->paths[0].len = 1;
    //acutal number of paths
    unsigned int *nexts;
    unsigned int paths = 1;
    unsigned int pos;
    //while paths are imcompletes
    int incomplete = 1;
    while (incomplete)
    {
        size_t i = 0;
        incomplete = 0;
        while (i < paths)
        {
            pos = data->paths[i].nodes[data->paths[i].len -1];
            //termina en la salida
            if (pos == data->p_end)
            {
                i++;
                continue;
            }
            nexts = next_node(data, pos, i);
            //termina sin salida
            if (nexts[0] == 0)
            {
                //free(nexts);
                //printf("no exit\n");
                i++;
                continue;
            }
            //continua el camino
            size_t j = 1;
            while (j <= nexts[0])
            {
                incomplete = 1;
                //añade otro nodo al camino actual
                if (j == 1)
                {
                    data->paths[i].nodes[data->paths[i].len] = nexts[j];
                    data->paths[i].len += 1;
                }
                //se bifurca
                else
                {
                    size_t cp = 0;
                    while (cp < data->paths[i].len)
                    {
                        data->paths[paths].nodes[cp] = data->paths[i].nodes[cp];
                        cp++;
                    }
                    data->paths[paths].nodes[cp -1] = nexts[j];
                    data->paths[paths].len = data->paths[i].len;
                    paths++;
                }
                j++;
            }
            i++;
        }
    }
    path_validation(data, paths);
    print_paths(data, paths);
}

