#include "../include/visualizer.h"

size_t  room_index(t_data *data, char *room_name)
{
    size_t  i = 0;
    size_t  len = ft_strlen(room_name);
    while (i < data->n_rooms)
    {
        if (ft_strncmp(data->rooms[i].name, room_name, len) == 0)
            return (i);
        i++;
    }
    return (i);
}

void    calculate_delta(t_data *data, int i)
{
    data->instructions->delta_x[i] = (data->instructions->destination[i].x - 50) - data->ant->instances[data->instructions->ants_moving[i] -1].x;
    data->instructions->delta_y[i] = (data->instructions->destination[i].y - 50) - data->ant->instances[data->instructions->ants_moving[i] -1].y;
    float pixels = sqrt((data->instructions->delta_x[i] * data->instructions->delta_x[i]) + (data->instructions->delta_y[i] * data->instructions->delta_y[i]));
    data->instructions->delta_x[i] = data->instructions->delta_x[i] / pixels;
    data->instructions->delta_y[i] = data->instructions->delta_y[i] / pixels;
    data->instructions->pixel_x[i] = data->ant->instances[data->instructions->ants_moving[i] -1].x;
    data->instructions->pixel_y[i] = data->ant->instances[data->instructions->ants_moving[i] -1].y;
}
 
void    parser_instruction(t_data *data)
{
    size_t spaces = 0;
    size_t i = 0;
    while (data->instructions->instrucction[i])
    {
        if (data->instructions->instrucction[i] == ' ')
            spaces++;
        i++;
    }
    data->instructions->n_ants = 1 + spaces;
    data->instructions->ants_moving = malloc(sizeof(int) * data->instructions->n_ants);
    data->instructions->destination = malloc(sizeof(t_point) * data->instructions->n_ants);
    data->instructions->pixel_x = malloc(sizeof(float) * data->instructions->n_ants);
    data->instructions->pixel_y = malloc(sizeof(float) * data->instructions->n_ants);
    data->instructions->delta_x = malloc(sizeof(float) * data->instructions->n_ants);
    data->instructions->delta_y = malloc(sizeof(float) * data->instructions->n_ants);
    i = 0;
    char *str;
    size_t pos_l = 0;
    size_t pos_slash = 0;
    size_t ants = 0;
    int start = 0;
    int end = 0;
    while (data->instructions->instrucction[i])
    {
        if (data->instructions->instrucction[i] == 'L')
        {
            pos_l = i;
            start = 1;
        }
        if (data->instructions->instrucction[i] == '-')
        {
            pos_slash = i;
            end = 1;
        }
        if ((data->instructions->instrucction[i] == ' ' || data->instructions->instrucction[i] == '\n') && end == 1)
        {
            str = ft_substr(data->instructions->instrucction, pos_slash + 1, (i - pos_slash)-1);
            data->instructions->destination[ants] = data->rooms[room_index(data, str)].point;
            ants++;
            end = 0;
        }
        if (start && end)
        {
            str = ft_substr(data->instructions->instrucction, pos_l + 1, (pos_slash - pos_l)-1);
            data->instructions->ants_moving[ants] = ft_atoi(str);
            start = 0;
            free(str);
        }
        i++;
    }
    if (end == 1)
    {
        str = ft_substr(data->instructions->instrucction, pos_slash + 1, (i - pos_slash)-1);
        data->instructions->destination[ants] = data->rooms[room_index(data, str)].point;
    }
    i = 0;
    while (i < data->instructions->n_ants)
    {
        calculate_delta(data, i);
        i++;
    }
}