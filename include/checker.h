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


t_multi_str *init_multi_str(size_t size, size_t len);
void        init_data(t_data *data);
t_table     *init_table(int rows, int columns, char value);
int         is_int(char *str);
int         is_room(char *str);
int         is_link(char *str);
void        add_room_name(t_multi_str *multi, char *str);
size_t      get_str_index(t_multi_str *multi, char *str);
void        set_value(t_table *table, int row, int colum, char value);
void        read_link(t_data *data, char *link);
char        *str_pos(t_multi_str *multi, size_t pos);
void        create_ants(t_data *data);
char        get_value(t_table *table, int row, int colum);
size_t      check_movement(t_data *data, int num_ant, int index);
void        check_rooms(t_data *data);
void        save_movements(t_data *data, char *str);
void        check_ants(t_data *data);
void        parser(t_data *data);
void        free_data(t_data *data);
int         main(void);

#endif