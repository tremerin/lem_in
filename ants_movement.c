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
        lines += dif_paths;
        if (total_ants > dif_paths)
        {
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
    unsigned short  *assigned = malloc(sizeof(unsigned short *) * n_paths);
    if (n_paths == 1)
    {
        assigned[0] = ants;
        return(assigned);
    }
    //ordenar paths len de menor a mayor
    size_t i = 0;
    size_t j = 0;
    size_t dif_paths = 0;
    size_t open_paths = 1;
    unsigned short total_ants = ants - 1;
    assigned[0] = 1;

    while (i < n_paths - 1 && total_ants > 0)
    {
        dif_paths = paths_len[i + 1] - paths_len[i];
        j = 0;
        if (total_ants - ((dif_paths * i ) + paths_len[i]) < 0)
            break ;
        assigned[i] += paths_len[i];
        total_ants -= paths_len[i];
        while (j <= i)
        {
            total_ants -= dif_paths;
            assigned[j] += dif_paths;
            j++;
        }
        if (total_ants > (dif_paths * i))
        {
            assigned[i + 1] = 1;
            total_ants -= 1;
            open_paths++;
        }
        else
            break ;
        i++;
    }
    //repatir resto de hormigas
    if (total_ants > 0)
    {
        unsigned short rest = total_ants / open_paths;
        i = 0;
        while (i < open_paths)
        {
            assigned[i] += rest;
            i++;
        }
        if (total_ants % open_paths != 0)
            assigned[0] += 1;
    }


    return (assigned);
}

int main(void)
{
    unsigned short ants = 100;
    size_t n_paths = 3;
    size_t *lens = malloc(sizeof(size_t) * n_paths);
    lens[0] = 5;
    lens[1] = 20;
    lens[2] = 50;
    size_t lines = num_lines(ants, lens, n_paths);
    printf("lines: %ld\n", lines);
    unsigned short *paths = assign_ants(ants, lens, n_paths);
    size_t i = 0;
    while (i < n_paths)
    {
        printf("path[%ld] %d\n", i, paths[i]);
        i++;
    }
    return (0);
}