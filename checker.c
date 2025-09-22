#include "include/checker.h"


t_multi_str *init_multi_str(size_t size, size_t len)
{
    t_multi_str *new = malloc(sizeof(t_multi_str));
    if (!new)
    {
        perror("Error: malloc");
        exit(EXIT_FAILURE);
    }
    new->array = malloc(sizeof(char) * size * (len + 1));
    if (!new->array)
    {
        free(new);
        perror("Error: no memory");
        exit(EXIT_FAILURE);
    }
    ft_bzero(new->array, size * (len + 1));
    new->count = 0;
    new->len_str = len + 1;
    new->max_str = size;
    return (new);
}


void init_data(t_data *data)
{

    data->names = init_multi_str(6000, 5);
    if (!data->names)
    {
        perror("Error: malloc");
        exit(EXIT_FAILURE);
    }
    data->t_adjacency = NULL;
}


t_table *init_table(int rows, int columns, char value)
{
    t_table *new = malloc(sizeof(t_table));
    new->rows = rows;
    new->columns = columns;
    int size = rows * columns;
    new->array = malloc(sizeof(char) * size);
    if (!new->array)
    {
        perror("Error: no memory");
        free(new);
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < size)
    {
        new->array[i] = value;
        i++;
    }
    return new;
}


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


void    add_room_name(t_multi_str *multi, char *str)
{
    size_t  i = multi->count * multi->len_str;
    size_t  j = 0;
    size_t  end = i + multi->len_str -1;
    while (i < end && str[j] && str[j] != ' ')
    {
        multi->array[i] = str[j];
        i++;
        j++;
    }
    multi->array[i] = '\0';
    multi->count++;
}


size_t   get_str_index(t_multi_str *multi, char *str)
{
    size_t  i = 0;
    size_t  j = 0;
    size_t  len = ft_strlen(str);
    int     equal;

    while (i < multi->count)
    {
        j = 0;
        equal = 1;
        while (j < len)
        {
            if (multi->array[(i * multi->len_str) + j] != str[j])
            {
                equal = 0;
                break ;
            }
            j++;
        }
        if (equal)
            return (i);
        i++;
    }
    return (i);
}


void    set_value(t_table *table, int row, int colum, char value)
{
    table->array[(table->columns * row) + colum] = value;
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
    pos_name_one = get_str_index(data->names, node_one);
    pos_name_two = get_str_index(data->names, node_two);
    set_value(data->t_adjacency, pos_name_one, pos_name_two, 1);
    set_value(data->t_adjacency, pos_name_two, pos_name_one, 1);
    free(node_one);
    free(node_two);
}


char    *str_pos(t_multi_str *multi, size_t pos)
{
    return (char *)(multi->array + (pos * multi->len_str));
}


void create_ants(t_data *data)
{
    data->ants_data = malloc(sizeof(t_ants) * data->ants);
    char *room = str_pos(data->names, data->p_start);
    for (unsigned short i = 0; i < data->ants; i++)
    {
        data->ants_data[i].actual_pos = malloc(sizeof(char) * (ft_strlen(str_pos(data->names, data->p_start)) + 1));
        ft_strlcpy(data->ants_data[i].actual_pos, room, ft_strlen(room));
    }
}


char    get_value(t_table *table, int row, int colum)
{
    return (table->array[(table->columns * row) + colum]);
}


size_t check_movement(t_data *data, int num_ant, int index)
{
    int start = get_str_index(data->names, data->ants_data[num_ant].actual_pos);
    printf("num_ant %i start %i index %i\n", num_ant, start, index);
    printf("value: %i\n", get_value(data->t_adjacency, start, index));
    if (get_value(data->t_adjacency, start, index))
    {
        return 1;
    }
    return 0;
}

void save_movements(t_data *data, char *str)
{
    int i = 0;
    int init_num = 1;
    int init_room = 0;
    int k = 0;
    int j = 0;
    char *num;
    char *room;
    int num_ant = 0;
    int index = INT_MAX;
    printf("%s\n", str);
    while (str[i] != '\n')
    {
        if (str[i] == '-')
        {
            k = i;
            num = ft_substr(str, init_num, k - init_num);
            num_ant = ft_atoi(num) - 1;
            free(num);
            init_room = i + 1;
        }
        else if (str[i] == ' ' || str[i] == '\n' || str[i + 1] == '\0')
        {
            j = i;
            // int room_len;
            
            // if (str[i + 1] == '\0' && str[i] != ' ' && str[i] != '\n')
            // {
            //     // Último movimiento: incluir el carácter actual
            //     room_len = j - init_room + 1;
            // }
            // else
            // {
            //     // Movimiento con espacio: no incluir el espacio
            //     room_len = j - init_room;
            // }
            room = ft_substr(str, init_room, j - init_room);
            init_num = j + 2;
            index = get_str_index(data->names, room);
            if (!check_movement(data, num_ant, index))
            {
                printf("Movement from room %s to room %s is wrong\n", data->ants_data[num_ant].actual_pos, room);
                exit(EXIT_FAILURE);
            }
            free(data->ants_data[num_ant].actual_pos);
            data->ants_data[num_ant].actual_pos = room;

            if (str[i] == '\n' || str[i + 1] == '\0')
                break;
        }
        i++;
    }
}


void parser(t_data *data)
{
    char *str = NULL;
    unsigned short ants = 0;
    unsigned short link = 0;
    unsigned short move = 0;
    size_t  n_rooms = 0;

    str = get_next_line(0);
    while (str)
    {
        if (ants == 0)
        {
            if (is_int(str))
            {
                data->ants = ft_atoi(str);
                ants = 1;
            }
        }
        if (ft_strncmp(str, "##start\n", 9) == 0)
        {
            data->p_start = n_rooms;
        }
        if (ft_strncmp(str, "##end\n", 6) == 0)
        {
            data->p_end = n_rooms;
        }
        if (is_room(str))
        {
            add_room_name(data->names, str);
            n_rooms++;
        }
        else if (ft_strncmp(str, "L", 1) != 0 && is_link(str))
        {
            if (link == 0)
            {
                data->t_adjacency = init_table(n_rooms, n_rooms, 0);
                data->table_size = n_rooms;
                link = 1;
            }
            read_link(data, str);
        }
        else if (ft_strncmp(str, "L", 1) == 0)
        {
            if (move == 0)
            {
                create_ants(data);
                move = 1;
            }
            save_movements(data, str);
        }
        free(str);
        str = get_next_line(0);
    }
}


void free_data(t_data *data)
{
    for (int i = 0; i < data->ants; i++)
    {
        free(data->ants_data[i].actual_pos);
    }
    free(data->ants_data);
    free(data->t_adjacency);
    free(data->names->array);
    free(data->names);
}


int main(void)
{
    t_data data;
    init_data(&data);
    parser(&data);
    free_data(&data);
    return 0;
}