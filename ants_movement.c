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

size_t *path_len_sort(t_data *data)
{
    size_t *paths_len = malloc(sizeof(size_t) * data->n_paths);
    size_t index = 0;
    for (size_t i = 0; i < data->n_paths; i++)
    {
        for (size_t j = 0; j < data->n_paths; j++)
        {
            if (index == data->paths_index[j])
            {
                paths_len[index] = data->paths[j].len;
                index++;
            }
        }
    }
    for (size_t i = 0; i < data->n_paths; i++)
    {
        printf("len: %li\n", paths_len[i]);
    }
    return paths_len;
}

void    moving_ants(t_data *data, size_t *paths_len, size_t n_paths)
{
    size_t lines = num_lines(data->ants, paths_len, n_paths);
    printf("ants:%d\n", data->ants);
    printf("lines:%ld\n", lines);
    unsigned short *assigned_ants = assign_ants(data->ants, paths_len, n_paths);
    printf("assigned ants[0]: %d\n", assigned_ants[0]);
    printf("assigned ants[1]: %d\n", assigned_ants[1]);
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
                    printf("L%ld-%s ", ant_num + ants, str_pos(data->names, 
                        data->paths[data->paths_index[path]].nodes[steps - ants]));
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

/* int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sig;

	i = 0;
	num = 0;
	sig = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sig = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + str[i] - '0';
		i++;
	}
	return (num * sig);
}

int main(int argc, char** argv)
{
    size_t *lens = malloc(sizeof(size_t) * argc);
    size_t ants = ft_atoi(argv[1]);
    size_t i = 0;
    size_t n_paths = argc - 2;
    while (i < n_paths)
    {
        lens[i] = ft_atoi(argv[i+ 2]);
        printf("len[%ld]%ld\n", i, lens[i + 2]);
        i++;
    }
    size_t lines = num_lines(ants, lens, n_paths);
    printf("lines: %ld\n", lines);
    unsigned short *paths = assign_ants(ants, lens, n_paths);
    i = 0;
    while (i < n_paths)
    {
        printf("path[%ld] %d\n", i, paths[i]);
        i++;
    }
    return (0);
} */
