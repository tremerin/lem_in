#include "../include/visualizer.h"



t_data    *init_data(size_t width, size_t height, size_t cell_size, size_t margin)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data)
    {
        perror("Error: bad malloc");
        return (NULL);
    }
    if (!(data->mlx = mlx_init(width, height, "Visualizer", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return (NULL);
	}
    if (!(data->map_1 = mlx_new_image(data->mlx, width, height)) || mlx_image_to_window(data->mlx, data->map_1, 0, 0) == -1)
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return (NULL);
    }
    if (!(data->map_2 = mlx_new_image(data->mlx, width, height)) || mlx_image_to_window(data->mlx, data->map_2, 0, 0) == -1)
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return (NULL);
    }
    if (!(data->names = mlx_new_image(data->mlx, width, height)) || mlx_image_to_window(data->mlx, data->names, 0, 0) == -1)
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return (NULL);
    }
    data->width = width;
    data->height = height;
    data->cell_size = cell_size;
    data->margin = margin;
    data->instructions = malloc(sizeof(t_instructions));
    data->instructions->n_ants = 0;
    data->instructions->ants_moving = NULL;
    data->instructions->instrucction = NULL;
    data->instructions->destination = NULL;
    data->instructions->state = 1;
    return (data);
}

void free_data(t_data *data)
{
    mlx_terminate(data->mlx);
    free(data);
}

void reading_hook(void *param)
{
    t_data *data = param;
    char *str;
    if (data->instructions->state == 1)
    {
        printf("reading hook: ");
        str = get_next_line(0);
        if (str == NULL)
            data->instructions->state = 0;
        else 
        {
            data->instructions->instrucction = ft_strdup(str);
            //parseo instruccion
            data->instructions->state = 2;
        } 
        printf("%s", str);
        free(str);
    }
}

void moving_hook(void *param)
{
    t_data *data = param;
    (void)data;

}

int main(void)
{
    t_data *data = init_data(1900, 1200, 100, 50);
    if (data == NULL)
    {
        perror("Error: init fail");
        return (1);
    }
    data->max_rooms = 120;
    data->n_rooms = 0;
    data->rooms = malloc(sizeof(t_room) * data->max_rooms);
    mlx_loop_hook(data->mlx, reading_hook, data);
    mlx_loop_hook(data->mlx, moving_hook, data);
    parser_and_draw(data);
	mlx_loop(data->mlx);
    free(data);
    return (0);
}