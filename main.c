#include "lem_in.h"

void init_data(t_data *data, size_t name_len)
{
    data->name_len = name_len;
    data->names = malloc(sizeof(char) * data->name_len * 4000);
    if (!data->names)
    {
        perror("Error: no memory");
        exit(EXIT_FAILURE);
    }
    ft_bzero(data->names, data->name_len *4000);
}

void free_data(t_data *data)
{
    free(data->names);
}

int main(void)
{
    t_data data;
    init_data(&data, 5);
    file_parser(&data);
    free_data(&data);
    return (0);
}