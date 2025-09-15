#include "../include/visualizer.h"

t_data    *init_data(size_t width, size_t height)
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
    if (!(data->map = mlx_new_image(data->mlx, width, height)))
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return (NULL);
    }
    if (!(data->names = mlx_new_image(data->mlx, width, height)))
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return (NULL);
    }
    if (mlx_image_to_window(data->mlx, data->map, 0, 0) == -1)
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return (NULL);
    }
    if (mlx_image_to_window(data->mlx, data->names, 0, 0) == -1)
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return (NULL);
    }
    return (data);
}

void free_data(t_data *data)
{
    mlx_terminate(data->mlx);
    free(data);
}

int main(void)
{
    t_data *data = init_data(900, 900);
    if (data == NULL)
    {
        perror("Error: init fail");
        return (1);
    }
    data->max_rooms = 10;
    data->n_rooms = 0;
    data->rooms = malloc(sizeof(t_room) * data->max_rooms);
    parser_and_draw(data);
	mlx_loop(data->mlx);
    free(data);
    return (0);
}