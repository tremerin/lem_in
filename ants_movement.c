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

// int main(void)
// {
//     unsigned short ants = 100;
//     size_t *lens = malloc(sizeof(size_t) * 3);
//     lens[0] = 20;
//     lens[1] = 20;
//     lens[2] = 30;
//     size_t lines = num_lines(ants, lens, 3);
//     printf("lines: %ld\n", lines);
//     return (0);
// }