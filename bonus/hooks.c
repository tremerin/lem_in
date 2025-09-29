#include "../include/visualizer.h"

void reading_hook(void *param)
{
    t_data *data = param;
    char *str;
    if (data->instructions->state == 1)
    {
        str = get_next_line(0);
        if (str == NULL)
            data->instructions->state = 0;
        else 
        {
            data->instructions->instrucction = ft_strdup(str);
            parser_instruction(data);
            data->instructions->state = 2;
        } 
        free(str);
    }
} 

void moving_hook(void *param)
{
    t_data *data = param;
    size_t i = 0;
    size_t step = 0;
    size_t end_move = 0;
    if (data->instructions->state == 2)
    {
        while (i < data->instructions->n_ants)
        {
        step = 0;
            while (step < (size_t)data->instructions->speed)
            {
                if (data->ant->instances[data->instructions->ants_moving[i] -1].x != data->instructions->destination[i].x - 50)
                {
                    data->instructions->pixel_x[i] += (data->instructions->delta_x[i]);// * data->instructions->speed);
                    data->ant->instances[data->instructions->ants_moving[i] - 1].x = (int)data->instructions->pixel_x[i];
                }
                if (data->ant->instances[data->instructions->ants_moving[i] -1].y != data->instructions->destination[i].y - 50)
                {
                    data->instructions->pixel_y[i] += (data->instructions->delta_y[i]); //* data->instructions->speed);
                    data->ant->instances[data->instructions->ants_moving[i] - 1].y = (int)data->instructions->pixel_y[i];
                }
                step++;
            }
            i++;
        }
        i = 0;
        while (i < data->instructions->n_ants)
        {
            if (data->ant->instances[data->instructions->ants_moving[i] -1].x == data->instructions->destination[i].x - 50)
                end_move ++;
            if (data->ant->instances[data->instructions->ants_moving[i] -1].y == data->instructions->destination[i].y - 50)
                end_move ++;
            i++;
        }
        if (end_move == data->instructions->n_ants * 2)
            data->instructions->state = 1;
    }
}