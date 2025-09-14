#ifndef VISUALIZER_H
    #define VISUALIZER_H

# include "../Libft/libft.h"
# include "../MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

# define RED     0xFF0000FF
# define GREEN   0x00FF00FF
# define BLUE    0x0000FFFF
# define YELLOW  0xFFFF00FF
# define CYAN    0x00FFFFFF
# define MAGENTA 0xFF00FFFF
# define ORANGE  0xFFA500FF
# define PURPLE  0x800080FF
# define WHITE   0xFFFFFFFF
# define BLACK   0x000000FF

typedef struct s_point
{
    uint32_t    x;
    uint32_t    y;
}   t_point;

typedef struct s_room
{
    char        *name;
    t_point     point;
}   t_room;

typedef struct s_data
{
    int         height;
    int         width; 
    mlx_t       *mlx;
    mlx_image_t *map;
    t_room      *rooms;
    size_t      n_rooms;
    size_t      max_rooms;
}   t_data;

//parser
void    parser_and_draw(t_data *data);


//shapes
void	draw_line(mlx_image_t *image, t_point begin, t_point end, int color);
void	draw_circle(mlx_image_t *image, t_point center, int radius, int color);
void	draw_poli(mlx_image_t *img, t_point *vertices, int vrt_num, int color);
void	draw_cell(mlx_image_t *img, t_point init, int size, int color);

#endif

