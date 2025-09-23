#ifndef CHECKER_H
#define CHECKER_H

#include "../Libft/libft.h"
#include <stdio.h>
#include <limits.h>

typedef struct s_ants
{
    char    *actual_pos; //room name
    int     end_pos;
}   t_ants;

typedef struct s_multi_str
{
    char            *array;
    size_t          count;
    size_t          len_str;
    size_t          max_str;
}	t_multi_str;

typedef struct s_table
{
    unsigned int    rows;
    unsigned int    columns;
    char            *array;
}   t_table;

typedef struct s_data
{
    unsigned short  ants;
    unsigned short  p_start;
    unsigned short  p_end;
    t_table         *t_adjacency;
    size_t          table_size;
    t_multi_str     *names;
    t_ants          *ants_data;
}   t_data;

#endif