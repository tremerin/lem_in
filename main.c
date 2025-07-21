#include "lem_in.h"

void init_data(t_data *data)
{

    data->names = init_multi_str(4000, 5);
    if (!data->names)
    {
        perror("Error: malloc");
        exit(EXIT_FAILURE);
    }
    data->t_adjacency = NULL;
}

void free_data(t_data *data)
{
    free_multi_str(data->names);
    if (data->t_adjacency != NULL)
        free_table(data->t_adjacency);
}

int main(void)
{
    t_data data;
    init_data(&data);
    printf("1\n");
    file_parser(&data);
    printf("2\n");
    //print_table(data.t_adjacency);
    free_data(&data);
    return (0);
}