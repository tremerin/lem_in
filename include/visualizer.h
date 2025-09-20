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
    int             x;
    int             y;
}   t_point;

typedef struct s_room
{
    char            *name;
    t_point         point;
}   t_room;

typedef struct s_instructions
{
    /*
    0: No instruction 
    1: Waiting instruction -> start state
    2: Executing instruction
    3: End of instruction -> go to state 1
    */
    int             state; 
    char            *instrucction;
    size_t          n_ants;
    int             *ants_moving;
    t_point         *destination;
    float           *pixel_x;
    float           *pixel_y; 
    float           *delta_x;
    float           *delta_y;
}   t_instructions;

typedef struct s_data
{
    int             height;
    int             width; 
    mlx_t           *mlx;
    mlx_image_t     *map_1;
    mlx_image_t     *map_2;
    mlx_image_t     *names;
    mlx_image_t     *ant;
    mlx_image_t     *ants_numbers;
    t_room          *rooms;
    size_t          n_rooms;
    size_t          max_rooms;
    size_t          ants;
    size_t          cell_size;
    size_t          margin;
    size_t          p_start;
    size_t          p_end;
    t_instructions  *instructions;
}   t_data;

//parser
void    parser_and_draw(t_data *data);

//instruction
void    parser_instruction(t_data *data);

//shapes
void	draw_line(mlx_image_t *image, t_point begin, t_point end, int color);
void	draw_line_width(mlx_image_t *image, t_point begin, t_point end, size_t width, int color);
void	draw_circle(mlx_image_t *image, t_point center, int radius, int color);
void	draw_fill_circle(mlx_image_t *image, t_point center, int radius, int color);
void	draw_poli(mlx_image_t *img, t_point *vertices, int vrt_num, int color);
void	draw_cell(mlx_image_t *img, t_point init, int size, int color);

#endif

