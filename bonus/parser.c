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

void    draw_room(t_data *data, char *str)
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
    data->rooms[data->n_rooms].point.x = ft_atoi(str + space_one) * 100 + 50;
    data->rooms[data->n_rooms].point.y = ft_atoi(str + space_two) * 100 + 50;
    center = data->rooms[data->n_rooms].point;
    draw_circle(data->map, center, 25, WHITE);
    draw_circle(data->map, center, 26, BLUE);
    draw_circle(data->map, center, 27, BLUE);
    draw_circle(data->map, center, 28, BLUE);
    draw_circle(data->map, center, 29, WHITE);
    data->names = mlx_put_string(data->mlx, data->rooms[data->n_rooms].name, center.x, center.y + 25);
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
        if (ft_strncmp(data->rooms[i].name, name_one, len_one) == 0)
        {
            start.x = data->rooms[i].point.x;
            start.y = data->rooms[i].point.y;
        }
        if (ft_strncmp(data->rooms[i].name, name_two, len_two) == 0)
        {
            end.x = data->rooms[i].point.x;
            end.y = data->rooms[i].point.y;
        }
        i++;
    }
    draw_line(data->map, start, end, WHITE);
    draw_line(data->map, start, end, RED);
    free(name_one);
    free(name_two);
}

void    parser_and_draw(t_data *data)
{
    char    *str = NULL;

    str = get_next_line(0);
    while (str)
    {
        if (is_room(str))
        {
            printf("is room: %s", str);
            draw_room(data, str);
        }
        else if (is_link(str))
        {
            printf("is link: %s", str);
            draw_link(data, str);
        }
        free(str);
        str = get_next_line(0);
    }
}