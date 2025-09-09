# include "lem_in.h"

size_t num_lines(unsigned short ants, size_t *paths_len, size_t n_paths)
{
    size_t lines = 0;
    if (n_paths == 1)
    {
        lines = paths_len[0] + ants - 1;
        return (lines);
    }
    //ordenar paths len de menor a mayor
    size_t i = 0;
    size_t dif_paths = 0;
    size_t open_paths = 1;
    unsigned short total_ants = ants - 1;
    lines = paths_len[0];
    size_t actual_len = paths_len[0];
    while (i < n_paths - 1 && total_ants > 0)
    {
        dif_paths = paths_len[i + 1] - actual_len;
        if (total_ants > dif_paths * open_paths)
        {
            lines += dif_paths;
            actual_len = paths_len[i + 1];
            total_ants -= (dif_paths * open_paths) + 1;
            open_paths++;
        }
        i++;
    }
    //repatir resto de hormigas
    lines += total_ants / open_paths;
    if (total_ants % open_paths != 0)
        lines++;
    return (lines);
}

unsigned short *assign_ants(unsigned short ants, size_t *paths_len, size_t n_paths)
{
    unsigned short *assigned = malloc(sizeof(unsigned short) * n_paths);
    ft_bzero(assigned, sizeof(unsigned short) * n_paths);
    size_t lines = 0;
    if (n_paths == 1)
    {
        assigned[0] = ants;
        return (assigned);
    }
    //ordenar paths len de menor a mayor
    size_t i = 0;
    size_t dif_paths = 0;
    size_t open_paths = 1;
    unsigned short total_ants = ants - 1;
    lines = paths_len[0];
    size_t actual_len = paths_len[0];
    while (i < n_paths - 1 && total_ants > 0)
    {
        dif_paths = paths_len[i + 1] - actual_len;
        if (total_ants > dif_paths * open_paths)
        {
            lines += dif_paths;
            actual_len = paths_len[i + 1];
            total_ants -= (dif_paths * open_paths) + 1;
            open_paths++;
        }
        i++;
    }
    //repatir resto de hormigas
    lines += total_ants / open_paths;
    size_t modulo = total_ants % open_paths;
    //hormigas por camino
    i = 0;
    while (i < open_paths)
    {
        assigned[i] = lines - (paths_len[i] - 1);
        if (modulo > 0)
        {
            assigned[i] += 1;
            modulo--;
        }
        i++;
    }
    return (assigned);
}


unsigned short  first_ant(size_t path, unsigned short *ants)
{
    unsigned short first = 1;
    size_t  i = 0;
    while (i < path)
    {
        first += ants[i];
        i++;
    }
    return (first);
}


void    moving_ants(t_data *data, size_t *paths_len, size_t n_paths, size_t lines)
{
    unsigned short *assigned_ants = assign_ants(data->ants, paths_len, n_paths);
    size_t steps = 0;
    size_t path = 0;
    size_t ants = 0;
    unsigned short ant_num = 0;
    while (steps < lines)
    {
        path = 0;
        while (path < n_paths)
        {
            ants = 0;
            ant_num = first_ant(path, assigned_ants);
            while (ants < assigned_ants[path])
            {
                if ((int)steps - (int)ants < (int)paths_len[path] && (int)steps - (int)ants >= 0)
                {
                    if (data->n_algo == 1)
                    {
                        printf("L%ld-%s ", ant_num + ants, str_pos(data->names, 
                            data->ff_paths.paths[path].nodes[steps - ants]));
                            //data->paths[data->paths_index[path]].nodes[steps - ants]));
                    }
                    else
                    {
                        printf("L%ld-%s ", ant_num + ants, str_pos(data->names, 
                            data->paths.paths[path].nodes[steps - ants]));
                            //data->paths[data->paths_index[path]].nodes[steps - ants]));
                    }
                }
                ants++;
            }
            path++;
        }
        printf("\n");
        steps++;
    }
    free(assigned_ants);
}
