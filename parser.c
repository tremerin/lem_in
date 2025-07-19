#include "lem_in.h"

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
    size_t  i;
    size_t  space_one;
    size_t  space_two;

    i = space_one = space_two = 0;
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
    //printf("num1: %s,num2: %s\n", num_one, num_two);
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
    size_t  i;
    size_t  dash;

    i = 0;
    dash = 0;
    if (str[i] == ' ' || str[i] == '-')
        return (0);
    while (str[i]) 
    {
        if (str[i] == '-' && dash == 0)
        {
            dash++;
            //check room name
        }
        i++;
    }
    if (dash != 1)
        return (0);

    return (1);
}

void    file_parser(t_data *data)
{
    char    *str = get_next_line(0);
    (void)data;
    while (str)
    {
        free(str);
        str = get_next_line(0);
    }
}
