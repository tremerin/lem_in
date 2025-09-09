#include "lem_in.h"


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


void    add_str(t_multi_str *multi, char *str)
{
    size_t  i = multi->count * multi->len_str;
    size_t  j = 0;
    size_t  end = i + multi->len_str -1;
    while (i < end && str[j])
    {
        multi->array[i] = str[j];
        i++;
        j++;
    }
    multi->array[i] = '\0';
    multi->count++;
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


char    *str_pos(t_multi_str *multi, size_t pos)
{
    return (char *)(multi->array + (pos * multi->len_str));
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


void    free_multi_str(t_multi_str *multi)
{
    free(multi->array);
    free(multi);
}