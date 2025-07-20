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
    size_t  end = i + multi->len_str;
    while (i < end && str[j])
    {
        multi->array[i] = str[j];
        i++;
        j++;
    }
    multi->count++;
}

void    free_multi_str(t_multi_str *multi)
{
    free(multi->array);
    free(multi);
}