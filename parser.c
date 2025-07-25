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

char *get_name(char *room)
{
    char    *name;
    size_t  i;
    size_t  j;

    i = 0;
    j = 0;
    while (room[i] != ' ')
        i++;
    name = malloc((i + 1) * sizeof(char));
    while (j < i)
    {
        name[j] = room[j];
        j++;
    }
    name[j] = 0;
    return (name);
}

void    read_link(t_data *data, char *link)
{
    char    *node_one;
    char    *node_two;
    size_t  i = 0;
    size_t  len = ft_strlen(link);
    int     pos_name_one;
    int     pos_name_two;

    if (link[len -1] == '\n')
        len--;
    while (link[i])
    {
        if (link[i] == '-')
        {
            node_one = ft_substr(link, 0, i);
            node_two = ft_substr(link, i + 1, len - (i+1));
        }
        i++;
    }
    //printf("one: %s$\ntwo: %s$\n", node_one, node_two);
    pos_name_one = get_str_index(data->names, node_one);
    pos_name_two = get_str_index(data->names, node_two);
    //printf("one: %d, two: %d\n", pos_name_one, pos_name_two);
    set_value(data->t_adjacency, pos_name_one, pos_name_two, 1);
    set_value(data->t_adjacency, pos_name_two, pos_name_one, 1);
    free(node_one);
    free(node_two);
}

void    file_parser(t_data *data)
{
    int     start = 0;
    int     end = 0;
    char    *name;
    size_t  i = 0;

    char    *str = get_next_line(0);
    while (str)
    {
        //void line
        if (ft_strlen(str) == 1)
        {
            printf("void line\n");
            //try
            break ;
        }
        //check start
        if (ft_strncmp(str, "##start\n", 9) == 0)
        {
            if (start == 0)
                start++;
            else if (start > 1)
            {
                perror("Error: more than one entry");
                free(str);
                exit(EXIT_FAILURE);
            }
        }
        else if (start == 1)
        {
            start++;
            data->p_start = i;
        }
        //check end
        if (ft_strncmp(str, "##end\n", 7) == 0)
        {
            if (end == 0)
                end++;
            else if (end > 1)
            {
                perror("Error: more than one exit");
                free(str);
                exit(EXIT_FAILURE);
            }
        }
        else if (end == 1)
        {
            end++;
            data->p_end = i;
        }
        //check room
        if (is_room(str))
        {
            name = get_name(str);
            add_str(data->names, name);
            free(name);
            i++;
        }
        //check link
        else if (is_link(str))
        {
            if (data->t_adjacency == NULL)
            {
                data->t_adjacency = init_table(i, i, 0);
                data->table_size = i;
            }
            read_link(data, str);
        }
        free(str);
        str = get_next_line(0);
    }
}
