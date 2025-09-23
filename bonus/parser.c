#include "../include/visualizer.h"

int     is_int(char *str)
{
    while (*str && *str != '\n')
    {
        if (!ft_isdigit(*str))
                return (0);
        str++;
    }
    return (1);
}

int     is_instrucction(char *str)
{
    if (str[0] == 'L')
        return (1);
    else
        return (0);
}

int     is_room(char *str)
{
    size_t  i = 0;
    size_t  space_one = 0;
    size_t  space_two = 0;

    if (str[0] == 'L' || str[0] == '#' || str[0] == ' ')
        return (0);
    while (str[i] && str[i] != '\n')
    {
        if (str[i] == ' ')
        {
            if (space_one == 0)
                space_one = i + 1;
            else if (space_two == 0)
                space_two = i + 1;
            else
                return (0);
        } 
        i++;
    }
    if (space_two == 0)
        return (0);
    char * num_one = ft_substr(str, space_one, (space_two - space_one) -1);
    char * num_two = ft_substr(str, space_two, (ft_strlen(str) - space_two) -1);
    if (!is_int(num_one) || !is_int(num_two))
    {
        free(num_one);
        free(num_two);
        return (0);
    }
    free(num_one);
    free(num_two);
    return (1);
}


int     is_link(char *str)
{
    size_t  i = 0;
    size_t  dash = 0;

    if (str[i] == ' ' || str[i] == '-')
        return (0);
    while (str[i]) 
    {
        if (str[i] == '-')
        {
            dash++;
        }
        i++;
    }
    if (dash != 1)
        return (0);

    return (1);
}

void    draw_room(t_data *data, char *str, int dist, int margin, int color)
{
    size_t  i = 0;
    size_t  space_one = 0;
    size_t  space_two = 0;
    t_point center;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] == ' ')
        {
            if (space_one == 0)
                space_one = i + 1;
            else if (space_two == 0)
                space_two = i + 1;
        } 
        i++;
    }
    data->rooms[data->n_rooms].name = ft_substr(str, 0, space_one -1);
    data->rooms[data->n_rooms].point.x = ft_atoi(str + space_one) * dist + margin;
    data->rooms[data->n_rooms].point.y = ft_atoi(str + space_two) * dist + margin;
    if (data->rooms[data->n_rooms].point.x > (int)data->max_x)
        data->max_x = data->rooms[data->n_rooms].point.x;
    if (data->rooms[data->n_rooms].point.y > (int)data->max_y)
        data->max_y = data->rooms[data->n_rooms].point.y;
    center = data->rooms[data->n_rooms].point;
    //draw_fill_circle(data->map_1, center, 31, BLACK);
    draw_fill_circle(data->map_1, center, 29, color);
    draw_fill_circle(data->map_2, center, 26, RED);
    data->names = mlx_put_string(data->mlx, data->rooms[data->n_rooms].name, 
        center.x - ft_strlen(data->rooms[data->n_rooms].name) * 5, center.y - 10);
    data->n_rooms++;
}

void    draw_link(t_data *data, char *str)
{
    t_point start = {0, 0};
    t_point end = {0, 0};
    char    *name_one;
    char    *name_two;
    size_t  i = 0;

    while (str[i] && str[i] != '-') 
        i++;

    name_one = ft_substr(str, 0, i);
    name_two = ft_substr(str, i + 1, ft_strlen(str) -1);
    size_t len_one = ft_strlen(name_one);
    size_t len_two = ft_strlen(name_two) -1;
    i = 0;
    while (i < data->n_rooms)
    {
        if (ft_strncmp(data->rooms[i].name, name_one, len_one) == 0 && ft_strlen(data->rooms[i].name) == len_one)
        {
            start.x = data->rooms[i].point.x;
            start.y = data->rooms[i].point.y;
        }
        if (ft_strncmp(data->rooms[i].name, name_two, len_two) == 0 && ft_strlen(data->rooms[i].name) == len_two)
        {
            end.x = data->rooms[i].point.x;
            end.y = data->rooms[i].point.y;
        }
        i++;
    }
    draw_line_width(data->map_1, start, end, 12, WHITE);
    draw_line_width(data->map_2, start, end, 8, RED);
    free(name_one);
    free(name_two);
}

void    create_ants(t_data *data)
{
    size_t  i = 0;
    if (!(data->ant = mlx_new_image(data->mlx, 100, 100)))
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return;
    }
    if (!(data->ants_numbers = mlx_new_image(data->mlx, data->width, data->height)))
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return;
    }
    if (mlx_image_to_window(data->mlx, data->ants_numbers, 0, 0) == -1)
    {
        mlx_close_window(data->mlx);
        puts(mlx_strerror(mlx_errno));
        return;
    }
    t_point center = {50, 50};
    draw_fill_circle(data->ant, center, 20, BLACK);
    while (i < data->ants)
    {
        if (mlx_image_to_window(data->mlx, data->ant,  data->rooms[data->p_start].point.x - 50, data->rooms[data->p_start].point.y -50) == -1)
        {
            mlx_close_window(data->mlx);
            puts(mlx_strerror(mlx_errno));
            return;
        }
        i++;
    }
}

void    parser_and_draw(t_data *data)
{
    char    *str = NULL;
    size_t  start = 0;
    size_t  end = 0;
    size_t  rooms = 0;

    str = get_next_line(0);
    data->ants = ft_atoi(str);
    free(str);
    str = get_next_line(0);
    while (str)
    {
        if (is_room(str))
        {
            printf("is room: %s", str);
            if (start == 1)
            {
                draw_room(data, str, data->cell_size, data->margin, GREEN);
                data->p_start = rooms;
                //create_ants(data);
                start++;
            }
            else if (end == 1)
            {
                draw_room(data, str, data->cell_size, data->margin, GREEN);
                data->p_end = rooms;
                end++;                
            }
            else    
                draw_room(data, str, data->cell_size, data->margin, BROWN);
            rooms++;
        }
        else if (is_link(str))
        {
            printf("is link: %s", str);
            draw_link(data, str);
        }
        else if (ft_strncmp(str, "##start\n", 9) == 0)
        {
            start++;
        }
        else if (ft_strncmp(str, "##end\n", 7) == 0)
        {
            end++;
        }
        else if (ft_strncmp(str, "##speed ", 8) == 0)
        {
            data->instructions->speed = ft_atoi(str + 8);
        }
        else if (is_instrucction(str))
        {
            mlx_set_window_size(data->mlx, data->max_x + data->margin, data->max_y + data->margin);
            data->instructions->instrucction = ft_strdup(str);
            data->instructions->state = 2;
            create_ants(data);
            printf("parser, instrucction: %s", str);
            parser_instruction(data);
            break ;
        }
        else if (!ft_strncmp(str, "#", 1) == 0)
        {
            printf("%s", str);
            free(str);
            break ;
        }  
        free(str);
        str = get_next_line(0);
    }
    if (str != NULL)
        free(str);
}