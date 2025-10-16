#include "../include/lem_in.h"

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
    pos_name_one = get_str_index(data->names, node_one);
    pos_name_two = get_str_index(data->names, node_two);
    set_value(data->t_adjacency, pos_name_one, pos_name_two, 1);
    set_value(data->t_adjacency, pos_name_two, pos_name_one, 1);
    free(node_one);
    free(node_two);
}


void fill_diagonal(t_data *data)
{
    unsigned int i = 0;
    while (i < data->t_adjacency->rows)
    {
        if (i != data->p_start && i != data->p_end)
            set_value(data->t_adjacency, i, i, 1);
        i++;
    }
}


void print_table(t_table *table, t_data *data)
{
    if (!table || !table->array)
    {
        printf("Error: tabla nula\n");
        return;
    }
    
    // Imprimir índices de columnas
    for (unsigned int col = 0; col < table->columns; col++)
    {
        printf("%3s", str_pos(data->names, col));
    }
    printf("\n");
    
    // Línea separadora
    printf("   ");
    for (unsigned int col = 0; col < table->columns; col++)
    {
        printf("---");
    }
    printf("\n");
    
    // Imprimir filas
    for (unsigned int row = 0; row < table->rows; row++)
    {
        printf("%2d |", row);  // Índice de fila
        
        for (unsigned int col = 0; col < table->columns; col++)
        {
            int index = row * table->columns + col;
            printf("%3d", table->array[index]);
        }
        printf("\n");
    }
    printf("\n");
}


void    file_parser(t_data *data)
{
    int     control = 0; //ants = 0, rooms = 1, links = 2
    int     start = 0;
    int     end = 0;
    char    *str = NULL;
    data->ants = 0;
    size_t  rooms = 0;

    str = get_next_line(0);
    while (str)
    {
        //waiting rooms
        if (control == 1)
        {
            if (is_room(str))
            {
                add_room_name(data->names, str);
                if (start == 1)
                {
                    start++;
                    data->p_start = rooms;
                }
                else if (end == 1)
                {
                    end++;
                    data->p_end = rooms;
                }
                rooms++;
            }
            //check start
            else if (ft_strncmp(str, "##start\n", 9) == 0)
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
            //check end
            else if (ft_strncmp(str, "##end\n", 7) == 0)
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
            else if (start == 1 || end == 1)
            {
                printf("%s", str);
                free(str);
                break ;
            }
            //create table
            else if (is_link(str))
            {
                data->t_adjacency = init_table(rooms, rooms, 0);
                fill_diagonal(data);
                data->table_size = rooms;
                control = 2;
                read_link(data, str);
            }
            else if (!ft_strncmp(str, "#", 1) == 0)
            {
                printf("%s", str);
                free(str);
                break ;
            }  
        }
        //waiting links
        else if (control == 2)
        {
            if (is_link(str))
            {
                read_link(data, str);
            }
            else if (!ft_strncmp(str, "#", 1) == 0)
            {
                printf("%s", str);
                free(str);
                break ;
            }  
        }
        //waiting ants
        else if (control == 0)
        {
            if (is_int(str))
            {
                data->ants = ft_atoi(str);
                control = 1;
            }
            else if (!ft_strncmp(str, "#", 1) == 0)
            {
                    perror("Error: no ants");
                    free(str);
                    exit(EXIT_FAILURE);
            }  
        }
        if (!data->flags.print_map)
        {
            printf("%s", str);
        }
        free(str);
        str = get_next_line(0);
    }
    if (!data->flags.print_map)
    {
        printf("\n");
    }
    if (start < 2)
    {
        perror("Error: no start");
        if (data->names != NULL)
            free_multi_str(data->names);
        exit(EXIT_FAILURE);
    }
    else if (end < 2)
    {
        perror("Error: no end");
        if (data->names != NULL)
            free_multi_str(data->names);
        exit(EXIT_FAILURE);
    }
    else if (data->t_adjacency == NULL)
    {
        perror("Error: insufficient data");
        free_multi_str(data->names);
        exit(EXIT_FAILURE);
    }
}
